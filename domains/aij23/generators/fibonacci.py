#!/usr/bin/env python
# coding: utf-8

import sys
import argparse


def main():
    parser = argparse.ArgumentParser(description="Fibonacci generator")
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
    str_domain = "[DOMAIN]: FIBONACCI\n\n"
    str_domain += "[FUNCTIONS]:\n"
    str_domain += "vector(?o:object)\n"

    str_domain += "[ACTIONS]:\n"
    str_domain += "[ACTION]: vector_add(?x:object,?y:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "(vector(?x)+vector(?y))\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(vector(?x)+=vector(?y))\n"

    str_domain += "\n[ACTION]: vector_inc(?x:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "(vector(?x)+1)\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(vector(?x)+=1)\n"

    str_domain += "\n[ACTION]: vector_dec(?x:object)\n"
    str_domain += "[TYPE]: memory\n"
    str_domain += "[PRECONDITIONS]:\n"
    str_domain += "(vector(?x)-1)\n"
    str_domain += "[EFFECTS]:\n"
    str_domain += "(vector(?x)-=1)\n"

    f_domain = open(out_folder + "domain.txt", "w")
    f_domain.write(str_domain)
    f_domain.close()

    # INSTANCES
    for i in range(from_nth, to_nth + 1,step):
        # Problem name
        str_problem = "[INSTANCE]: fibo-" + str(i) + "\n"
        str_problem += "[DOMAIN]: FIBONACCI\n"        

        # Objects
        str_problem += "\n[OBJECTS]:\n"
        for j in range(i + 1):
            str_problem += "p" + str(j) + ":object\n"

        # Initial state
        str_problem += "\n[INIT]:\n"
        str_problem += "(vector(p0)=0)\n"
        str_problem += "(vector(p1)=1)\n"
        for j in range(2, i + 1):
            str_problem += "(vector(p" + str(j) + ")=0)\n"

        # Goal condition
        str_problem += "\n[GOAL]:\n"
        str_problem += "(vector(p0)=0)\n"
        str_problem += "(vector(p1)=1)\n"
        fn = 1
        fn1 = 0
        fn2 = 0
        for j in range(2, i + 1):
            fn2 = fn1
            fn1 = fn
            fn += fn2
            str_problem += "(vector(p" + str(j) + ")=" + str(fn) + ")\n"

        # print( str_problem )
        f_problem = open(out_folder + str((i + step - from_nth) // step) + ".txt", "w")
        f_problem.write(str_problem)
        f_problem.close()

        #i += step

    sys.exit(0)


if __name__ == "__main__":
    main()
