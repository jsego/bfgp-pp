import sys
import random
import argparse
from pddl_translator import translate_pddl_to_ram


def get_objects(n_size: int) -> str:
    return (" ".join([f"r{i}" for i in range(1, n_size+1)]) + " - row " +
            " ".join([f"c{i}" for i in range(1, n_size+1)]) + " - column")


def get_init(n_size: int) -> str:
    str_init = f"(at_row r1)(at_column c1)(visited r1 c1)\n"  # the agent always start in the bottom-left corner
    str_init += "    " + "    \n".join([f"(adjacent_rows r{i} r{i+1})" for i in range(1, n_size)])
    str_init += "\n    " + "    \n".join([f"(adjacent_columns c{i} c{i+1})" for i in range(1, n_size)])
    return str_init


def get_goals(n_size: int) -> str:
    return "\n".join([f"    (visited r{r} c{c})" for r in range(1, n_size+1) for c in range(1, n_size+1)])


def generate_problem(name: str, n_size: int):
    str_obj = get_objects(n_size)
    str_init = get_init(n_size)
    str_goal = get_goals(n_size)
    return f"(define (problem {name})\n" \
           f"  (:domain visitall)\n" \
           f"  (:objects {str_obj})\n" \
           f"  (:init {str_init})\n" \
           f"  (:goal (and \n{str_goal})))\n"


def generate_domain():
    return """(define (domain visitall)
 (:requirements :strips :typing :negative-preconditions)
 (:types row column)
 (:predicates 
    (visited ?r - row ?c - column)
    (at_row ?r - row)
    (at_column ?c - column)
    (adjacent_rows ?r1 ?r2 - row)
    (adjacent_columns ?c1 ?c2 - column))
     
 (:action move_up
    :parameters (?from ?to - row ?c - column)
    :precondition (and (adjacent_rows ?from ?to) (at_row ?from) (not (at_row ?to))(at_column ?c))
    :effect (and (not (at_row ?from)) (at_row ?to)(visited ?to ?c)))
    
 (:action move_down
    :parameters (?from ?to - row ?c - column)
    :precondition (and (adjacent_rows ?to ?from) (at_row ?from) (not (at_row ?to))(at_column ?c))
    :effect (and (not (at_row ?from)) (at_row ?to)(visited ?to ?c)))

 (:action move_right
    :parameters (?from ?to - column ?r - row)
    :precondition (and (adjacent_columns ?from ?to) (at_column ?from) (not (at_column ?to))(at_row ?r))
    :effect (and (not (at_column ?from)) (at_column ?to)(visited ?r ?to)))
    
 (:action move_left
    :parameters (?from ?to - column ?r - row)
    :precondition (and (adjacent_columns ?to ?from) (at_column ?from) (not (at_column ?to))(at_row ?r))
    :effect (and (not (at_column ?from)) (at_column ?to)(visited ?r ?to))))
 
"""


def main():
    parser = argparse.ArgumentParser(description="Visitall generator")
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

    random.seed(1007)

    # INSTANCES
    problem_id = 1
    num_of_same_complexity_problems = 1
    for i in range(from_nth, to_nth+1, step):
        for j in range(num_of_same_complexity_problems):
            instance_name = f"{out_folder}/{problem_id}.pddl"
            str_problem = generate_problem(name=f"visitall_{problem_id}", n_size=i)
            with open(instance_name, "w") as f_problem:
                f_problem.write(str_problem)
            translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                                  pddl_action="", id=problem_id)
            problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
