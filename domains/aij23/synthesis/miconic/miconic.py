#!/usr/bin/env python
import sys, random
from tarski.io import PDDLReader
import PDDLtranslator

#*****************#
# Functions declarations
#*****************#
def get_objects(num_floors,num_passengers):
   str_objects="\n    "

   # -- floors
   for i in range(1,num_floors+1):
      str_objects=str_objects+" floor"+str(i)
   str_objects=str_objects+" - floor\n    "


   # -- passengers
   for i in range(1,num_passengers+1):
      str_objects=str_objects+" pass"+str(i)
   str_objects=str_objects+" - passenger\n    "


   return(str_objects)
   

#*****************#
def get_init(num_floors,num_passengers):
   str_init="\n"
   str_init=str_init+"    (lift-at floor1)\n"

   for i in range(num_floors,0,-1):
   	for j in range(1,i):      
   		str_init=str_init+"    (above floor"+str(i)+" floor"+str(j)+")\n"

   for i in range(1,num_passengers+1):
      str_init=str_init+"    (origin pass" + str(i) + " floor" + str(str(random.randint(1,num_floors))) + ")\n"	
      str_init=str_init+"    (destin pass" + str(i) + " floor" + str(str(random.randint(1,num_floors))) + ")\n"
      
   return(str_init)

#*****************#
def get_goals(num_passengers):
   str_goal=""
   str_goal=str_goal+"\n  (and\n"

   for i in range(1,num_passengers+1):
      str_goal=str_goal+ "   (served pass"+str(i)+")\n"
            
   str_goal=str_goal+")"
   return(str_goal)
#*****************#

def generate_problem(name,floors,passengers):
   str_out = ""
   str_out += "(define (problem "+name+")\n"
   str_out += " (:domain MICONIC)\n"
   str_out += " (:objects "+ get_objects(floors,passengers)+")\n"
   str_out += " (:init " + get_init(floors,passengers)+")\n"
   str_out += " (:goal"+ get_goals(passengers)+"))\n"
   return str_out
#*****************#

def generate_domain():
   str_out = ""
   str_out += "(define (domain MICONIC)\n"
   str_out += " (:requirements :strips :typing)\n"
   str_out += " (:types passenger floor - object)\n"
   str_out += " (:predicates (origin ?p - passenger ?f - floor) (destin ?p - passenger ?f - floor) (above ?f1 ?f2 - floor) (boarded ?p - passenger) (served ?p - passenger) (lift-at ?f - floor))\n"
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


#*****************#
# MAIN
#*****************#
# Reading the command line arguments

def main():
   try:
      from_nth = int( sys.argv[1] )
      to_nth = int( sys.argv[2] )
      extra_pointers = int( sys.argv[3] )
      out_folder = sys.argv[4]
   except:
      print("Usage: ")
      print(sys.argv[ 0 ] + " <from_n> <to_n> <additional pointers> <outfolder>")
      print(sys.argv[ 0 ] + " 2 6 0 tmp/")
      sys.exit(-1)

   # GENERATION
   vfloors = range(from_nth,to_nth+1)
   vpassenger = range(from_nth,to_nth+1)

   # DOMAIN
   str_domain = generate_domain()
   f_domain=open( out_folder + "domain.pddl", "w" )
   f_domain.write( str_domain )
   f_domain.close()

   # INSTANCES
   random.seed(1007)
   for i in range(from_nth,to_nth+1):
      # Problem name
      problem_name = "MICONIC-" + str( i+1-from_nth )

      str_problem = generate_problem(problem_name,int(vfloors[i-from_nth]),int(1.5*vpassenger[i-from_nth]))
         
      f_problem = open( out_folder + str( i+1-from_nth ) + ".pddl","w")
      f_problem.write( str_problem )
      f_problem.close()

   # TRANSLATION
   for i in range(from_nth,to_nth+1):
      reader = PDDLReader(raise_on_error=True)
      reader.parse_domain(out_folder +"domain.pddl")

      problem = reader.parse_instance(out_folder + str( i+1-from_nth ) + ".pddl")
      PDDLtranslator.translate_domain(problem,extra_pointers,out_folder +"domain.txt")
      PDDLtranslator.translate_problem(problem,out_folder + str( i+1-from_nth ) + ".txt")

   sys.exit(0)


if __name__ == "__main__":
   main()



