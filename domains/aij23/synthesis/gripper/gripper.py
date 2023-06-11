#!/usr/bin/env python
# coding: utf-8

import sys
import argparse

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
	str_domain = "[DOMAIN]: Gripper\n\n"
	str_domain += "[TYPES]:\n"
	str_domain += "room:object\n"
	str_domain += "ball:object\n"
	str_domain += "gripper:object\n\n"

	str_domain += "[CONSTANTS]:\n"
	str_domain += "left:gripper\n"
	str_domain += "right:gripper\n"
	str_domain += "roomA:room\n"
	str_domain += "roomB:room\n\n"

	str_domain += "[FUNCTIONS]:\n"	
	str_domain += "at_robby(?r:room)\n"
	str_domain += "at(?b:ball,?r:room)\n"
	str_domain += "free(?g:gripper)\n"
	str_domain += "carry(?b:ball,?g:gripper)\n\n"
	
	str_domain += "[ACTIONS]:\n"		
	str_domain += "[ACTION]: move(?r1:room,?r2:room)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(at_robby(?r1)=1)\n"
	str_domain += "(at_robby(?r2)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at_robby(?r1)=0)\n"
	str_domain += "(at_robby(?r2)=1)\n"

	str_domain += "\n[ACTION]: pick(?b:ball,?r:room,?g:gripper)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(at(?b,?r)=1)\n"
	str_domain += "(at_robby(?r)=1)\n"
	str_domain += "(free(?g)=1)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(carry(?b,?g)=1)\n"
	str_domain += "(at(?b,?r)=0)\n"
	str_domain += "(free(?g)=0)\n"
	
	str_domain += "\n[ACTION]: drop(?b:ball,?r:room,?g:gripper)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(carry(?b,?g)=1)\n"
	str_domain += "(at_robby(?r)=1)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(carry(?b,?g)=0)\n"
	str_domain += "(at(?b,?r)=1)\n"
	str_domain += "(free(?g)=1)\n"
		
	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close()
			
	# INSTANCES
	for i in range(from_nth,to_nth+1,step):
		# Problem name
		str_problem = "[INSTANCE]: gripper-" + str(i) + "\n"		
		str_problem += "[DOMAIN]: Gripper\n"
		
		# Objects
		str_problem += "\n[OBJECTS]:\n"
		for j in range(i):
			str_problem += "ball"+str(j+1)+":ball\n"
				
		# Initial state
		str_problem += "\n[INIT]:\n"
		str_problem += "(at_robby(roomA)=1)\n"
		for j in range(i):
			str_problem += "(at(ball"+str(j+1)+",roomA)=1)\n"
		str_problem += "(free(left)=1)\n"
		str_problem += "(free(right)=1)\n"
		
		# Compute		
		
		# Goal condition
		str_problem += "\n[GOAL]:\n"
		for j in range(i):
			str_problem += "(at(ball"+str(j+1)+",roomB)=1)\n"
		
		#print( str_problem )
		f_problem=open( out_folder + str( (i+step-from_nth)//step ) + ".txt","w")
		f_problem.write( str_problem )
		f_problem.close()
		#i += step
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
