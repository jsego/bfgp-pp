# Blocks
rm -rf domains/ecai23/training/strips/blocks/pick-up/ \
       domains/ecai23/training/strips/blocks/put-down/ \
       domains/ecai23/training/strips/blocks/stack/ \
       domains/ecai23/training/strips/blocks/unstack/ \
       domains/ecai23/training/strips/blocks/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/blocks/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/blocks/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/blocks/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/blocks/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/blocks/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/blocks/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/blocks/

# Driverlog
rm -rf domains/ecai23/training/strips/driverlog/load-truck/ \
       domains/ecai23/training/strips/driverlog/disembark-truck/ \
       domains/ecai23/training/strips/driverlog/unload-truck/ \
       domains/ecai23/training/strips/driverlog/board-truck/ \
       domains/ecai23/training/strips/driverlog/drive-truck/ \
       domains/ecai23/training/strips/driverlog/walk/ \
       domains/ecai23/training/strips/driverlog/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/driverlog/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/driverlog/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/driverlog/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/driverlog/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/driverlog/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/driverlog/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/driverlog/

# Ferry
rm -rf domains/ecai23/training/strips/ferry/sail/ \
       domains/ecai23/training/strips/ferry/board/ \
       domains/ecai23/training/strips/ferry/debark/ \
       domains/ecai23/training/strips/ferry/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/ferry/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/ferry/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/ferry/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/ferry/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/ferry/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/ferry/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/ferry/

# Grid
rm -rf domains/ecai23/training/strips/grid/pickup/ \
       domains/ecai23/training/strips/grid/putdown/ \
       domains/ecai23/training/strips/grid/move/ \
       domains/ecai23/training/strips/grid/pickup-and-loose/ \
       domains/ecai23/training/strips/grid/unlock/ \
       domains/ecai23/training/strips/grid/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/grid/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/grid/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/grid/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/grid/pddl/instance_3.pddl \
                                   -o domains/ecai23/training/strips/grid/

# Gripper
rm -rf domains/ecai23/training/strips/gripper/pick/ \
       domains/ecai23/training/strips/gripper/drop/ \
       domains/ecai23/training/strips/gripper/move/ \
       domains/ecai23/training/strips/gripper/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/gripper/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/gripper/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/gripper/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/gripper/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/gripper/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/gripper/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/gripper/

# Hanoi
rm -rf domains/ecai23/training/strips/hanoi/move/ \
       domains/ecai23/training/strips/hanoi/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/hanoi/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/hanoi/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/hanoi/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/hanoi/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/hanoi/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/hanoi/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/hanoi/

# Miconic
rm -rf domains/ecai23/training/strips/miconic/board/ \
       domains/ecai23/training/strips/miconic/depart/ \
       domains/ecai23/training/strips/miconic/up/ \
       domains/ecai23/training/strips/miconic/down/ \
       domains/ecai23/training/strips/miconic/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/miconic/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/miconic/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/miconic/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/miconic/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/miconic/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/miconic/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/miconic/

# N-Puzzle
rm -rf domains/ecai23/training/strips/npuzzle/move/ \
       domains/ecai23/training/strips/npuzzle/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/npuzzle/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/npuzzle/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/npuzzle/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/npuzzle/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/npuzzle/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/npuzzle/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/npuzzle/

# Parking
rm -rf domains/ecai23/training/strips/parking/move-car-to-car/ \
       domains/ecai23/training/strips/parking/move-car-to-curb/ \
       domains/ecai23/training/strips/parking/move-curb-to-car/ \
       domains/ecai23/training/strips/parking/move-curb-to-curb/ \
       domains/ecai23/training/strips/parking/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/parking/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/parking/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/parking/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/parking/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/parking/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/parking/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/parking/

# Rovers
rm -rf domains/ecai23/training/strips/rovers/calibrate/ \
       domains/ecai23/training/strips/rovers/communicate_image_data/ \
       domains/ecai23/training/strips/rovers/communicate_rock_data/ \
       domains/ecai23/training/strips/rovers/communicate_soil_data/ \
       domains/ecai23/training/strips/rovers/drop/ \
       domains/ecai23/training/strips/rovers/navigate/ \
       domains/ecai23/training/strips/rovers/sample_rock/ \
       domains/ecai23/training/strips/rovers/sample_soil/ \
       domains/ecai23/training/strips/rovers/take_image/ \
       domains/ecai23/training/strips/rovers/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/rovers/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/rovers/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_5.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_6.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_7.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_8.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_9.pddl \
                                      domains/ecai23/training/strips/rovers/pddl/instance_10.pddl \
                                   -o domains/ecai23/training/strips/rovers/

# Satellite
rm -rf domains/ecai23/training/strips/satellite/turn_to/ \
       domains/ecai23/training/strips/satellite/switch_on/ \
       domains/ecai23/training/strips/satellite/switch_off/ \
       domains/ecai23/training/strips/satellite/calibrate/ \
       domains/ecai23/training/strips/satellite/take_image/ \
       domains/ecai23/training/strips/satellite/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/satellite/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/satellite/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/satellite/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/satellite/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/satellite/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/satellite/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/satellite/


# Transport
rm -rf domains/ecai23/training/strips/transport/pick-up/ \
       domains/ecai23/training/strips/transport/drop/ \
       domains/ecai23/training/strips/transport/drive/ \
       domains/ecai23/training/strips/transport/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/transport/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/transport/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/transport/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/transport/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/transport/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/transport/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/transport/

# Visitall
rm -rf domains/ecai23/training/strips/visitall/move/ \
       domains/ecai23/training/strips/visitall/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/training/strips/visitall/pddl/domain.pddl \
                                   -i domains/ecai23/training/strips/visitall/pddl/instance_1.pddl \
                                      domains/ecai23/training/strips/visitall/pddl/instance_2.pddl \
                                      domains/ecai23/training/strips/visitall/pddl/instance_3.pddl \
                                      domains/ecai23/training/strips/visitall/pddl/instance_4.pddl \
                                      domains/ecai23/training/strips/visitall/pddl/instance_5.pddl \
                                   -o domains/ecai23/training/strips/visitall/
