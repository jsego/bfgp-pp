#!/usr/bin/env python
import sys
import random
import argparse
# from tarski.io import PDDLReader


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
           f"  (:domain BLOCKS)\n" \
           f"  (:objects {get_objects(nblocks)})\n" \
           f"  (:init {get_init(nblocks)})\n" \
           f"  (:goal {get_goals(nblocks)}))\n"

def generate_domain():
    str_out = ""
    str_out += "(define (domain BLOCKS)\n"
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
    parser.add_argument("-e", "--extra_pointers", type=int, nargs='?', default=0, required=False)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_nth = args.from_nth
    to_nth = args.to_nth
    extra_pointers = args.extra_pointers
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_nth < from_nth:
        sys.exit(-2)

    # GENERATION
    vblocks = range(from_nth, to_nth+1)

    # DOMAIN
    str_domain = generate_domain()
    f_domain = open(out_folder + "domain.pddl", "w")
    f_domain.write(str_domain)
    f_domain.close()

    # INSTANCES
    random.seed(1007)

    num_of_same_complexity_problems = 1
    for i in range(from_nth, to_nth+1, step):
        for j in range(num_of_same_complexity_problems):
            # Problem name
            problem_name = "BLOCKS-" + str((i+step-from_nth)//step)

            str_problem = generate_problem(problem_name, vblocks[i-from_nth])

            f_problem = open(out_folder + str((i+step-from_nth)//step) + "-" + str(j) + ".pddl", "w")
            f_problem.write(str_problem)
            f_problem.close()

        # i += step
    """
    # TRANSLATION
    for i in range(from_nth, to_nth+1, step):
        for j in range(num_of_same_complexity_problems):
            reader = PDDLReader(raise_on_error=True)
            reader.parse_domain(out_folder + "domain.pddl")
            problem = reader.parse_instance(out_folder + str((i+step-from_nth)//step) + "-" + str(j) + ".pddl")
        # i += step
    """
    sys.exit(0)


if __name__ == "__main__":
    main()



