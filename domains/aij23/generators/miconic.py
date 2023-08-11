import sys
import random
import argparse
from pddl_translator import translate_pddl_to_ram


def get_objects(num_floors: int, num_passengers: int):
    str_objects = "\n    "

    # -- floors
    for i in range(1, num_floors+1):
        str_objects += f" floor{i}"
    str_objects += " - floor\n    "

    # -- passengers
    for i in range(1, num_passengers+1):
        str_objects += f" pass{i}"
    str_objects += " - passenger\n    "

    return str_objects


def get_init(num_floors: int, num_passengers: int):
    str_init = "\n    (lift-at floor1)\n"

    for i in range(num_floors, 0, -1):
        for j in range(1, i):
            str_init += "    (above floor"+str(i)+" floor"+str(j)+")\n"

    for i in range(1, num_passengers+1):
        str_init += "    (origin pass" + str(i) + " floor" + str(str(random.randint(1, num_floors))) + ")\n"
        str_init += "    (destin pass" + str(i) + " floor" + str(str(random.randint(1, num_floors))) + ")\n"

    return str_init


def get_goals(num_passengers: int):
    str_goal = "\n  (and\n"
    for i in range(1, num_passengers+1):
        str_goal += "   (served pass"+str(i)+")\n"
    str_goal += ")"
    return str_goal


def generate_problem(name: str, floors: int, passengers: int):
    str_out = ""
    str_out += "(define (problem "+name+")\n"
    str_out += " (:domain MICONIC)\n"
    str_out += " (:objects "+ get_objects(floors, passengers)+")\n"
    str_out += " (:init " + get_init(floors, passengers)+")\n"
    str_out += " (:goal"+ get_goals(passengers)+"))\n"
    return str_out


def generate_domain():
    str_out = ""
    str_out += "(define (domain MICONIC)\n"
    str_out += " (:requirements :strips :typing)\n"
    str_out += " (:types passenger floor - object)\n"
    str_out += " (:predicates (origin ?p - passenger ?f - floor) (destin ?p - passenger ?f - floor)\n"
    str_out += "   (above ?f1 ?f2 - floor) (boarded ?p - passenger) (served ?p - passenger) (lift-at ?f - floor))\n"
    str_out += "\n"
    str_out += " (:action board\n"
    str_out += "    :parameters (?p - passenger ?f - floor)\n"
    str_out += "    :precondition (and (lift-at ?f) (origin ?p ?f))\n"
    str_out += "    :effect (boarded ?p))\n"
    str_out += "\n"
    str_out += " (:action depart\n"
    str_out += "    :parameters (?p - passenger ?f - floor)\n"
    str_out += "    :precondition (and (lift-at ?f) (destin ?p ?f) (boarded ?p))\n"
    str_out += "    :effect (and (not (boarded ?p))(served ?p)))\n"
    str_out += "\n"
    str_out += " (:action up\n"
    str_out += "    :parameters (?f1 ?f2 - floor)\n"
    str_out += "    :precondition (and (lift-at ?f1) (above ?f2 ?f1))\n"
    str_out += "    :effect (and (lift-at ?f2) (not (lift-at ?f1))))\n"
    str_out += "\n"
    str_out += " (:action down\n"
    str_out += "    :parameters (?f1 ?f2 - floor)\n"
    str_out += "    :precondition (and (lift-at ?f1) (above ?f1 ?f2))\n"
    str_out += "    :effect (and (lift-at ?f2) (not (lift-at ?f1))))\n"
    str_out += ")"
    return str_out


def main():
    parser = argparse.ArgumentParser(description="Miconic generator")
    parser.add_argument("-f", "--from_nth", type=int, required=True)
    parser.add_argument("-t", "--to_nth", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_nth = args.from_nth
    to_nth = args.to_nth
    step = args.step
    out_folder = args.out_folder

    # GENERATION
    v_floors = range(from_nth, to_nth+1)
    v_passenger = range(from_nth, to_nth+1)

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    random.seed(1007)

    problem_id = 1
    for i in range(from_nth, to_nth+1, step):
        instance_name = f"{out_folder}/{problem_id}.pddl"
        str_problem = generate_problem(f"miconic_{problem_id}", int(v_floors[i-from_nth]), int(1.5*v_passenger[i-from_nth]))
        with open(instance_name, "w") as f_problem:
            f_problem.write(str_problem)
        translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                              pddl_action="", id=problem_id)
        problem_id += 1


    sys.exit(0)


if __name__ == "__main__":
   main()



