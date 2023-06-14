#!/usr/bin/env python
# coding: utf-8

import sys

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
	str_domain = "SIEVE-OF-ERATOSTHENES\n\n"
	
	str_domain += "STATE DESCRIPTOR:\n"
	str_domain += "object:var_type\n"
	str_domain += "vector(object):pred_type\n"
	str_domain += "i:object\n"
	str_domain += "j:object\n"
	str_domain += "k:object\n"
		
	str_domain += "\nACTION: set-no-prime(x:object)\n"
	str_domain += "TYPE: memory\n"
	str_domain += "PRECONDITIONS:\n"
	str_domain += "EFFECTS:\n"
	str_domain += "( vector(x) = 0 )\n"
	
	#str_domain += "\nACTION: vector-set-1(x:object)\n"
	#str_domain += "TYPE: memory\n"
	#str_domain += "PRECONDITIONS:\n"
	#str_domain += "EFFECTS:\n"
	#str_domain += "( vector(x) = 1 )\n"
	
	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close
		
	# INSTANCES
	for i in range(from_nth,to_nth+1):
		# Problem name
		str_problem = "SIEVE-OF-ERATOSTHENES-" + str(i) + "\n"
		
		# Objects
		str_problem += "\nOBJECTS:\n"
		for j in range(0,i+1):
			str_problem += "p"+str(j)+":object\n"
		
		# Initial state
		str_problem += "\nINIT:\n"
		for j in range(0,i+1):
			str_problem += "( vector(p" + str(j) + ") = 1 )\n"
		
		# Compute
		v = [1]*(i+1)
		for j in range(2,i+1):
			if v[j] == 0:
				continue
			k = j+j
			while k < i+1 :
				v[k] = 0
				k += j
		
		# Goal condition
		str_problem += "\nGOAL:\n"
		for j in range(0,i+1):
			str_problem += "( vector(p" + str(j) + ") = " + str(v[j]) + " )\n"
		
		#print( str_problem )
		f_problem=open( out_folder + str( i+1-from_nth ) + ".txt","w")
		f_problem.write( str_problem )
		f_problem.close()
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
