import sys
import random
import argparse
from pddl_translator import translate_pddl_to_ram


def get_objects(num_satellites: int, num_instruments: int, num_modes: int, num_directions: int):
    str_objects = "\n    "

    # -- satellites
    for i in range(1, num_satellites+1):
        str_objects += " satellite"+str(i)
    str_objects += " - satellite\n    "

    # -- instruments
    for i in range(1, num_instruments+1):
        str_objects += " instrument"+str(i)
    str_objects += " - instrument\n    "

    # -- modes
    for i in range(1, num_modes+1):
        str_objects += " mode"+str(i)
    str_objects += " - mode\n    "

    # -- directions
    for i in range(1, num_directions+1):
        str_objects += " direction"+str(i)
    str_objects += " - direction\n    "

    return str_objects


def get_init(num_satellites: int, num_instruments: int, num_modes: int, num_directions: int):
    str_init = "\n"

    for i in range(1, num_satellites+1):
        str_init += f"   (power_avail satellite{i})\n"
        str_init += f"   (pointing satellite{i} direction{random.randint(1, num_directions)})\n"

    for i in range(1, num_instruments+1):
        str_init += f"   (on_board instrument{i} satellite{random.randint(1, num_satellites)})\n"
        str_init += f"   (calibration_target instrument{i} direction{random.randint(1, num_directions)})\n"
        for j in range(1, num_modes+1):
            if random.randint(0, 1) == 0:
                str_init += f"   (supports instrument{i} mode{j})\n"

    return str_init


def get_goals(num_directions: int, num_modes: int, str_init: str):
    str_goal = "\n  (and\n"

    for i in range(1, num_directions+1):
        r_mode = random.randint(1, num_modes)
        if(random.randint(0, 1) == 0) and f"mode{r_mode}" in str_init:
            str_goal += f"   (have_image direction{i} mode{r_mode})\n"

    str_goal += ")"
    return str_goal


def generate_problem(name: str, num_satellites: int, num_instruments: int, num_modes: int, num_directions: int):
    str_out = ""
    str_out += "(define (problem "+name+")\n"
    str_out += " (:domain SATELLITE)\n"
    str_out += " (:objects " + get_objects(num_satellites, num_instruments, num_modes, num_directions)+")\n"
    str_init = get_init(num_satellites, num_instruments, num_modes, num_directions)
    str_out += " (:init " + str_init + ")\n"
    str_out += " (:goal" + get_goals(num_directions, num_modes, str_init)+"))\n"
    return str_out


def generate_domain():
    str_out = ""
    str_out += "(define (domain SATELLITE)\n"
    str_out += " (:requirements :strips :typing)\n"
    str_out += " (:types satellite direction instrument mode - object)\n"
    str_out += " (:predicates (on_board ?i - instrument ?s - satellite) (supports ?i - instrument ?m - mode)\n"
    str_out += "   (pointing ?s - satellite ?d - direction) (power_avail ?s - satellite) (power_on ?i - instrument)\n"
    str_out += "   (calibrated ?i - instrument) (have_image ?d - direction ?m - mode)\n"
    str_out += "   (calibration_target ?i - instrument ?d - direction))\n"
    str_out += "\n"
    str_out += " (:action turn_to\n"
    str_out += "    :parameters (?s - satellite ?d_new - direction ?d_prev - direction)\n"
    str_out += "    :precondition (and (pointing ?s ?d_prev))\n"
    str_out += "    :effect (and  (pointing ?s ?d_new) (not (pointing ?s ?d_prev))))\n"
    str_out += "\n"
    str_out += " (:action switch_on\n"
    str_out += "    :parameters (?i - instrument ?s - satellite)\n"
    str_out += "    :precondition (and (on_board ?i ?s) (power_avail ?s))\n"
    str_out += "    :effect (and (power_on ?i) (not (calibrated ?i)) (not (power_avail ?s))))\n"
    str_out += "\n"
    str_out += " (:action switch_off\n"
    str_out += "    :parameters (?i - instrument ?s - satellite)\n"
    str_out += "    :precondition (and (on_board ?i ?s) (power_on ?i))\n"
    str_out += "    :effect (and (not (power_on ?i)) (power_avail ?s)))\n"
    str_out += "\n"
    str_out += " (:action calibrate\n"
    str_out += "    :parameters (?s - satellite ?i - instrument ?d - direction)\n"
    str_out += "    :precondition (and (on_board ?i ?s) (calibration_target ?i ?d) (pointing ?s ?d) (power_on ?i))\n"
    str_out += "    :effect (calibrated ?i))\n"
    str_out += "\n"
    str_out += " (:action take_image\n"
    str_out += "    :parameters (?s - satellite ?d - direction ?i - instrument ?m - mode)\n"
    str_out += "    :precondition (and (calibrated ?i)(on_board ?i ?s)(supports ?i ?m)(power_on ?i)(pointing ?s ?d))\n"
    str_out += "    :effect (have_image ?d ?m))\n"
    str_out += ")"
    return str_out


def main():
    parser = argparse.ArgumentParser(description="Satellite generator")
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

    v_satellites = range(from_nth, to_nth+1, step)
    v_instruments = range(2*from_nth, 2*to_nth+1, 2*step)
    v_modes = range(2*from_nth, 2*to_nth+1, 2*step)
    v_directions = range(4*from_nth, 4*to_nth+1, 4*step)

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    random.seed(1007)
    problem_id = 1
    for n_sat, n_ins, n_mod, n_dir in zip(v_satellites, v_instruments, v_modes, v_directions):
        instance_name = f"{out_folder}/{problem_id}.pddl"
        str_problem = generate_problem(name=f"satellite_{problem_id}",
                                       num_satellites=n_sat,
                                       num_instruments=n_ins,
                                       num_modes=n_mod,
                                       num_directions=n_dir)
        with open(instance_name, "w") as f_problem:
            f_problem.write(str_problem)
        translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                              pddl_action="", id=problem_id)
        problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
