#!/usr/bin/env python
# coding: utf-8

import argparse
import sys
import numpy as np


def main():
    parser = argparse.ArgumentParser(description="Select Generator")
    parser.add_argument("-m", "--mode", type=str, choices=["synthesis", "validation"], required=True)
    parser.add_argument("-f", "--from_size", type=int, required=True)
    parser.add_argument("-t", "--to_size", type=int, required=True)
    parser.add_argument("-s", "--step", type=int, nargs='?', default=1, required=False)
    parser.add_argument("-o", "--out_folder", type=str, required=True)
    args = parser.parse_args()

    mode = args.mode
    from_size = args.from_size
    to_size = args.to_size
    step = args.step
    out_folder = args.out_folder

    if step < 1 or to_size < from_size:
        sys.exit(-2)

    # DOMAIN
    str_domain = "[DOMAIN]: SELECT\n\n"
    str_domain += "[FUNCTIONS]: \n"
    str_domain += "vector(?o:object)\n"
    str_domain += "selected(?o:object)\n"

    str_domain += "[ACTIONS]: \n"   
    str_domain += "[ACTION]: select(?x:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "(selected(?x)=0)\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(selected(?x)=1)\n"

    f_domain = open(out_folder + "domain.txt", "w")
    f_domain.write(str_domain)
    f_domain.close()

    # INSTANCES
    problem_id = 1
    seed = 0
    i = from_size

    # synthesis by default
    max_val = 100 if mode == "synthesis" else 1000000000

    while i <= to_size:
        # Computing
        np.random.seed(seed)  # new id for each problem
        v = np.random.randint(max_val, size=i)
        sol = np.argmin(v, axis=0)

        # Problem name
        str_problem = "[INSTANCE]: select-" + str(i) + "\n"
        str_problem = str_problem + "[DOMAIN]: SELECT\n"        

        # Objects
        str_problem += "\n[OBJECTS]:\n"
        for j in range(i):
            str_problem += "p" + str(j) + ":object\n"

        # Initial state
        str_problem += "\n[INIT]:\n"
        for j in range(i):
            str_problem += "(vector(p" + str(j) + ")=" + str(v[j]) + ")\n"
            str_problem += "(selected(p" + str(j) + ")=0)\n"

        # Goal condition
        str_problem += "\n[GOAL]:\n"
        for j in range(i):
            if j != sol:
                str_problem += "(selected(p" + str(j) + ")=0)\n"
            else:
                str_problem += "(selected(p" + str(sol)  + ")=1)\n"

        # print( str_problem )
        f_problem = open(f"{out_folder}/{problem_id}.txt", "w")
        f_problem.write(str_problem)
        f_problem.close()

        i += step
        problem_id += 1
        seed += 1

    sys.exit(0)


if __name__ == "__main__":
    main()
