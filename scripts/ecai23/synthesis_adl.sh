# ELEVATOR
./main.bin -m synthesis -t actions_adl -l 7 -f domains/ecai23/training/adl/elevators/up/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_adl -l 7 -f domains/ecai23/training/adl/elevators/down/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_adl -l 18 -f domains/ecai23/training/adl/elevators/stop/ -e ilc mi cwed -pgp true

# BRIEFCASE
./main.bin -m synthesis -t actions_adl -l 4 -f domains/ecai23/training/adl/briefcase/take-out/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_adl -l 8 -f domains/ecai23/training/adl/briefcase/put-in/ -e ilc mi cwed -pgp true
./main.bin -m synthesis -t actions_adl -l 15 -f domains/ecai23/training/adl/briefcase/move/ -e ilc mi cwed -pgp true

# MAINTENANCE
./main.bin -m synthesis -t actions_adl -l 9 -f domains/ecai23/training/adl/maintenance/workat/ -e ilc mi cwed -pgp true

