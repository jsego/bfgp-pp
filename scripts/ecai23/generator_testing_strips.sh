# Blocks
rm -rf domains/ecai23/testing/strips/blocks/pick-up/ \
       domains/ecai23/testing/strips/blocks/put-down/ \
       domains/ecai23/testing/strips/blocks/stack/ \
       domains/ecai23/testing/strips/blocks/unstack/ \
       domains/ecai23/testing/strips/blocks/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/blocks/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/blocks/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/blocks/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/blocks/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/blocks/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/blocks/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/blocks/

# Driverlog
rm -rf domains/ecai23/testing/strips/driverlog/load-truck/ \
       domains/ecai23/testing/strips/driverlog/disembark-truck/ \
       domains/ecai23/testing/strips/driverlog/unload-truck/ \
       domains/ecai23/testing/strips/driverlog/board-truck/ \
       domains/ecai23/testing/strips/driverlog/drive-truck/ \
       domains/ecai23/testing/strips/driverlog/walk/ \
       domains/ecai23/testing/strips/driverlog/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/driverlog/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/driverlog/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/driverlog/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/driverlog/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/driverlog/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/driverlog/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/driverlog/

# Ferry
rm -rf domains/ecai23/testing/strips/ferry/sail/ \
       domains/ecai23/testing/strips/ferry/board/ \
       domains/ecai23/testing/strips/ferry/debark/ \
       domains/ecai23/testing/strips/ferry/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/ferry/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/ferry/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/ferry/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/ferry/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/ferry/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/ferry/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/ferry/

# Grid
rm -rf domains/ecai23/testing/strips/grid/pickup/ \
       domains/ecai23/testing/strips/grid/putdown/ \
       domains/ecai23/testing/strips/grid/move/ \
       domains/ecai23/testing/strips/grid/pickup-and-loose/ \
       domains/ecai23/testing/strips/grid/unlock/ \
       domains/ecai23/testing/strips/grid/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/grid/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/grid/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/grid/pddl/instance_2.pddl \
                                   -o domains/ecai23/testing/strips/grid/

# Gripper
rm -rf domains/ecai23/testing/strips/gripper/pick/ \
       domains/ecai23/testing/strips/gripper/drop/ \
       domains/ecai23/testing/strips/gripper/move/ \
       domains/ecai23/testing/strips/gripper/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/gripper/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/gripper/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/gripper/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/gripper/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/gripper/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/gripper/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/gripper/
# Miconic
rm -rf domains/ecai23/testing/strips/miconic/board/ \
       domains/ecai23/testing/strips/miconic/depart/ \
       domains/ecai23/testing/strips/miconic/up/ \
       domains/ecai23/testing/strips/miconic/down/ \
       domains/ecai23/testing/strips/miconic/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/miconic/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/miconic/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/miconic/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/miconic/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/miconic/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/miconic/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/miconic/

# Hanoi
rm -rf domains/ecai23/testing/strips/hanoi/move/ \
       domains/ecai23/testing/strips/hanoi/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/hanoi/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/hanoi/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/hanoi/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/hanoi/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/hanoi/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/hanoi/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/hanoi/

# N-Puzzle
rm -rf domains/ecai23/testing/strips/npuzzle/move/ \
       domains/ecai23/testing/strips/npuzzle/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/npuzzle/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/npuzzle/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/npuzzle/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/npuzzle/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/npuzzle/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/npuzzle/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/npuzzle/

# Parking
rm -rf domains/ecai23/testing/strips/parking/move-car-to-car/ \
       domains/ecai23/testing/strips/parking/move-car-to-curb/ \
       domains/ecai23/testing/strips/parking/move-curb-to-car/ \
       domains/ecai23/testing/strips/parking/move-curb-to-curb/ \
       domains/ecai23/testing/strips/parking/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/parking/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/parking/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/parking/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/parking/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/parking/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/parking/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/parking/

# Rovers
rm -rf domains/ecai23/testing/strips/rovers/calibrate/ \
       domains/ecai23/testing/strips/rovers/communicate_image_data/ \
       domains/ecai23/testing/strips/rovers/communicate_rock_data/ \
       domains/ecai23/testing/strips/rovers/communicate_soil_data/ \
       domains/ecai23/testing/strips/rovers/drop/ \
       domains/ecai23/testing/strips/rovers/navigate/ \
       domains/ecai23/testing/strips/rovers/sample_rock/ \
       domains/ecai23/testing/strips/rovers/sample_soil/ \
       domains/ecai23/testing/strips/rovers/take_image/ \
       domains/ecai23/testing/strips/rovers/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/rovers/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/rovers/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/rovers/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/rovers/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/rovers/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/rovers/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/rovers/

# Satellite
rm -rf domains/ecai23/testing/strips/satellite/turn_to/ \
       domains/ecai23/testing/strips/satellite/switch_on/ \
       domains/ecai23/testing/strips/satellite/switch_off/ \
       domains/ecai23/testing/strips/satellite/calibrate/ \
       domains/ecai23/testing/strips/satellite/take_image/ \
       domains/ecai23/testing/strips/satellite/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/satellite/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/satellite/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/satellite/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/satellite/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/satellite/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/satellite/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/satellite/

# Transport
rm -rf domains/ecai23/testing/strips/transport/pick-up/ \
       domains/ecai23/testing/strips/transport/drop/ \
       domains/ecai23/testing/strips/transport/drive/ \
       domains/ecai23/testing/strips/transport/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/transport/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/transport/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/transport/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/transport/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/transport/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/transport/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/transport/

# Visit All
rm -rf domains/ecai23/testing/strips/visitall/move/ \
       domains/ecai23/testing/strips/visitall/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/strips/visitall/pddl/domain.pddl \
                                   -i domains/ecai23/testing/strips/visitall/pddl/instance_1.pddl \
                                      domains/ecai23/testing/strips/visitall/pddl/instance_2.pddl \
                                      domains/ecai23/testing/strips/visitall/pddl/instance_3.pddl \
                                      domains/ecai23/testing/strips/visitall/pddl/instance_4.pddl \
                                      domains/ecai23/testing/strips/visitall/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/strips/visitall/

