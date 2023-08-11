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
    folder: str
    eval_funcs: List
    extra_pointers: int = 0

    def get_command(self) -> str:
        return f"/bin/bash scripts/time_memory.sh ./main.bin -m synthesis -t assembler -l {self.lines} " \
               f"-f {self.folder} -e {' '.join(self.eval_funcs)} -s {self.extra_pointers}"

@dataclass(frozen=True)
class ValidationTask(Task):
    folder: str
    program: str
    extra_pointers: int = 0
    infinite_detection: str = "False"

    def get_command(self) -> str:
        return f"/bin/bash scripts/time_memory.sh ./main.bin -m validation-prog -t assembler -p {self.program} " \
               f"-f {self.folder} -s {self.extra_pointers} -inf {self.infinite_detection}"

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


def generate_instances(json_file: str):
    with open(json_file) as json_data:
        data = json.load(json_data)
    in_folder = data["in_folder"]
    out_folder = data["out_folder"]

    # Create all domain dirs
    for dom in data["domains"]:
        os.makedirs(f"{out_folder}/{dom['name']}", exist_ok=True)

    tasks = [GeneratorTask(domain=dom["name"], in_folder=in_folder, out_folder=out_folder, args=dom["args"])
             for dom in data['domains']]
    parallel_execution(tasks=tasks)

def experiment_1():
    """Tables 1 & 2 - Individual analysis of each evaluation function and domain"""
    lines = [4, 5, 7, 7, 7, 8, 11, 11, 15]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0, 0]
    problems = [f"domains/aij23/synthesis/{domain}/"
                for domain in ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor", "visitall"]]
    # f1="lc"; f2="nei"; f3="mri"; f4="dll"; f5="ed"; f6="ac"; f7="mnl"; f8="astar"; f9="wastar";
    eval_funcs = ["lc", "nei", "mri", "dll", "ed", "ac", "mnl", "astar", "wastar"]


    parallel_execution(tasks=[SynthesisTask(lines[idx], prob, [ef], extra_pointers[idx])
                              for ef in eval_funcs for idx, prob in enumerate(problems)])

def experiment_2():
    """Table 4 - Best combination of two evaluation functions"""
    lines = [4, 5, 7, 7, 7, 8, 11, 11]#, 15]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0]#, 0]
    problems = [f"domains/aij23/synthesis/{domain}/"
                for domain in ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor"]]#, "visitall"]]

    eval_funcs = ["lc ed", "ed lc", "nei ed", "ed nei", "mri ed", "ed mri", "mnl ed", "ed mnl"]

    parallel_execution(tasks=[SynthesisTask(lines[idx], prob, [ef], extra_pointers[idx])
                              for ef in eval_funcs for idx, prob in enumerate(problems)])


def experiment_3():
    """Table 3 - Validation of synthesized programs (better use the programs from the best combination of experiment_2)"""
    domains = ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor"]#, "visitall"]
    lines = [4, 5, 7, 7, 7, 8, 11, 11]#, 15]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0]#, 0]
    problems = [f"domains/aij23/validation/{domain}/" for domain in domains]
    programs = [f"experiments/aij23/synthesis/{domain}_{lines[idx]}_ed_mri.prog" for idx, domain in enumerate(domains)]
    parallel_execution(tasks=[ValidationTask(problem, programs[idx], extra_pointers[idx], inf_detection)
                              for inf_detection in ["False", "True"] for idx, problem in enumerate(problems)])


def main():
    #parser = argparse.ArgumentParser(description='Executing the BFGP over all listed GP problems with a given configuration')
    #parser.add_argument("-c", "--config_file", type=str, required=True)
    #args = parser.parse_args()
    #config_file = args.config_file

    generate_instances("scripts/aij23_synthesis.json")
    generate_instances("scripts/aij23_validation.json")

    #experiment_1()
    #experiment_2()
    #experiment_3()

if __name__ == "__main__":
    main()
