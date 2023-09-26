import argparse
import json
import logging
import os
import multiprocessing as mp
from tqdm import tqdm
from typing import List
from dataclasses import dataclass
import subprocess
from abc import ABC, abstractmethod
import shutil


def execute_command(command: List[str], **kwargs) -> int:
    cwd = kwargs["cwd"] if "cwd" in kwargs else os.getcwd()
    output_dir = kwargs["output_dir"] if "output_dir" in kwargs else "."
    shell = kwargs["shell"] if "shell" in kwargs else False
    stdout = open(output_dir + "/" + kwargs["stdout"], 'w') if "stdout" in kwargs else None
    stderr = open(output_dir + "/" + kwargs["stderr"], 'w') if "stderr" in kwargs else None
    #logging.debug(f'Executing "{" ".join(map(str, command))}" on directory "{cwd}"')
    #print(f'Executing "{" ".join(map(str, command))}" on directory "{cwd}"')
    print(f'Executing "{command}" on directory "{cwd}"')
    if stdout:
        logging.debug(f'Standard output redirected to "{stdout.name}"')
    if stderr:
        logging.debug(f'Standard error redirected to "{stderr.name}"')

    ret_code = subprocess.call(command, cwd=cwd, stdout=stdout, stderr=stderr, shell=shell)

    if stdout:
        stdout.close()
    if stdout is not None and os.path.getsize(stdout.name) == 0:  # Delete error log if empty
        os.remove(stdout.name)
    if stderr:
        stderr.close()
    if stderr is not None and os.path.getsize(stderr.name) == 0:  # Delete error log if empty
        os.remove(stderr.name)

    return ret_code

class Task(ABC):
    @abstractmethod
    def get_command(self) -> str:
        pass

@dataclass(frozen=True)
class GeneratorTask(Task):
    domain: str
    in_folder: str
    out_folder: str
    args: str

    def get_command(self) -> str:
        return (f"PYTHONHASHSEED=0 python {self.in_folder}/{self.domain}.py {self.args} "
                f"-o {self.out_folder}/{self.domain}/")

@dataclass(frozen=True)
class SynthesisTask(Task):
    lines: int
    theory: str
    folder: str
    eval_funcs: List
    extra_pointers: int = 0

    def get_command(self) -> str:
        return f"/bin/bash scripts/time_memory.sh ./main.bin -m synthesis -t {self.theory} -l {self.lines} " \
               f"-f {self.folder} -e {' '.join(self.eval_funcs)} -s {self.extra_pointers} -pgp True"

@dataclass(frozen=True)
class ValidationTask(Task):
    folder: str
    theory: str
    program: str
    extra_pointers: int = 0
    infinite_detection: str = "False"

    def get_command(self) -> str:
        return f"/bin/bash scripts/time_memory.sh ./main.bin -m validation-prog -t {self.theory} -p {self.program} " \
               f"-f {self.folder} -s {self.extra_pointers} -inf {self.infinite_detection}"

@dataclass(frozen=True)
class TranslateTask(Task):
    domain_file: str
    instance_file: str
    dest_folder: str
    instance_id: int
    
    def get_command(self) -> str:
        return f"PYTHONHASHSEED=0 python preprocess/pddl_translator.py -d {self.domain_file} -i {self.instance_file} "\
               f"-o {self.dest_folder} -id {self.instance_id}"

def parallel_execution(tasks: List[Task]):
    print(f"Parallelizing {len(tasks)} tasks with {mp.cpu_count()} processors")
    pool = mp.Pool(mp.cpu_count())
    pbar = tqdm(total=len(tasks), bar_format='{percentage:3.0f}%|{bar:10}{r_bar}')

    def collect_result(result):
        pbar.update()

    def print_error(result):
        print(f"\rError callback: {result}\n")

    for task in tasks:
        pool.apply_async(execute_command,
                         kwds={'command': task.get_command(), 'shell': True},
                         callback=collect_result,
                         error_callback=print_error)
    pool.close()
    pool.join()
    pbar.close()


def translate_strips():
    strips_domains = ["gripper", "spanner", "visitall"]
    synthesis_folders = [f"domains/aiplan4eu/strips/synthesis/{domain}/" for domain in strips_domains]
    tasks = [TranslateTask(f"{folder}/domain.pddl", f"{folder}/p{idx:02}.pddl", folder, idx)
             for folder in synthesis_folders for idx in range(1,100) if os.path.exists(f"{folder}/p{idx:02}.pddl")]  # Up to 100 tasks
             
    validation_folders = [f"domains/aiplan4eu/strips/validation/{domain}/" for domain in strips_domains]
    for folder in validation_folders:
        dom = f"{folder}/domain.pddl"
        for subfolder in ["easy", "medium", "hard"]:
            for idx in range(1,100):
                ins_name = f"{folder}/{subfolder}/p{idx:02}.pddl"
                if not os.path.exists(ins_name):
                    break
                tasks.extend([TranslateTask(dom, ins_name, f"{folder}/{subfolder}", idx)])
            
    parallel_execution(tasks=tasks)


def generate_instances(json_file: str):
    with open(json_file) as json_data:
        data = json.load(json_data)
    in_folder = data["in_folder"]
    out_folder = data["out_folder"]

    # Remove old and create all new domain dirs
    for dom in data["domains"]:
        shutil.rmtree(f"{out_folder}/{dom['name']}", ignore_errors=True)
        os.makedirs(f"{out_folder}/{dom['name']}", exist_ok=True)

    tasks = [GeneratorTask(domain=dom["name"], in_folder=in_folder, out_folder=out_folder, args=dom["args"])
             for dom in data['domains']]
    parallel_execution(tasks=tasks)


def experiments_synthesis(json_file: str):
    with open(json_file) as json_data:
        data = json.load(json_data)

    tasks = []
    
    # STRIPS experiments
    strips_folder = data['strips_folder']
    assembler_eval_funcs = data['assembler_eval_funcs']
    cpp_eval_funcs = data['cpp_eval_funcs']

    for domain in data['strips_domains']:
        domain_name = domain['name']

        # STRIPS - assembler
        synthesis_assembler_args = domain['synthesis_args']['assembler']
        tasks.extend([SynthesisTask(synthesis_assembler_args['lines'], "assembler",
                                    f"{strips_folder}/synthesis/{domain_name}/", assembler_eval_funcs,
                                    synthesis_assembler_args['extra_pointers'])])

        # STRIPS - cpp
        synthesis_cpp_args = domain['synthesis_args']['cpp']
        tasks.extend([SynthesisTask(synthesis_cpp_args['lines'], "cpp", f"{strips_folder}/synthesis/{domain_name}/",
                                    cpp_eval_funcs, synthesis_cpp_args['extra_pointers'])])

    # Program Synthesis (PS) experiments
    ps_folder = data['program_synthesis_folder']
    for domain in data['program_synthesis_domains']:
        domain_name = domain['name']

        # PS - assembler
        synthesis_assembler_args = domain['synthesis_args']['assembler']
        tasks.extend([SynthesisTask(synthesis_assembler_args['lines'], "assembler",
                                    f"{ps_folder}/synthesis/{domain_name}/", assembler_eval_funcs,
                                    synthesis_assembler_args['extra_pointers'])])

        # PS - cpp
        synthesis_cpp_args = domain['synthesis_args']['cpp']
        tasks.extend([SynthesisTask(synthesis_cpp_args['lines'], "cpp", f"{ps_folder}/synthesis/{domain_name}/",
                                    cpp_eval_funcs, synthesis_cpp_args['extra_pointers'])])

    # Learning Action Models (LAM) experiments
    lam_folder = data['action_models_folder']
    lam_domains = data['action_models_domains']
    lam_eval_funcs = data['lam_eval_funcs']

    # LAM - STRIPS
    for domain in lam_domains['strips']:
        domain_name = domain['name']
        for act_name in domain['actions']:
            tasks.extend([SynthesisTask(1, 'actions_strips', f"{lam_folder}/synthesis/strips/{domain_name}/{act_name}/",
                                        lam_eval_funcs, 0)])

    # LAM - CELLULAR
    for domain in lam_domains['cellular']:
        tasks.extend([SynthesisTask(95, 'actions_cell', f"{lam_folder}/synthesis/cellular/{domain}/",
                                    lam_eval_funcs, 2)])

    # LAM - ADL
    for domain in lam_domains['adl']:
        domain_name = domain['name']
        for action in domain['actions']:
            act_name = action['name']
            act_lines = action['lines']
            tasks.extend([SynthesisTask(act_lines, 'actions_adl',
                                        f"{lam_folder}/synthesis/adl/{domain_name}/{act_name}/", lam_eval_funcs, 0)])


    # LAM - RAM
    for domain in lam_domains['ram']:
        tasks.extend([SynthesisTask(domain['lines'], 'actions_ram', f"{lam_folder}/synthesis/ram/{domain['name']}/",
                                    lam_eval_funcs, domain['extra_pointers'])])

    parallel_execution(tasks=tasks)


def experiment_validation(json_file: str):
    with open(json_file) as json_data:
        data = json.load(json_data)

    tasks = []

    solutions_folder = data['solutions_folder']
    assembler_eval_funcs = '_'.join(data['assembler_eval_funcs'])
    cpp_eval_funcs = '_'.join(data['cpp_eval_funcs'])

    # STRIPS experiments
    difficulty_folders = ["easy", "medium", "hard"]
    strips_folder = data['strips_folder']

    for domain in data['strips_domains']:
        domain_name = domain['name']
        validation_folder = f"{strips_folder}/validation/{domain_name}/"
        # STRIPS - assembler
        validation_assembler_args = domain['synthesis_args']['assembler']
        lines = validation_assembler_args['lines']
        extra_pointers = validation_assembler_args['extra_pointers']
        program = f"{solutions_folder}/strips/{domain_name}_{lines}_{assembler_eval_funcs}.prog"
        tasks.extend([ValidationTask(f"{validation_folder}/{difficulty}/", "assembler", program, extra_pointers)
                      for difficulty in difficulty_folders])

        # STRIPS - cpp
        validation_cpp_args = domain['synthesis_args']['cpp']
        lines = validation_cpp_args['lines']
        extra_pointers = validation_cpp_args['extra_pointers']
        program = f"{solutions_folder}/strips/{domain_name}_{lines}_{cpp_eval_funcs}.prog"
        tasks.extend([ValidationTask(f"{validation_folder}/{difficulty}/", "cpp", program, extra_pointers)
                      for difficulty in difficulty_folders])
   
    # Program Synthesis (PS) experiments
    ps_folder = data['program_synthesis_folder']
    for domain in data['program_synthesis_domains']:
        domain_name = domain['name']
        validation_folder = f"{ps_folder}/validation/{domain_name}/"

        # PS - assembler
        validation_assembler_args = domain['synthesis_args']['assembler']
        lines = validation_assembler_args['lines']
        extra_pointers = validation_assembler_args['extra_pointers']
        program = f"{solutions_folder}/program_synthesis/{domain_name}_{lines}_{assembler_eval_funcs}.prog"
        tasks.extend([ValidationTask(validation_folder, "assembler", program, extra_pointers)])

        # PS - cpp
        validation_cpp_args = domain['synthesis_args']['cpp']
        lines = validation_cpp_args['lines']
        extra_pointers = validation_cpp_args['extra_pointers']
        program = f"{solutions_folder}/program_synthesis/{domain_name}_{lines}_{cpp_eval_funcs}.prog"
        tasks.extend([ValidationTask(validation_folder, "cpp", program, extra_pointers)])


    # Learning Action Models (LAM) experiments
    lam_folder = data['action_models_folder']
    lam_domains = data['action_models_domains']
    lam_eval_funcs = '_'.join(data['lam_eval_funcs'])

    # LAM - STRIPS
    for domain in lam_domains['strips']:
        domain_name = domain['name']
        for act_name in domain['actions']:
            program = f"{solutions_folder}/action_models/strips/{domain_name}/{act_name}_1_{lam_eval_funcs}.prog"
            tasks.extend([
                ValidationTask(f"{lam_folder}/validation/strips/{domain_name}/{act_name}/", 'actions_strips', program)
            ])

    # LAM - CELLULAR
    for domain in lam_domains['cellular']:
        program = f"{solutions_folder}/action_models/cellular/{domain}_95_{lam_eval_funcs}.prog"
        tasks.extend([
            ValidationTask(f"{lam_folder}/validation/cellular/{domain}/", 'actions_cell', program, 2)
        ])

    # LAM - ADL
    for domain in lam_domains['adl']:
        domain_name = domain['name']
        for action in domain['actions']:
            act_name = action['name']
            act_lines = action['lines']
            program = f"{solutions_folder}/action_models/adl/{domain_name}/{act_name}_{act_lines}_{lam_eval_funcs}.prog"
            tasks.extend([
                ValidationTask(f"{lam_folder}/validation/adl/{domain_name}/{act_name}/", 'actions_adl', program)
            ])

    # LAM - RAM
    for domain in lam_domains['ram']:
        domain_name = domain['name']
        lines = domain['lines']
        extra_pointers = domain['extra_pointers']
        program = f"{solutions_folder}/action_models/ram/{domain_name}_{lines}_{lam_eval_funcs}.prog"
        tasks.extend([
            ValidationTask(f"{lam_folder}/validation/ram/{domain_name}/", 'actions_ram', program, extra_pointers)
        ])

    parallel_execution(tasks=tasks)


def experiment_repair():
    pass

def main():
    """Assumes all data has been generated"""
    #translate_strips()
    #experiments_synthesis('scripts/aiplan4eu.json')
    experiment_validation('scripts/aiplan4eu.json')
    #experiment_repair()
    

if __name__ == "__main__":
    main()
