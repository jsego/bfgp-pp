#!/usr/bin/env python
# coding: utf-8

import sys
import random
import argparse


def main():
	parser = argparse.ArgumentParser(description="Corridor generator")
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
	str_domain = "[DOMAIN]: CORRIDOR\n\n"
	str_domain += "[FUNCTIONS]:\n"	
	str_domain += "at(?o:object)\n"
	str_domain += "goal_at(?o:object)\n"
	str_domain += "adjacent(?o1:object,?o2:object)\n\n"
		
	str_domain += "[ACTIONS]:\n"			
	str_domain += "[ACTION]: move(?o1:object,?o2:object)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(at(?o1)=1)\n"
	str_domain += "(at(?o2)=0)\n"
	str_domain += "(adjacent(?o1,?o2)=1)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at(?o1)=0)\n"
	str_domain += "(at(?o2)=1)\n"

	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close()
		

	random.seed(1007)

	# INSTANCES
	for i in range(from_nth,to_nth+1,step):
		# Problem name
		str_problem = "[INSTANCE]: corridor-" + str(i) + "\n"
		str_problem += "[DOMAIN]: CORRIDOR\n"		
		
		# Compute (pre)
		vi = random.randint(1,i)
		vgi = random.randint(1,i)
		while vgi == vi:
			vgi = random.randint(1, i)
			
		# Objects
		str_problem += "\n[OBJECTS]:\n"
		for j in range(1,i+1):
			str_problem += "l"+str(j)+":object\n"
		
		# Initial state
		str_problem += "\n[INIT]:\n"
		str_problem += "(at(l"+str(vi)+")=1)\n"
		str_problem += "(goal_at(l"+str(vgi)+")=1)\n"
		for j in range(1,i):
			str_problem += "(adjacent(l"+str(j)+",l"+str(j+1)+")=1)\n"
			str_problem += "(adjacent(l"+str(j+1)+",l"+str(j)+")=1)\n"
		
		# Compute		
		
		# Goal condition
		str_problem += "\n[GOAL]:\n"
		str_problem += "(at(l"+str(vgi)+")=1)\n"
		
		#print( str_problem )
		f_problem=open( out_folder + str( (i+step-from_nth)//step ) + ".txt","w")
		f_problem.write( str_problem )
		f_problem.close()
		
		#i += step
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
