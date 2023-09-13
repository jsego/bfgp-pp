import os
from copy import copy
import logging
import subprocess
import argparse
import random
from typing import List, Union
import tarski
from tarski.io import PDDLReader, FstripsWriter
from tarski.search import GroundForwardSearchModel
from tarski.search.operations import is_applicable, progress
from tarski.grounding.lp_grounding import ground_problem_schemas_into_plain_operators
from tarski.syntax.transform.action_grounding import ground_schema_into_plain_operator_from_grounding
from tarski.syntax.formulas import Tautology, CompoundFormula, Connective, is_atom
from pddl_translator import translate_pddl_to_ram
import numpy as np


# GLOBAL VARIABLES
action_counter = {}

def init_random_seeds():
	random.seed(1)
	np.random.seed(1)

def execute_command(command: List[str], **kwargs) -> int:
    cwd = kwargs["cwd"] if "cwd" in kwargs else os.getcwd()
    output_dir = kwargs["output_dir"] if "output_dir" in kwargs else "."
    stdout = open(output_dir + "/" + kwargs["stdout"], 'w') if "stdout" in kwargs else None
    stderr = open(output_dir + "/" + kwargs["stderr"], 'w') if "stderr" in kwargs else None

    logging.debug(f'Executing "{" ".join(map(str, command))}" on directory "{cwd}"')
    if stdout:
        logging.debug(f'Standard output redirected to "{stdout.name}"')
    if stderr:
        logging.debug(f'Standard error redirected to "{stderr.name}"')

    ret_code = subprocess.call(command, cwd=cwd, stdout=stdout, stderr=stderr)

    if stdout:
        stdout.close()
    if stdout is not None and os.path.getsize(stdout.name) == 0:  # Delete error log if empty
        os.remove(stdout.name)
    if stderr:
        stderr.close()
    if stderr is not None and os.path.getsize(stderr.name) == 0:  # Delete error log if empty
        os.remove(stderr.name)

    return ret_code


def run_fd(domain: str, instance: str, output_dir: str) -> Union[List[str], None]:
    """ Run Fast Downward on a given domain and instance, and return a plan,
    or None if the problem is not solvable. """
    instance_name = instance.split("/")[-1].split(".")[0]
    print(instance_name)
    # e.g. fast-downward.py --alias seq-opt-lmcut /home/frances/projects/code/downward-benchmarks/gripper/prob01.pddl
    # Optimal planner
    #args = f'--alias  seq-opt-lmcut --plan-file {output_dir}/{instance_name}.plan ' \
    #       f'--sas-file {output_dir}/{instance_name}_output.sas ' \
    #       f'{domain} {instance}'.split()
    # Satisficing planner
    args = f'--alias lama-first --plan-file {output_dir}/{instance_name}.plan ' \
           f'--sas-file {output_dir}/{instance_name}_output.sas ' \
           f'{domain} {instance}'.split()
    # ToDo: add fast-downward.py as a requirement (accessible from /usr/bin/ folder)
    ret_code = execute_command(command=['fast-downward.py'] + args, stdout="stdout", output_dir=output_dir)
    if ret_code != 0:
        # logging.error("Fast Downward error")
        return None

    plan = []
    with open(f'{output_dir}/{instance_name}.plan', 'r') as f:
        # Read up all lines in plan file that do not start with a comment character ";"
        plan = [line for line in f.read().splitlines() if not line.startswith(';')]
    return plan


def parse_domain_file(domain_file: str):
    """ Parses the PDDL instance file using Tarski. """
    reader = PDDLReader()
    reader.parse_domain(domain_file)
    return reader.problem


def parse_instance_file(domain_file: str, instance_file: str):
    """ Parses the PDDL instance file using Tarski. """
    reader = PDDLReader()
    reader.parse_domain(domain_file)
    reader.parse_instance(instance_file)
    return reader.problem


def generate_random_walk(model: tarski.search.GroundForwardSearchModel, length: int) -> List:
    tarski_state = model.problem.init
    walk = []
    for i in range(0, length):
        tarski_actions_states = [(str(a), s) for a, s in model.successors(tarski_state)]
        if not tarski_actions_states:
            return walk

        # New: sampling first the action label, then use to filter the ground operators
        tarski_action_labels = set([str(a).split('(')[0] for a, _ in tarski_actions_states])
        sampled_action_label = random.choice(list(tarski_action_labels))

        tarski_action, tarski_state = random.choice([ (a, s) for a, s in tarski_actions_states if a.split('(')[0] == sampled_action_label])
        pddl_action = "(" + " ".join((" ".join(tarski_action.split(","))).split("("))
        walk.append(pddl_action)
    return walk


def get_states_from_plan(model: tarski.search.GroundForwardSearchModel, plan: List[str],
                         init_state: tarski.model.Model = None) -> List[tarski.model.Model]:
    init = model.init() if init_state is None else init_state
    states, current_state = [init], init
    for a in plan:
        components = a.rstrip(')').lstrip('(').split()
        action = model.problem.get_action(components[0])
        grounded_operator = ground_schema_into_plain_operator_from_grounding(action, components[1:])
        if not is_applicable(current_state, grounded_operator):
            raise RuntimeError(f"Action {grounded_operator} from FD plan not applicable!")
        current_state = progress(current_state, grounded_operator)
        states.append(current_state)

    # ToDo: add the next condition only for plans
    #if not model.is_goal(current_state):
    #    raise RuntimeError(f"State after executing FD plan is not a goal: {current_state}")

    return states


def generate_instance_file(
        instance_filename: str,
        tarski_model: tarski.search.GroundForwardSearchModel,
        tarski_constants: List,
        tarski_init_state: tarski.model.Model,
        tarski_goal_state: tarski.model.Model) -> str:
    """ Useful to run FD on intermediate states, creating a temporary problem """
    new_problem = copy(tarski_model.problem)
    new_problem.init = tarski_init_state
    atoms = [atom for atom in tarski_goal_state.as_atoms() if is_atom(atom)]
    # Tarksi Connective.And does not work with an empty list or one atom
    if not atoms:
        new_problem.goal = Tautology()
    elif len(atoms) == 1:
        new_problem.goal = atoms[0]
    else:
        new_problem.goal = CompoundFormula(Connective.And, atoms)
    writer = FstripsWriter(new_problem)
    with open(instance_filename, "w") as ins_f:
        ins_f.write(writer.print_instance(tarski_constants))


def generate_instances(tarski_model, tarski_domain, domain_file, plan, output_dir: str):
    states = get_states_from_plan(tarski_model, plan)
    for idx, s in enumerate(states):
        if idx + 1 >= len(states):
            break
        action_label = plan[idx].split(" ")[0][1:]
        output_instance_dir = f"{output_dir}/{action_label}"
        if action_label in action_counter.keys():
            action_counter[action_label] += 1
        else:
            os.makedirs(output_instance_dir, exist_ok=True)
            action_counter[action_label] = 1
        counter = action_counter[action_label]

        generate_instance_file(instance_filename=f"{output_instance_dir}/{counter}.pddl",
                               tarski_model=tarski_model,
                               tarski_constants=tarski_domain.language.constants(),
                               tarski_init_state=s,
                               tarski_goal_state=states[idx+1])

        translate_pddl_to_ram(domain_file=domain_file,
                              instance_file=f"{output_instance_dir}/{counter}.pddl",
                              output_dir=output_instance_dir,
                              pddl_action=plan[idx],
                              id=counter)


def main():
    # ArgParser
    parser = argparse.ArgumentParser(description='State trajectory generator from plans')
    parser.add_argument("-d", "--domain", type=str, required=True)
    parser.add_argument("-i", "--instances", type=str, nargs='*', required=True)
    parser.add_argument("-o", "--outdir", type=str, required=True)
    args = parser.parse_args()

    domain_file = args.domain
    instance_files = args.instances
    output_dir = args.outdir

    # Preprocessing
    #random.seed(1)
    init_random_seeds()
    tarski_domain = parse_domain_file(domain_file)
    os.makedirs(f"{output_dir}/plans", exist_ok=True)

    for idx, ins_f in enumerate(instance_files):
        # Create Tarski model
        tarski_instance = parse_instance_file(domain_file, ins_f)
        tarski_model = GroundForwardSearchModel(tarski_instance, ground_problem_schemas_into_plain_operators(tarski_instance))
        # Generate a random walk
        walk = generate_random_walk(model=tarski_model, length=50)  # domain_file, ins_f, f"{output_dir}/plans")
        with open(f"{output_dir}/plans/random_walk.{idx}", "w") as rw:
            rw.write('\n'.join([str(a) for a in walk]))

        generate_instances(tarski_model=tarski_model, tarski_domain=tarski_domain, domain_file=domain_file,
                           plan=walk, output_dir=output_dir)

        # Generate LAMA plan
        plan = run_fd(domain_file, ins_f, f"{output_dir}/plans")
        generate_instances(tarski_model=tarski_model, tarski_domain=tarski_domain, domain_file=domain_file,
                           plan=plan, output_dir=output_dir)


if __name__ == "__main__":
    main()
