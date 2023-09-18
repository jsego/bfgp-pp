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

def experiment_synthesis():	
    """Synthesis of Gripper, Spanner, Visitall and all Prog. Synth. and Learn. Act. Models benchmarks"""
    tasks = []

    # STRIPS benchmarks
    strips_domains = ["gripper", "spanner", "visitall"]
    strips_assembler_lines = [8, 14, 13]
    strips_cpp_lines = [8, 12, 13]
    strips_extra_ptrs = [0, 0, 0]
    strips_problems = [f"domains/aiplan4eu/strips/synthesis/{domain}/" for domain in strips_domains]
    assembler_eval_funcs = ["ed", "mri"]
    cpp_eval_funcs = ["ed", "ilc"]
    tasks.extend([SynthesisTask(strips_assembler_lines[idx], "assembler", prob, assembler_eval_funcs, strips_extra_ptrs[idx])
                  for idx, prob in enumerate(strips_problems)])
    
    tasks.extend([SynthesisTask(strips_cpp_lines[idx], "cpp", prob, cpp_eval_funcs, strips_extra_ptrs[idx])
                  for idx, prob in enumerate(strips_problems)])
    
    # Program Synthesis benchmarks
    ps_domains = ["find", "triangular_sum", "reverse", "select", "fibonacci", "sorting"]
    ps_assembler_lines = [4, 5, 7, 7, 7, 9]
    ps_cpp_lines = [4, 5, 7, 7, 7, 8]
    ps_extra_pointers = [0, 0, 0, 1, 0, 0]
    ps_problems = [f"domains/aiplan4eu/program_synthesis/synthesis/{domain}/" for domain in ps_domains]
    tasks.extend([SynthesisTask(ps_assembler_lines[idx], "assembler", prob, assembler_eval_funcs, ps_extra_pointers[idx]) 
                  for idx, prob in enumerate(ps_problems)])     
    tasks.extend([SynthesisTask(ps_cpp_lines[idx], "cpp", prob, cpp_eval_funcs, ps_extra_pointers[idx]) 
                  for idx, prob in enumerate(ps_problems)])     
                  
    # Learning Action Models
    lam_strips_domains = ["blocks/pick-up", "blocks/put-down", "blocks/stack", "blocks/unstack",
                          "driverlog/board-truck", "driverlog/disembark-truck", "driverlog/drive-truck",
                          "driverlog/load-truck", "driverlog/unload-truck", "driverlog/walk",
                          "ferry/board", "ferry/debark", "ferry/sail",
                          "grid/move", "grid/pickup", "grid/pickup-and-loose", "grid/putdown", "grid/unlock",
                          "gripper/pick", "gripper/drop", "gripper/move", "hanoi/move",
                          "miconic/board", "miconic/depart", "miconic/down", "miconic/up", "npuzzle/move",
                          "parking/move-car-to-car", "parking/move-car-to-curb",
                          "parking/move-curb-to-car", "parking/move-curb-to-curb",
                          "rovers/calibrate", "rovers/communicate_image_data", "rovers/communicate_rock_data",
                          "rovers/communicate_soil_data", "rovers/drop", "rovers/navigate", "rovers/sample_rock",
                          "rovers/sample_soil", "rovers/take_image",
                          "satellite/calibrate", "satellite/switch_off", "satellite/switch_on",
                          "satellite/take_image", "satellite/turn_to",
                          "transport/drive", "transport/drop", "transport/pick-up", "visitall/move"]
    lam_cellular_domains = ["rule30", "rule90", "rule110", "rule184"]
    lam_adl_domains = ["briefcase/move", "briefcase/put-in", "briefcase/take-out",
                       "elevators/down", "elevators/stop", "elevators/up",
                       "maintenance/workat"]
    lam_adl_lines = [15, 8, 4, 7, 18, 7, 9]
    lam_ram_domains = ["pancakes"]
    lam_ram_lines = [8]

    lam_strips_problems = [f"domains/aiplan4eu/action_models/synthesis/strips/{domain}/"
                           for domain in lam_strips_domains]
    lam_cellular_problems = [f"domains/aiplan4eu/action_models/synthesis/cellular/{domain}/"
                             for domain in lam_cellular_domains]
    lam_adl_problems = [f"domains/aiplan4eu/action_models/synthesis/adl/{domain}/"
                        for domain in lam_adl_domains]
    lam_ram_problems = [f"domains/aiplan4eu/action_models/synthesis/ram/{domain}/"
                        for domain in lam_ram_domains]

    tasks.extend([SynthesisTask(1, "actions_strips", prob, ["ilc", "mi", "cwed"], 0)
                  for idx, prob in enumerate(lam_strips_problems)])
    tasks.extend([SynthesisTask(95, "actions_cell", prob, ["ilc", "mi", "cwed"], 2)
                  for idx, prob in enumerate(lam_cellular_problems)])
    tasks.extend([SynthesisTask(lam_adl_lines[idx], "action_adl", prob, ["ilc", "mi", "cwed"], 0)
                  for idx, prob in enumerate(lam_adl_problems)])
    tasks.extend([SynthesisTask(lam_ram_lines[idx], "action_ram", prob, ["ilc", "mi", "cwed"], 0)
                  for idx, prob in enumerate(lam_ram_problems)])

    parallel_execution(tasks=tasks)

def experiments_synthesis_2(json_file: str):
    with open(json_file) as json_data:
        data = json.load(json_data)

    tasks = []
    
    # STRIPS experiments
    strips_folder = data['strips_folder']
    assembler_eval_funcs = data['assembler_eval_funcs']
    cpp_eval_funcs = data['cpp_eval_funcs']
    """
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
    """
    # Program Synthesis experiments
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

    # Learning Action Models experiments
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


def experiment_validation():
    # ToDo: make a JSON file with the data from Synthesis, and reuse the info for validation and repair experiments!
    """
    domains = ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor", "visitall"]
    lines = [4, 5, 7, 7, 7, 8, 9, 10, 13]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0, 0]
    problems = [f"domains/aij23/validation/{domain}/" for domain in domains]
    programs = [f"experiments/aij23/synthesis/{domain}_{lines[idx]}_ed_mri.prog" for idx, domain in enumerate(domains)]
    parallel_execution(tasks=[ValidationTask(problem, programs[idx], extra_pointers[idx], inf_detection)
                              for inf_detection in ["False", "True"] for idx, problem in enumerate(problems)])
    """
    pass

def experiment_repair():
    pass

def main():
    """Assumes all data has been generated"""
    #translate_strips()
    #experiment_synthesis()
    experiments_synthesis_2('scripts/synthesis_aiplan4eu.json')
    #experiment_validation()
    #experiment_repair()
    

if __name__ == "__main__":
    main()
