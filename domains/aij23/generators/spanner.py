import sys
import random
import argparse
from pddl_translator import translate_pddl_to_ram


def get_objects(num_nuts: int, num_spanners: int, num_locations: int):
    str_objects = "\n"

    # -- man
    str_objects += "     bob - man\n    "

    # -- spanner
    for i in range(1, num_spanners+1):
        str_objects += " spanner"+str(i)
    str_objects += " - spanner\n    "

    # -- nuts
    for i in range(1, num_nuts+1):
        str_objects += " nut"+str(i)
    str_objects += " - nut\n    "

    # -- locations
    for i in range(1, num_locations+1):
        str_objects += " location"+str(i)
    str_objects += " - location\n"

    return str_objects
   

def get_init(num_nuts: int, num_spanners: int, num_locations: int):
    str_init = "\n"
    str_init += "    (atm bob location1)\n"

    for i in range(1, num_spanners+1):
        str_init += f"    (ats spanner{i} location{random.randint(1, num_locations)})\n"
        str_init += f"    (usable spanner{i})\n"

    for i in range(1, num_nuts+1):
        str_init += f"    (loose nut{i})\n"
        str_init += f"    (atn nut{i} location{num_locations})\n"

    for i in range(1, num_locations):
        str_init += f"    (link location{i} location{i+1})\n"
      
    return str_init


def get_goals(num_nuts: int):
    str_goal = ""
    str_goal += "\n  (and\n"
    for i in range(1, num_nuts+1):
        str_goal += f"   (tightened nut{i})\n"
    str_goal += ")"

    return str_goal


def generate_problem(name: str, nuts: int, spanners: int, locations: int):
    str_out = ""
    str_out += f"(define (problem {name})\n"
    str_out += f" (:domain SPANNER)\n"
    str_out += f" (:objects {get_objects(nuts, spanners, locations)})\n"
    str_out += f" (:init {get_init(nuts, spanners, locations)})\n"
    str_out += f" (:goal {get_goals(nuts)}))\n"
    return str_out


def generate_domain():
    str_out = ""
    str_out += "(define (domain SPANNER)\n"
    str_out += " (:requirements :typing :strips)\n"
    str_out += " (:types location man nut spanner - object)\n"
    str_out += "\n"
    str_out += " (:predicates\n"
    str_out += "   (atm ?m - man ?l - location)\n"
    str_out += "   (ats ?s - spanner ?l - location)\n"
    str_out += "   (atn ?n - nut ?l - location)\n"
    str_out += "   (carrying ?m - man ?s - spanner)\n"
    str_out += "   (usable ?s - spanner)\n"
    str_out += "   (link ?l1 - location ?l2 - location)\n"
    str_out += "   (tightened ?n - nut)\n"
    str_out += "   (loose ?n - nut))\n"
    str_out += "\n"   
    str_out += " (:action walk\n" 
    str_out += "    :parameters (?start - location ?end - location ?m - man)\n"
    str_out += "    :precondition (and (atm ?m ?start) (link ?start ?end))\n"
    str_out += "    :effect (and (not (atm ?m ?start)) (atm ?m ?end)))\n"
    str_out += "\n"   
    str_out += " (:action pickup_spanner\n" 
    str_out += "    :parameters (?l - location ?s - spanner ?m - man)\n"
    str_out += "    :precondition (and (atm ?m ?l) (ats ?s ?l))\n"
    str_out += "    :effect (and (not (ats ?s ?l)) (carrying ?m ?s)))\n"
    str_out += "\n"   
    str_out += " (:action tighten_nut\n"
    str_out += "    :parameters (?l - location ?s - spanner ?m - man ?n - nut)\n"
    str_out += "    :precondition (and (atm ?m ?l) (atn ?n ?l) (carrying ?m ?s) (usable ?s) (loose ?n))\n"
    str_out += "    :effect (and (not (loose ?n))(not (usable ?s)) (tightened ?n)))\n"
    str_out += ")"
    return str_out  


def main():

    parser = argparse.ArgumentParser(description="Spanner generator")
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

    # GENERATION
    v_nuts = range(from_nth, to_nth+1)
    v_spanners = range(from_nth, to_nth+1)
    v_locations = range(from_nth, to_nth+1)

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
        nuts = int(2*v_nuts[i-from_nth])
        spanners = int(2*v_spanners[i-from_nth])
        locations = v_locations[i-from_nth]
        str_problem = generate_problem(f"spanner_{problem_id}", nuts, spanners, locations)
        with open(instance_name, "w") as f_problem:
            f_problem.write(str_problem)

        translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                              pddl_action="", id=problem_id)
        problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
