import argparse
import logging
import os
import multiprocessing as mp
from tqdm import tqdm
from typing import List
from dataclasses import dataclass
import subprocess

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

@dataclass(frozen=True)
class Task:
    lines: int
    folder: str
    eval_funcs: List
    extra_pointers: int = 0

    def get_command(self) -> str:
        return f"/bin/bash scripts/time_memory.sh ./main.bin -m synthesis -t assembler -l {self.lines} " \
               f"-f {self.folder} -e {' '.join(self.eval_funcs)} -s {self.extra_pointers}"

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


def experiment_1():
    lines = [4, 5, 7, 7, 7, 8, 11, 10, 15]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0, 0]
    problems = [f"domains/aij23/synthesis/{domain}/"
                for domain in ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor", "visitall"]]
    # f1="lc"; f2="nei"; f3="mri"; f4="dll"; f5="ed"; f6="ac"; f7="mnl"; f8="astar"; f9="wastar";
    eval_funcs = ["lc", "nei", "mri", "dll", "ed", "ac", "mnl", "astar", "wastar"]


    parallel_execution(tasks=[Task(lines[idx], prob, [ef], extra_pointers[idx])
                              for ef in eval_funcs for idx, prob in enumerate(problems)])

def experiment_2():
    lines = [4, 5, 7, 7, 7, 8, 11, 10, 15]
    extra_pointers = [0, 0, 0, 1, 0, 0, 0, 0, 0]
    problems = [f"domains/aij23/synthesis/{domain}/"
                for domain in ["find", "triangular_sum", "reverse", "select", "fibonacci", "gripper", "sorting", "corridor", "visitall"]]

    eval_funcs = ["lc ed", "ed lc", "nei ed", "ed nei", "mri ed", "ed mri", "mnl ed", "ed mnl"]

    parallel_execution(tasks=[Task(lines[idx], prob, [ef], extra_pointers[idx])
                              for ef in eval_funcs for idx, prob in enumerate(problems)])

def main():
    #parser = argparse.ArgumentParser(description='Executing the BFGP over all listed GP problems with a given configuration')
    #parser.add_argument("-c", "--config_file", type=str, required=True)
    #args = parser.parse_args()
    #config_file = args.config_file

    #experiment_1()
    experiment_2()

if __name__ == "__main__":
    main()
