# BLOCKS
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/blocks/pick-up/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/blocks/put-down/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/blocks/stack/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/blocks/unstack/ -e ilc mi cwed -pgp true

# DRIVERLOG
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/board-truck/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/disembark-truck/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/drive-truck/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/load-truck/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/unload-truck/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/driverlog/walk/ -e ilc mi cwed -pgp true

# FERRY
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/ferry/board/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/ferry/debark/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/ferry/sail/ -e ilc mi cwed -pgp true


# GRID
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/grid/move/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/grid/pickup/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/grid/pickup-and-loose/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/grid/putdown/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/grid/unlock/ -e ilc mi cwed -pgp true

# GRIPPER
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/gripper/pick/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/gripper/drop/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/gripper/move/ -e ilc mi cwed -pgp true

# HANOI
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/hanoi/move/ -e ilc mi cwed -pgp true

# MICONIC
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/miconic/board/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/miconic/depart/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/miconic/down/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/miconic/up/ -e ilc mi cwed -pgp true

# N-PUZZLE
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/npuzzle/move/ -e ilc mi cwed -pgp true

# PARKING
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/parking/move-car-to-car/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/parking/move-car-to-curb/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/parking/move-curb-to-car/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/parking/move-curb-to-curb/ -e ilc mi cwed -pgp true

# ROVERS
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/calibrate/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/communicate_image_data/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/communicate_rock_data/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/communicate_soil_data/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/drop/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/navigate/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/sample_rock/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/sample_soil/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/rovers/take_image/ -e ilc mi cwed -pgp true

# SATELLITE
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/satellite/calibrate/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/satellite/switch_off/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/satellite/switch_on/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/satellite/take_image/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/satellite/turn_to/ -e ilc mi cwed -pgp true

# TRANSPORT
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/transport/drive/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/transport/drop/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/transport/pick-up/ -e ilc mi cwed -pgp true

# VISITALL
./main.bin -m synthesis -t actions_strips -l 1 -f domains/ecai23/training/strips/visitall/move/ -e ilc mi cwed -pgp true

