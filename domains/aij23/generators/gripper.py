import sys
import argparse
from pddl_translator import translate_pddl_to_ram


def get_objects(n_balls: int):
    return " ".join([f"b{i}" for i in range(1, 1+n_balls)]) + " - ball"


def get_init(n_balls: int):
    return ("\n    ".join([f"(at b{i} rooma)" for i in range(1, 1+n_balls)]) +
            "\n    (at_robby rooma)\n    (free left)\n    (free right)")


def get_goals(n_balls: int):
    return "\n    ".join([f"(at b{i} roomb)" for i in range(1, 1+n_balls)])


def generate_problem(name, n_balls):
    return f"(define (problem {name})\n" \
           f"  (:domain Gripper)\n" \
           f"  (:objects {get_objects(n_balls)})\n" \
           f"  (:init {get_init(n_balls)})\n" \
           f"  (:goal (and {get_goals(n_balls)})))\n"


def generate_domain():
    return """(define (domain Gripper)
   (:requirements :typing :strips)
   (:types room gripper ball - object)
   (:constants left right - gripper rooma roomb - room)
   (:predicates
       (at_robby ?r - room)
       (at ?b - ball ?r - room)
       (free ?g - gripper)
       (carry ?b - ball ?g - gripper))

   (:action move
       :parameters (?from - room ?to - room)
       :precondition (and (at_robby ?from))
       :effect (and (at_robby ?to)
                    (not (at_robby ?from))))

   (:action pick
       :parameters (?b - ball ?r - room ?g - gripper)
       :precondition (and (at ?b ?r)
                          (at_robby ?r)
                          (free ?g))
       :effect (and (carry ?b ?g)
                    (not (at ?b ?r))
                    (not (free ?g))))

   (:action drop
       :parameters (?b - ball ?r - room ?g - gripper)
       :precondition (and (carry ?b ?g)
                          (at_robby ?r))
       :effect (and (at ?b ?r)
                    (free ?g)
                    (not (carry ?b ?g)))))
"""


def main():
    parser = argparse.ArgumentParser(description="Gripper generator")
    parser.add_argument("-f", "--from_nth", type=int, required=True)
    parser.add_argument("-t", "--to_nth", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_nth = args.from_nth
    to_nth = args.to_nth
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_nth < from_nth:
        sys.exit(-2)

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    problem_id = 1
    for i in range(from_nth, to_nth+1, step):
        instance_name = f"{out_folder}/{problem_id}.pddl"
        str_problem = generate_problem(name=f"gripper_{problem_id}", n_balls=i)
        with open(instance_name, "w") as f_problem:
            f_problem.write(str_problem)
        translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                              pddl_action="", id=problem_id)
        problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
