echo 'SYNTHESIS'
echo 'Generating Corridor instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/corridor/corridor.py -f 2 -t 11 -o domains/aij23/synthesis/corridor/
echo 'Generating Fibonacci instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/fibonacci/fibonacci.py -f 2 -t 11 -o domains/aij23/synthesis/fibonacci/
echo 'Generating Find instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/find/find.py -f 2 -t 11 -o domains/aij23/synthesis/find/
echo 'Generating Gripper instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/gripper/gripper.py -f 2 -t 11 -o domains/aij23/synthesis/gripper/
echo 'Generating Reverse instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/reverse/reverse.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/reverse/
echo 'Generating Select instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/select/select.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/select/
echo 'Generating Sorting instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/sorting/sorting.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/sorting/
echo 'Generating Triangular Sum instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/triangular_sum/triangular_sum.py -f 2 -t 11 -o domains/aij23/synthesis/triangular_sum/
echo 'Generating Visitall instances...'
PYTHONHASHSEED=0 python domains/aij23/synthesis/visitall/visitall.py -f 2 -t 11 -o domains/aij23/synthesis/visitall/

#echo 'VALIDATION'
#ToDo

