#!/usr/bin/env python
import sys, random
from tarski.io import PDDLReader
import PDDLtranslator

#*****************#
# Functions declarations
#*****************#
def get_objects(num_satellites,num_instruments,num_modes,num_directions):
   str_objects="\n    "

   # -- satellites
   for i in range(1, num_satellites+1):
      str_objects=str_objects+" satellite"+str(i)
   str_objects=str_objects+" - satellite\n    "

   # -- instruments
   for i in range(1,num_instruments+1):
      str_objects=str_objects+" instrument"+str(i)
   str_objects=str_objects+" - instrument\n    "

   # -- modes
   for i in range(1,num_modes+1):
      str_objects=str_objects+" mode"+str(i)
   str_objects=str_objects+" - mode\n    "

   # -- directions
   for i in range(1,num_directions+1):
      str_objects=str_objects+" direction"+str(i)
   str_objects=str_objects+" - direction\n    "   

   return(str_objects)
   


#*****************#
def get_init(num_satellites,num_instruments,num_modes,num_directions):
   str_init="\n"

   for i in range(1, num_satellites+1):
      str_init=str_init+"   (power_avail satellite"+str(i) + ")\n"
      str_init=str_init+"   (pointing satellite"+str(i) + " direction"+str(random.randint(1,num_directions))+")\n"      


   for i in range(1,num_instruments+1):
   	str_init=str_init+"   (on_board instrument"+str(i) + " satellite"+str(random.randint(1,num_satellites))+")\n"
   	str_init=str_init+"   (calibration_target instrument"+str(i) + " direction"+str(random.randint(1,num_directions))+")\n"
   	for j in range(1,num_modes+1):
   		if(random.randint(0,1)==0):
   			str_init=str_init+"   (supports instrument"+str(i) + " mode"+str(j) + ")\n"

   return(str_init)

#*****************#
def get_goals(num_directions,num_modes,str_init):
   str_goal=""
   str_goal=str_goal+"\n  (and\n"

   for i in range(1,num_directions+1):
   	rmode = random.randint(1,num_modes)
   	if(random.randint(0,1)==0) and "mode"+str(rmode) in str_init:
   		str_goal=str_goal+ "   (have_image direction"+str(i)+" mode"+str(rmode)+")\n"
            
   str_goal=str_goal+")"
   return(str_goal)
#*****************#

def generate_problem(name,num_satellites,num_instruments,num_modes,num_directions):
   str_out = ""
   str_out += "(define (problem "+name+")\n"
   str_out += " (:domain SATELLITE)\n"
   str_out += " (:objects "+ get_objects(num_satellites,num_instruments,num_modes,num_directions)+")\n"
   str_init = get_init(num_satellites,num_instruments,num_modes,num_directions)
   str_out += " (:init " + str_init + ")\n"
   str_out += " (:goal"+ get_goals(num_directions,num_modes,str_init)+"))\n"
   return str_out

def generate_domain():
   str_out = ""
   str_out += "(define (domain SATELLITE)\n"
   str_out += " (:requirements :strips :typing)\n"
   str_out += " (:types satellite direction instrument mode - object)\n"
   str_out += " (:predicates (on_board ?i - instrument ?s - satellite) (supports ?i - instrument ?m - mode) (pointing ?s - satellite ?d - direction) (power_avail ?s - satellite) (power_on ?i - instrument) (calibrated ?i - instrument) (have_image ?d - direction ?m - mode) (calibration_target ?i - instrument ?d - direction))\n"
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
   str_out += "    :precondition (and (calibrated ?i) (on_board ?i ?s) (supports ?i ?m) (power_on ?i) (pointing ?s ?d))\n"
   str_out += "    :effect (have_image ?d ?m))\n"
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

   vsatellites = range(from_nth,to_nth+1)
   vinstruments = range(from_nth,to_nth+1)   
   vmodes = range(from_nth,to_nth+1)
   vdirections = range(from_nth,to_nth+1)

   # DOMAIN
   str_domain = generate_domain()

   f_domain=open( out_folder + "domain.pddl", "w" )
   f_domain.write( str_domain )
   f_domain.close()

   # INSTANCES
   random.seed(1007)
   for i in range(from_nth,to_nth+1):
      # Problem name
      problem_name = "SATELLITE-" + str( i+1-from_nth ) 
      str_problem = generate_problem(problem_name,vsatellites[i-from_nth],2*vinstruments[i-from_nth],2*vmodes[i-from_nth],4*vdirections[i-from_nth])
         
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



