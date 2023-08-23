import sys
import random
import argparse
from typing import Tuple
from pddl_translator import translate_pddl_to_ram


def get_objects(n_size: int) -> str:
    return " ".join([f"l{i}" for i in range(1, n_size+1)]) + " - object "


def get_init(n_size: int) -> Tuple[str, int]:
    agent_at = random.randint(1, n_size)
    goal_at = agent_at
    while goal_at == agent_at:
        goal_at = random.randint(1, n_size)
    str_init = f"(at l{agent_at})\n"
    str_init += f"    (goal_at l{goal_at})\n"
    str_init += "    " + "    \n".join([f"(adjacent l{i} l{i+1})" for i in range(1, n_size)])
    return str_init, goal_at


def get_goals(goal_at: int) -> str:
    return f"(and (at l{goal_at}))"


def generate_problem(name: str, n_size: int):
    str_obj = get_objects(n_size)
    str_init, goal_at = get_init(n_size)
    str_goal = get_goals(goal_at)
    return f"(define (problem {name})\n" \
           f"  (:domain corridor)\n" \
           f"  (:objects {str_obj})\n" \
           f"  (:init {str_init})\n" \
           f"  (:goal {str_goal}))\n"


def generate_domain():
    return """(define (domain corridor)
 (:requirements :strips :negative-preconditions)
 (:predicates 
    (at ?l)
    (adjacent ?l1 ?l2)
    (goal_at ?l))
 
 (:action move_right
    :parameters (?from ?to)
    :precondition (and (adjacent ?from ?to) (at ?from) (not (at ?to)))
    :effect (and (not (at ?from)) (at ?to)))
    
 (:action move_left
    :parameters (?from ?to)
    :precondition (and (adjacent ?to ?from) (at ?from) (not (at ?to)))
    :effect (and (not (at ?from)) (at ?to))))
 
"""


def main():
    parser = argparse.ArgumentParser(description="Corridor generator")
    parser.add_argument("-f", "--from_nth", type=int, required=True)
    parser.add_argument("-t", "--to_nth", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_nth = args.from_nth
    to_nth = args.to_nth
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_nth < from_nth or from_nth < 2:
        sys.exit(-2)

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    problem_id = 1
    num_of_same_complexity_problems = 1
    for i in range(from_nth, to_nth+1, step):
        for j in range(num_of_same_complexity_problems):        
            random.seed(problem_id)
            instance_name = f"{out_folder}/{problem_id}.pddl"
            str_problem = generate_problem(name=f"corridor_{problem_id}", n_size=i)
            with open(instance_name, "w") as f_problem:
                f_problem.write(str_problem)
            translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                                  pddl_action="", id=problem_id)
            problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
