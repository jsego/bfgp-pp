import sys
import random
import argparse
from pddl_translator import translate_pddl_to_ram

# ***************** #
# Functions declarations
# ***************** #
def get_objects(num_blocks: int):
    return " ".join([f"b{i}" for i in range(1, num_blocks+1)]) + " - object"

# ***************** #
def get_init(num_blocks):
    str_init="\n"
    str_init=str_init+"    (handempty)\n"

    vblocks = list(range(1, num_blocks+1))
    random.shuffle(vblocks)

    str_init=str_init+"    (clear b"+str(vblocks[0])+")\n"
    for i in range(0,len(vblocks)-1):
        if(random.randint(0,9)==0): # 10% chance of building a new tower
            str_init=str_init+"    (ontable b"+str(vblocks[i])+")\n"
            str_init=str_init+"    (clear b"+str(vblocks[i+1])+")\n"
        else:
            str_init=str_init+"    (on b"+str(vblocks[i])+" b"+str(vblocks[i+1])+")\n"

    str_init=str_init+"    (ontable b"+str(vblocks[-1])+")\n"
    return(str_init)


#*****************#
def get_goals(num_blocks):
    str_goal=""
    str_goal=str_goal+"\n  (and\n"

    for i in range(1,num_blocks+1):
        str_goal=str_goal+ "   (ontable b"+str(i)+")\n"

    str_goal=str_goal+")"
    return(str_goal)

def generate_problem(name,nblocks):
    return f"(define (problem {name})\n" \
           f"  (:domain blocks_ontable)\n" \
           f"  (:objects {get_objects(nblocks)})\n" \
           f"  (:init {get_init(nblocks)})\n" \
           f"  (:goal {get_goals(nblocks)}))\n"

def generate_domain():
    str_out = ""
    str_out += "(define (domain blocks_ontable)\n"
    str_out += " (:requirements :strips)\n"
    str_out += " (:predicates (on ?x ?y) (ontable ?x) (clear ?x) (handempty) (holding ?x))\n"
    str_out += "\n"
    str_out += " (:action pick-up\n"
    str_out += "    :parameters (?x)\n"
    str_out += "    :precondition (and (clear ?x) (ontable ?x) (handempty))\n"
    str_out += "    :effect\n"
    str_out += "      (and (not (ontable ?x))\n"
    str_out += "           (not (clear ?x))\n"
    str_out += "           (not (handempty))\n"
    str_out += "           (holding ?x)))\n"
    str_out += "\n"
    str_out += " (:action put-down\n"
    str_out += "    :parameters (?x)\n"
    str_out += "    :precondition (holding ?x)\n"
    str_out += "    :effect\n"
    str_out += "    	  (and (not (holding ?x))\n"
    str_out += "            (clear ?x)\n"
    str_out += "            (handempty)\n"
    str_out += "            (ontable ?x)))\n"
    str_out += "\n"
    str_out += " (:action stack\n"
    str_out += "    :parameters (?x ?y)\n"
    str_out += "    :precondition (and (holding ?x) (clear ?y))\n"
    str_out += "    :effect\n"
    str_out += "    	  (and (not (holding ?x))\n"
    str_out += "    	  	   (not (clear ?y))\n"
    str_out += "    	  	   (clear ?x)\n"
    str_out += "    	  	   (handempty)\n"
    str_out += "    	  	   (on ?x ?y)))\n"
    str_out += "\n"
    str_out += " (:action unstack\n"
    str_out += "    :parameters (?x ?y)\n"
    str_out += "    :precondition (and (on ?x ?y) (clear ?x) (handempty))\n"
    str_out += "    :effect\n"
    str_out += "    	  (and (holding ?x)\n"
    str_out += "            (clear ?y)\n"
    str_out += "            (not (clear ?x))\n"
    str_out += "            (not (handempty))\n"
    str_out += "            (not (on ?x ?y))))\n"
    str_out += ")"
    return str_out


#*****************#
# MAIN
#*****************#
# Reading the command line arguments

def main():
    parser = argparse.ArgumentParser(description="Blocks Ontable generator")
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
    vblocks = range(from_nth, to_nth+1)

    # DOMAIN
    domain_name = f"{out_folder}/domain.pddl"
    str_domain = generate_domain()
    with open(domain_name, "w") as f_domain:
        f_domain.write(str_domain)

    # INSTANCES
    random.seed(1007)

    problem_id = 1
    num_of_same_complexity_problems = 1
    for i in range(from_nth, to_nth+1, step):
        for j in range(num_of_same_complexity_problems):
            instance_name = f"{out_folder}/{problem_id}.pddl"
            str_problem = generate_problem(name=f"blocks_{problem_id}", nblocks=vblocks[i-from_nth])
            with open(instance_name, "w") as f_problem:
                f_problem.write(str_problem)
            translate_pddl_to_ram(domain_file=domain_name, instance_file=instance_name, output_dir=out_folder,
                                  pddl_action="", id=problem_id)
            problem_id += 1

    sys.exit(0)


if __name__ == "__main__":
    main()



