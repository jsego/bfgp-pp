echo 'SYNTHESIS'
echo 'Generating Corridor instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/corridor.py -f 2 -t 11 -o domains/aij23/synthesis/corridor/
echo 'Generating Fibonacci instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/fibonacci.py -f 2 -t 11 -o domains/aij23/synthesis/fibonacci/
echo 'Generating Find instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/find.py -f 2 -t 11 -o domains/aij23/synthesis/find/
echo 'Generating Gripper instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/gripper.py -f 2 -t 11 -o domains/aij23/synthesis/gripper/
echo 'Generating Reverse instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/reverse.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/reverse/
echo 'Generating Select instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/select.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/select/
echo 'Generating Sorting instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/sorting.py -m synthesis -f 2 -t 11 -o domains/aij23/synthesis/sorting/
echo 'Generating Triangular Sum instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/triangular_sum.py -f 2 -t 11 -o domains/aij23/synthesis/triangular_sum/
echo 'Generating Visitall instances...'
PYTHONHASHSEED=0 python domains/aij23/generators/visitall.py -f 2 -t 11 -o domains/aij23/synthesis/visitall/

