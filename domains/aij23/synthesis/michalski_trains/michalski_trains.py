#!/usr/bin/env python
# coding: utf-8

import sys
import numpy as np
import random

def main():
	try:
		out_folder = sys.argv[1]
	except:
		print("Usage: ")
		print(sys.argv[ 0 ] + " <outfolder>")
		print(sys.argv[ 0 ] + " tmp/")
		sys.exit(-1)
		
	# DOMAIN
	str_domain = "MTRAINS\n\n"
	
	str_domain += "STATE DESCRIPTOR:\n"	
	str_domain += "train:var_type\n"
	str_domain += "car:var_type\n"
	str_domain += "shape:var_type\n"
	str_domain += "inumber:var_type\n"
	str_domain += "eastbound(train):pred_type\n"
	str_domain += "westbound(train):pred_type\n"
	str_domain += "hascar(train,car):pred_type\n"
	str_domain += "open(car):pred_type\n"
	str_domain += "closed(car):pred_type\n"
	str_domain += "short(car):pred_type\n"
	str_domain += "long(car):pred_type\n"
	str_domain += "double(car):pred_type\n"
	str_domain += "jagged(car):pred_type\n"
	str_domain += "cshape(car,shape):pred_type\n"
	str_domain += "infront1(train,car):pred_type\n"
	str_domain += "infrontn(car,car):pred_type\n"
	str_domain += "load(car,shape,inumber):pred_type\n"
	str_domain += "wheels(car,inumber):pred_type\n"
	str_domain += "greater(inumber,inumber):pred_type\n"
	str_domain += "t1:train\n"
	str_domain += "c1:car\n"
	str_domain += "c2:car\n"
	str_domain += "s1:shape\n"
	str_domain += "i1:inumber\n"
	str_domain += "i2:inumber\n"
		
	str_domain += "\nACTION: set-eastbound(t:train)\n"
	str_domain += "TYPE: memory\n"
	str_domain += "PRECONDITIONS:\n"
	str_domain += "( westbound(t) != 1 )\n"
	str_domain += "( eastbound(t) != 1 )\n"
	str_domain += "EFFECTS:\n"
	str_domain += "( eastbound(t) = 1 )\n"
		
	str_domain += "\nACTION: set-westbound(t:train)\n"
	str_domain += "TYPE: memory\n"
	str_domain += "PRECONDITIONS:\n"
	str_domain += "( westbound(t) != 1 )\n"
	str_domain += "( eastbound(t) != 1 )\n"
	str_domain += "EFFECTS:\n"
	str_domain += "( westbound(t) = 1 )\n"

	f_domain=open( out_folder + "domain.txt", "w" )
	f_domain.write( str_domain )
	f_domain.close
		
	# INSTANCES
	# Problem name
	str_problem = "MTRAINS-1\n"
			
	# Objects
	str_problem += "\nOBJECTS:\n"
	for train in range(5):
		str_problem += "east"+str(train+1)+":train\n"
		str_problem += "west"+str(train+6)+":train\n"		
		
	cars = [4,3,3,4,3,2,3,2,4,2]
	for t in range(10):
		for c in range(cars[t]):
			str_problem += "car"+str(t+1)+str(c+1)+":car\n"
	
	shapes = ["elipse","hexagon","rectangle","u_shaped","triangle","circle"]
	for s in shapes:
		str_problem += s+":shape\n"
	
	for i in range(3):
		str_problem += "i"+str(i+1)+":inumber\n"
	
	# Initial state
	str_problem += "\nINIT:\n"
	
	# has car
	for t in range(10):
		train = "west"+str(t+1)
		if t < 5 : 
			train = "east"+str(t+1)
		for c in range(cars[t]):
			str_problem += "( hascar("+train+",car"+str(t+1)+str(c+1)+") = 1 )\n"
	
	# short
	short = [21,22,51,93,82,12,32,72,43,41,94,91,53,23,42,14,71,44,62,101,31]
	for s in short :
		str_problem += "( short(car" + str(s) + ") = 1 )\n"
	
	# closed
	closed = [12,52,32,33,43,23,53,61,81]
	for c in closed : 	
		str_problem += "( closed(car" + str(c) + ") = 1 )\n"
		
	# long
	longt = [52,73,13,33,92,102,61,11,81]
	for l in longt:
		str_problem += "( long(car" + str(l) + ") = 1 )\n"
	
	# open
	opent = [21,22,13,51,93,82,72,11,41,94,91,42,14,71,44,62,101,102,31]
	for o in opent:
		str_problem += "( open(car"+ str(o) +") = 1 )\n"
	
	# cshape ["elipse","hexagon","rectangle","u_shaped","triangle","circle"]
	cshapes = [ (43,0), (71,2), (22,3), (41,3), (51,2), (72,3), (42,2),(61,2),(62,2),(23,2),(53,2),(73,2),(91,3),(92,2),(93,2),(102,2),(52,2),(31,2),(32,1),(44,2),(11,2),(13,2),(101,3),(94,3),(21,3),(81,2),(82,3),(14,2),(33,2),(12,2) ]
	for c in cshapes:
		str_problem += "( cshape(car"+str(c[0])+","+shapes[c[1]]+") = 1 )\n"
	
	# load
	loads = [(93,2,1),(81,2,1),(102,2,2),(23,5,2),(42,4,1),(32,4,1),(33,4,1),(92,2,1),(101,2,1),(51,4,1),(93,5,1),(91,5,1),(22,2,1),(53,5,1),(31,5,1),(11,2,3),(41,4,1),(12,4,1),(62,4,1),(72,4,1),(43,2,1),(71,5,1),(14,5,1),(61,5,3),(82,5,1),(13,1,1),(44,2,1),(21,4,1),(52,2,1)]
	for l in loads:
		str_problem += "( load(car"+str(l[0])+","+shapes[l[1]]+",i"+str(l[2])+") = 1 )\n"

	# wheels
	wheels = [ (72,2),(102,2),(31,2),(44,2),(11,2),(14,2),(91,2),(12,2),(32,2),(71,2),(51,2),(94,2),(21,2),(82,2),(101,2),(42,2),(61,2),(52,3),(23,2),(73,2),(13,3),(62,2),(53,2),(22,2),(81,3),(33,3),(41,2),(43,2),(93,2),(92,2) ]
	for w in wheels:
		str_problem += 	"( wheels(car"+str(w[0])+",i"+str(w[1])+") = 1 )\n"
		
	# infront1	
	for t in range(10):
		train = "west"+str(t+1)
		if t < 5 :
			train = "east"+str(t+1)
		str_problem += "( infront1("+train+",car"+str(t+1)+"1) = 1 )\n"
	
	# infrontn
	for t in range(10):
		for c in range(1,cars[t]):
			str_problem += "( infrontn(car"+str(t+1)+str(c)+",car"+str(t+1)+str(c+1)+") = 1 )\n"
	
	str_problem += "( double(car42) = 1 )\n"
	str_problem += "( double(car71) = 1 )\n"
	str_problem += "( double(car51) = 1 )\n"
	str_problem += "( jagged(car92) = 1 )\n"
	str_problem += "( jagged(car73) = 1 )\n"
	str_problem += "( greater(i3,i2) = 1 )\n"
	str_problem += "( greater(i2,i1) = 1 )\n"
	str_problem += "( greater(i3,i1) = 1 )\n"
	
	# Compute		
		
	# Goal condition
	str_problem += "\nGOAL:\n"
	
	str_problem += "( eastbound(east1) = 1 )\n"
	str_problem += "( eastbound(east2) = 1 )\n"
	str_problem += "( eastbound(east3) = 1 )\n"
	str_problem += "( eastbound(east4) = 1 )\n"
	str_problem += "( eastbound(east5) = 1 )\n"
	str_problem += "( westbound(west6) = 1 )\n"
	str_problem += "( westbound(west7) = 1 )\n"
	str_problem += "( westbound(west8) = 1 )\n"
	str_problem += "( westbound(west9) = 1 )\n"
	str_problem += "( westbound(west10) = 1 )\n"
		
	#print( str_problem )
	f_problem=open( out_folder + "1.txt","w")
	f_problem.write( str_problem )
	f_problem.close()
	
	sys.exit( 0 )
	
if __name__ == "__main__":
	main()
