# ELEVATOR
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/elevators/up/ -p experiments/ecai23/training/adl/elevators/up_7_ilc_mi_cwed.prog
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/elevators/down/ -p experiments/ecai23/training/adl/elevators/down_7_ilc_mi_cwed.prog
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/elevators/stop/ -p experiments/ecai23/training/adl/elevators/stop_18_ilc_mi_cwed.prog

# BRIEFCASE
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/briefcase/take-out/ -p experiments/ecai23/training/adl/briefcase/take-out_4_ilc_mi_cwed.prog
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/briefcase/put-in/ -p experiments/ecai23/training/adl/briefcase/put-in_8_ilc_mi_cwed.prog 
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/briefcase/move/ -p experiments/ecai23/training/adl/briefcase/move_15_ilc_mi_cwed.prog

# MAINTENANCE
./main.bin -m validation-prog -t actions_adl -f domains/ecai23/testing/adl/maintenance/workat/ -p experiments/ecai23/training/adl/maintenance/workat_9_ilc_mi_cwed.prog

