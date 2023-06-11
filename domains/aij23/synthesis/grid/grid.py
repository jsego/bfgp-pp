#!/usr/bin/env python
# coding: utf-8

import sys
import numpy as np
import random

def main():
	try:
		from_nth = int( sys.argv[1] )
		to_nth = int( sys.argv[2] )
		out_folder = sys.argv[3]
	except:
		print("Usage: ")
		print(sys.argv[ 0 ] + " <from_n> <to_n> <outfolder>")
		print(sys.argv[ 0 ] + " 2 6 tmp/")
		sys.exit(-1)
		
	# DOMAIN
	str_domain = "GRID\n\n"
	str_domain += "STATE DESCRIPTOR:\n"
	
	str_domain += "row:var_type\n"
	str_domain += "column:var_type\n"
	str_domain += "cell(row,column):pred_type\n"
	str_domain += "goal-xpos(row):pred_type\n"
	str_domain += "goal-ypos(column):pred_type\n"
	str_domain += "i:row\n"
	str_domain += "j:column\n"
		
	str_domain += "\nACTION: visit(x:row,y:column)\n"
	str_domain += "TYPE: memory\n"
	str_domain += "PRECONDITIONS:\n"
	str_domain += "( cell(x,y) = 0 )\n"
	str_domain += "EFFECTS:\n"
	str_domain += "( cell(x,y) = 1 )\n"

	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close
		

	random.seed(1007)
	
	# INSTANCES
	instance_id = 1
	for i in range(from_nth,to_nth+1):
		for j in range(4): # For every i-th sized grid, test one direction
			# Problem name
			str_problem = "GRID-" + str(i) + "\n"
				
			# Objects
			str_problem += "\nOBJECTS:\n"
			for p in range(i):
				str_problem += "r"+str(p)+":row\n"
				str_problem += "c"+str(p)+":column\n"		
			
			# Initial state
			str_problem += "\nINIT:\n"
			ir = random.randint(0,i-1)
			jc = random.randint(0,i-1)
			gr = random.randint(0,i-1)
			while ( j == 0 and gr > ir ) or ( j == 1 and gr < ir ) :
				gr = random.randint(0,i-1)
			gc = random.randint(0,i-1)
			while ( j == 2 and gc > jc ) or ( j == 3 and gc < jc ) :
				gc = random.randint(0,i-1)
			str_problem += "( i = " + str(ir) + " )\n"
			str_problem += "( j = " + str(jc) + " )\n"
			str_problem += "( goal-xpos(r" + str(gr) + ") = 1 )\n"
			str_problem += "( goal-ypos(c" + str(gc) + ") = 1 )\n"
			for r in range(i):
				for c in range(i):
					str_problem += "( cell(r"+str(r)+",c"+str(c)+") = 0 )\n"
			
			# Compute		
			
			# Goal condition
			str_problem += "\nGOAL:\n"
			for r in range(i):
				for c in range(i):
					res = 0
					if gr == r and gc == c :
						res = 1
					str_problem += "( cell(r"+str(r)+",c"+str(c)+") = " + str(res) + " )\n"
			
			#print( str_problem )
			f_problem=open( out_folder + str( instance_id ) + ".txt","w")
			f_problem.write( str_problem )
			f_problem.close()
			instance_id = instance_id + 1
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
