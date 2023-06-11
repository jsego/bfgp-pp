#!/usr/bin/env python
import sys, random
from tarski.io import PDDLReader
import PDDLtranslator
import argparse

#*****************#
# Functions declarations
#*****************#
def get_objects(num_nuts,num_spanners,num_locations):
    str_objects="\n"

    # -- man
    str_objects=str_objects+"     bob - man\n    "

    # -- spanner
    for i in range(1, num_spanners+1):
        str_objects=str_objects+" spanner"+str(i)
    str_objects=str_objects+" - spanner\n    "

    # -- nuts
    for i in range(1,num_nuts+1):
        str_objects=str_objects+" nut"+str(i)
    str_objects=str_objects+" - nut\n    "

    # -- locations
    #str_objects=str_objects+" shed"
    for i in range(1,num_locations+1):
        str_objects=str_objects+" location"+str(i)
    #str_objects=str_objects+" gate - location\n"
    str_objects = str_objects + " - location\n"

    return(str_objects)
   

#*****************#
def get_init(num_nuts,num_spanners,num_locations):
    str_init="\n"
    #str_init=str_init+"    (atm bob shed)\n"
    str_init=str_init+"    (atm bob location1)\n"

    for i in range(1,num_spanners+1):      
        str_init=str_init+"    (ats spanner"+str(i)+" location"+ str(random.randint(1,num_locations))+")\n"
        str_init=str_init+"    (useable spanner"+str(i)+")\n"

    for i in range(1,num_nuts+1):
        str_init=str_init+"    (loose nut"+str(i)+")\n"	
        #str_init=str_init+"    (atn nut"+str(i)+" gate)\n"
        str_init=str_init+"    (atn nut"+str(i)+" location"+str(num_locations)+")\n"

    #str_init=str_init+"    (link shed location1)\n"
    #str_init=str_init+"    (link location"+str(num_locations)+" gate)\n"

    for i in range(1,num_locations):
        str_init=str_init+"    (link location"+str(i)+" location"+str(i+1)+")\n"
      
    return(str_init)

#*****************#
def get_goals(num_nuts):
    str_goal=""
    str_goal=str_goal+"\n  (and\n"

    for i in range(1,num_nuts+1):
        str_goal=str_goal+ "   (tightened nut"+str(i)+")\n"
            
    str_goal=str_goal+")"
    return(str_goal)
#*****************#

def generate_problem(name,nuts,spanners,locations):
    str_out = ""
    str_out += "(define (problem "+name+")\n"
    str_out += " (:domain SPANNER)\n"
    str_out += " (:objects "+ get_objects(nuts,spanners,locations)+")\n"
    str_out += " (:init " + get_init(nuts,spanners,locations)+")\n"
    str_out += " (:goal"+ get_goals(nuts)+"))\n"
    return str_out
#*****************#

def generate_domain():
    str_out = ""
    str_out += "(define (domain SPANNER)\n"
    str_out += " (:requirements :typing :strips)\n"
    str_out += " (:types location man nut spanner - object)\n"
    str_out += "\n"
    str_out += " (:predicates (atm ?m - man ?l - location) (ats ?s - spanner ?l - location) (atn ?n - nut ?l - location) (carrying ?m - man ?s - spanner) (useable ?s - spanner) (link ?l1 - location ?l2 - location) (tightened ?n - nut) (loose ?n - nut))\n"
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
    str_out += "    :precondition (and (atm ?m ?l) (atn ?n ?l) (carrying ?m ?s) (useable ?s) (loose ?n))\n"
    str_out += "    :effect (and (not (loose ?n))(not (useable ?s)) (tightened ?n)))\n"
    str_out += ")"
    return str_out  


#*****************#
# MAIN
#*****************#
# Reading the command line arguments


def main():

    parser = argparse.ArgumentParser(description="Spanner generator")
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
    vnuts = range(from_nth,to_nth+1)
    vspanners = range(from_nth,to_nth+1)
    vlocations = range(from_nth,to_nth+1)

    # DOMAIN
    str_domain = generate_domain()
    f_domain=open( out_folder + "domain.pddl", "w" )
    f_domain.write( str_domain )
    f_domain.close()

    # INSTANCES
    random.seed(1007)
    for i in range(from_nth,to_nth+1,step):
        # Problem name
        problem_name = "SPANNER-" + str( i+1-from_nth )

        str_problem = generate_problem(problem_name,int(2*vnuts[i-from_nth]),int(2*vspanners[i-from_nth]),vlocations[i-from_nth])
         
        f_problem = open( out_folder + str( (i+step-from_nth)//step ) + ".pddl","w")
        f_problem.write( str_problem )
        f_problem.close()

        #i += step

    # TRANSLATION
    for i in range(from_nth,to_nth+1,step):
        reader = PDDLReader(raise_on_error=True)
        reader.parse_domain(out_folder +"domain.pddl")

        problem = reader.parse_instance(out_folder + str( (i+step-from_nth)//step ) + ".pddl")
        PDDLtranslator.translate_domain(problem,extra_pointers,out_folder +"domain.txt")
        PDDLtranslator.translate_problem(problem,out_folder + str( (i+step-from_nth)//step ) + ".txt")

        #i += step

    sys.exit(0)


if __name__ == "__main__":
   main()



