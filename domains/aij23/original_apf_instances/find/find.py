#!/usr/bin/env python
# coding: utf-8

import sys
import numpy as np
import argparse

def main():
    parser = argparse.ArgumentParser(description="Find generator")
    parser.add_argument("-f", "--from_size", type=int, required=True)
    parser.add_argument("-t", "--to_size", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    from_size = args.from_size
    to_size = args.to_size
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_size < from_size :
        sys.exit( -2 )

    # DOMAIN
    str_domain = "[DOMAIN]: FIND\n\n"
    str_domain += "[TYPES]:\n"
    str_domain += "[FUNCTIONS]:\n"
    str_domain += "vector(?o:object)\n"
    str_domain += "counter()\n"
    str_domain += "target()\n"

    str_domain += "[ACTIONS]:\n"
    str_domain += "\n[ACTION]: accumulate(?o:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "(vector(?o)=target())\n"
    str_domain += "(counter()+1)\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(counter()+=1)\n"    
    
    f_domain=open( out_folder + "domain.txt", "w" )
    f_domain.write( str_domain )
    f_domain.close()

    # INSTANCES
    np.random.seed(1007)

    i = from_size
    while i <= to_size :
        # Computing
        v = np.random.randint(i//2, size=i)	
        tg = np.random.randint(0,i-1)
        acc = sum( v == v[tg] )

        # Problem name
        str_problem = "[INSTANCE]: find-" + str(i) + "\n"
        str_problem += "[DOMAIN]: FIND\n"        

        # Objects
        str_problem += "\n[OBJECTS]:\n"
        for j in range(i):
            str_problem += "p"+str(j)+":object\n"


        # Initial state
        str_problem += "\n[INIT]:\n"
        str_problem += "(target()=" + str(v[tg]) + ")\n"
        str_problem += "(counter()=0)\n"
        for j in range(i):
            str_problem += "(vector(p"+str(j)+")=" + str(v[j]) + ")\n"

        # Goal condition
        str_problem += "\n[GOAL]:\n"
        str_problem += "(counter()=" + str(acc) + ")\n"
        #str_problem += "( target = " + str(tg) + " )\n"

        #print( str_problem )
        f_problem=open( out_folder + str( (i - from_size + step)//step ) + ".txt","w")
        f_problem.write( str_problem )
        f_problem.close()

        i += step

    sys.exit( 0 )


if __name__ == "__main__":
    main()
