![Build Status](https://github.com/jsego/bfgp-pp/actions/workflows/build.yml/badge.svg)
![Tests Status](https://github.com/jsego/bfgp-pp/actions/workflows/tests.yml/badge.svg)


# BFGP++

A framework based on [Best-First Generalized Planning](https://github.com/rleap-project/best-first-generalized-planning) where 
solutions are either assembly-like programs, or structured programs 
that are syntactically terminating.


## Installation

1. Prepare the virtual environment for PDDL preprocessing
```shell
python3 -m venv venv
source venv/bin/activate
pip install -r requirements.txt
pip install -e .
```
2. Compile the BFGP++ generalized planner
```shell
./scripts/compile.sh
```

## Running Example

### 1. Synthesis Mode
Synthesis of a generalized plan with `8` lines for Gripper domain:
```shell
./main.bin -m synthesis -l 8 -f domains/gripper/synthesis/ -o gripper -pgp True
```
The returned strategy, must pick a ball from room A, move to room B, 
drop the ball and get back to room A for the next ball, until all
balls have been moved. This is represented with the following planning program:
```text
0. for(ptr_ball_0++,6)
1. pick(ptr_ball_0,ptr_room_0,ptr_gripper_0)
2. inc(ptr_room_1)
3. move(ptr_room_0,ptr_room_1)
4. drop(ptr_ball_0,ptr_room_1,ptr_gripper_0)
5. move(ptr_room_1,ptr_room_0)
6. endfor(ptr_ball_0++,0)
7. end
```

### 2. Validation Mode
Validation of the planning program above in `easy`, `medium` and `hard` 
Gripper problems:

```shell
./main.bin -m validation-prog -p gripper.prog -f domains/gripper/validation/easy/
./main.bin -m validation-prog -p gripper.prog -f domains/gripper/validation/medium/
./main.bin -m validation-prog -p gripper.prog -f domains/gripper/validation/hard/ 
```
The results will be placed in `experiments/gripper/validation/` folder, where
all files should contain the input program, the number of input instance,
whether the `GOAL` has been achieved for all instances, and the execution time, 
e.g., the output for the `medium` difficulty command is:
```text
[INFO] Parsed domain. [0.000s]
[INFO] Generalized Domain created. [0.000s]
[INFO] Generalized Planning Problem created. [0.032s]
[INFO] Program loaded: [0.000s]
[INFO] Read program:
0. for(ptr_ball_0++,6)
1. pick(ptr_ball_0,ptr_room_0,ptr_gripper_0)
2. inc(ptr_room_1)
3. move(ptr_room_0,ptr_room_1)
4. drop(ptr_ball_0,ptr_room_1,ptr_gripper_0)
5. move(ptr_room_1,ptr_room_0)
6. endfor(ptr_ball_0++,0)
7. end

[INFO] Number of instances: 10
[INFO] GOAL ACHIEVED!
[INFO] Total time: [0.153s]
```

### 3. Repair Mode

It is similar to synthesis mode in that it synthesizes a solution for a
generalized planning problem, but requires an initial planning program 
which might be repaired, e.g., find the generalized plan above
given the following program, located in `domains/gripper/repair/gripper.prog`, 
where only the first loop is programmed:
```text
0. for(ptr_ball_0++,6)
1. empty
2. empty
3. empty
4. empty
5. empty
6. endfor(ptr_ball_0++,0)
7. end
```

The solution will be found much faster than in synthesis mode for this case.
Run the repair mode as follows:
```shell
./main.bin -m repair -f domains/gripper/synthesis/ -p domains/gripper/repair/gripper.prog -pgp True 
```

## Input Arguments
The framework has a helper to guide the user with the required input arguments 
for each running mode. Next we list some of the most important:
* Running modes (`-m`): `synthesis`, `validation-prog` and `repair` as explained above.
* Theories (`-t`): `cpp` (default) and `assembler`. These are target 
languages, each with its own set of instructions and constraints. Also, there are
4 target languages for synthesizing planning action models, i.e., 
  * `actions_strips`, generate STRIPS-like action models,
  * `actions_cellular`, generate 1D cellular automa transition functions,
  * `actions_adl`, generate ADL-like action models, limited to universally quantified effects,
  * `actions_ram`, generate transition functions as planning programs.
* Lines (`-l`): bounds the program size.
* Evaluation Functions (`-e`): they are structural-based or performance-based, 
can be combined and are used to enumerate the solution space in a 
particular order, e.g., 
  * `ed`, is the aggregation of Euclidean distances between the resulting states and 
  their corresponding goal conditions,
  * `lc`, counts the number of loops in a program,
  * `mri`, counts the number of repeated instructions,
  * ...

## References

* Segovia-Aguas, J., Celorrio, S. J., & Jonsson, A (2023a). [Generalized Planning as Heuristic Search: A new planning search-space that leverages pointers over objects](https://arxiv.org/pdf/2301.11087),
AIJ 2023 (under review).
* Segovia-Aguas, J., Ferrer-Mestres, J., & Celorrio, S. J. (2023b). [Synthesis of Procedural Models for Deterministic Transition Systems](https://arxiv.org/pdf/2307.14368.pdf),
ECAI 2023.
* Segovia-Aguas, J., Celorrio, S. J., & Jonsson, A (2022a). [Computing Programs for Generalized Planning as Heuristic Search](https://www.ijcai.org/proceedings/2022/0746.pdf),
IJCAI-ECAI 2022.
* Segovia-Aguas, J., Celorrio, S. J., Sebastiá, L., & Jonsson, A (2022b). [Scaling-up generalized planning as heuristic search with landmarks](https://ojs.aaai.org/index.php/SOCS/article/download/21765/21529),
SoCS 2022.
* Segovia-Aguas, J., E-Martín, Y., & Celorrio, S. J. (2022c). [Representation and Synthesis of C++ Programs for Generalized Planning](https://arxiv.org/pdf/2206.14480), 
Workshop in Generalization in Planning at IJCAI-ECAI 2022.
* Segovia-Aguas, J., Celorrio, S. J., & Jonsson, A (2021). [Generalized planning as heuristic search](https://ojs.aaai.org/index.php/ICAPS/article/download/16005/15816), ICAPS 2021.


