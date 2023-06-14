#!/usr/bin/env python
# coding: utf-8

import sys
import random
import argparse

def main():
	parser = argparse.ArgumentParser(description="Visitall generator")
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
	str_domain = "[DOMAIN]: VISITALL\n\n"
	str_domain += "[TYPES]:\n"	
	str_domain += "row:object\n"
	str_domain += "column:object\n"
	str_domain += "[FUNCTIONS]:\n"		
	str_domain += "at_row(?r:row)\n"
	str_domain += "at_column(?c:column)\n"
	str_domain += "connected_rows(?r1:row,?r2:row)\n"
	str_domain += "connected_columns(?c1:column,?c2:column)\n"
	str_domain += "visited(?r:row,?c:column)\n"
	
	str_domain += "\n[ACTIONS]:\n"	
	str_domain += "[ACTION]: up(?r1:row,?r2:row)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(connected_rows(?r1,?r2)=1)\n"
	str_domain += "(at_row(?r1)=1)\n"
	str_domain += "(at_row(?r2)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at_row(?r1)=0)\n"
	str_domain += "(at_row(?r2)=1)\n"

	str_domain += "\n[ACTION]: down(?r1:row,?r2:row)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(connected_rows(?r2,?r1)=1)\n"
	str_domain += "(at_row(?r1)=1)\n"
	str_domain += "(at_row(?r2)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at_row(?r1)=0)\n"
	str_domain += "(at_row(?r2)=1)\n"

	str_domain += "\n[ACTION]: left(?c1:column,?c2:column)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(connected_columns(?c2,?c1)=1)\n"
	str_domain += "(at_column(?c1)=1)\n"
	str_domain += "(at_column(?c2)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at_column(?c1)=0)\n"
	str_domain += "(at_column(?c2)=1)\n"

	str_domain += "\n[ACTION]: right(?c1:column,?c2:column)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(connected_columns(?c1,?c2)=1)\n"
	str_domain += "(at_column(?c1)=1)\n"
	str_domain += "(at_column(?c2)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(at_column(?c1)=0)\n"
	str_domain += "(at_column(?c2)=1)\n"

	str_domain += "\n[ACTION]: visit(?r:row,?c:column)\n"
	str_domain += "[TYPE]: memory\n"
	str_domain += "[PRECONDITIONS]:\n"
	str_domain += "(at_row(?r)=1)\n"
	str_domain += "(at_column(?c)=1)\n"
	str_domain += "(visited(?r,?c)=0)\n"
	str_domain += "[EFFECTS]:\n"
	str_domain += "(visited(?r,?c)=1)\n"
	
	
	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close()
		

	random.seed(1007)
	
	# INSTANCES
	for i in range(from_nth,to_nth+1,step):
		# Problem name
		str_problem = "[INSTANCE]: Visitall-" + str(i) + "\n"		
		str_problem += "[DOMAIN]: VISITALL\n"
			
		# Objects
		str_problem += "\n[OBJECTS]:\n"
		for p in range(i):
			str_problem += "r"+str(p)+":row\n"
			str_problem += "c"+str(p)+":column\n"
		
		# Initial state
		str_problem += "\n[INIT]:\n"
		str_problem += "(at_row(r0)=1)\n"
		str_problem += "(at_column(c0)=1)\n"
		str_problem += "(visited(r0,c0)=1)\n"
		for p in range(1,i):
			str_problem += f"(connected_rows(r{p-1},r{p})=1)\n"
			str_problem += f"(connected_columns(c{p-1},c{p})=1)\n"
			
		# Compute		
		
		# Goal condition
		str_problem += "\n[GOAL]:\n"
		for r in range(i):
			for c in range(i):
				str_problem += f"(visited(r{r},c{c})=1)\n"
		
		#print( str_problem )
		f_problem=open( out_folder + str( (i+step-from_nth)//step ) + ".txt","w")
		f_problem.write( str_problem )
		f_problem.close()

		#i += step
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
