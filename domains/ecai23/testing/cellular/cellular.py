#!/usr/bin/env python

import sys
import argparse


def main():
    parser = argparse.ArgumentParser(description="Fibonacci generator")
    parser.add_argument("-n", "--number_of_cells", type=int, required=True)
    parser.add_argument("-r", "--rule", type=int, required=True)
    parser.add_argument("-s", "--steps", type=int, required=True)
    #parser.add_argument("-i", "--initial", type=str, required=True)
    parser.add_argument("-o", "--outfolder", type=str, required=True)

    args = parser.parse_args()

    ncells=args.number_of_cells
    rule=args.rule
    steps=args.steps
    #old_cells=args.initial
    mid_pos = (ncells+1)//2
    old_cells = [0] * (mid_pos-2) + [1,1,1] + [0] * (mid_pos-2)
    outfolder=args.outfolder

    f = open(outfolder+"domain.txt", "w")
    str_out=""
    str_out=str_out + "[DOMAIN]: CELLULAR\n"
    str_out=str_out + "[TYPES]:\n"
    str_out=str_out + "[FUNCTIONS]:\n"
    str_out=str_out + "cell(?c:object)\n"
    str_out=str_out + "[ACTIONS]:\n"
    f.write(str_out)
    f.close()

    pattern, pos = [], 0
    while len(pattern) != 8:
        pattern.append((rule>>pos)&1)
        pos += 1

    for idx, p in enumerate(pattern):
        print(idx, p)

    print(''.join((lambda x : str(x))(old_cells)))
    for n in range(1, steps+1):
        str_out=""
        new_cells = []
        for j in range(len(old_cells)):
            if j == 0:
                left = 0
            else:
                left = old_cells[j-1]
            center = old_cells[j]
            if j+1 == len(old_cells):
                right = 0
            else :
                right = old_cells[j+1]

            new_cells.append(pattern[4*left+2*center+right])
        print(''.join((lambda x : str(x))(new_cells)))
        
        problem_name=str(n)
        f = open(outfolder+problem_name+".txt", "w")        
        str_out = str_out + "[INSTANCE]: "+problem_name+"\n"
        str_out = str_out + "[DOMAIN]: CELLULAR\n"
        str_out = str_out + "[OBJECTS]: "
        for i in range(len(old_cells)):
            str_out = str_out + "c"+str(i)+":object "        
        str_out = str_out +"\n"
        str_out = str_out + "[INIT]: "
        for i in range(len(old_cells)):
            str_out = str_out + "(cell(c"+str(i)+")="+str(old_cells[i])+") "
        str_out = str_out +"\n"
        str_out = str_out + "[GOAL]: "
        for i in range(len(new_cells)):
            str_out = str_out + "(cell(c"+str(i)+")="+str(new_cells[i])+") "
        str_out = str_out +"\n"

        f.write(str_out)
        f.close()

        old_cells=new_cells
    sys.exit(0)

if __name__ == "__main__":
    main()


