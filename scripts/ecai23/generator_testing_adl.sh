# Briefcase
rm -rf domains/ecai23/testing/adl/briefcase/move/ \
       domains/ecai23/testing/adl/briefcase/take-out/ \
       domains/ecai23/testing/adl/briefcase/put-in/ \
       domains/ecai23/testing/adl/briefcase/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/adl/briefcase/pddl/domain.pddl \
                                   -i domains/ecai23/testing/adl/briefcase/pddl/instance_1.pddl \
                                      domains/ecai23/testing/adl/briefcase/pddl/instance_2.pddl \
                                      domains/ecai23/testing/adl/briefcase/pddl/instance_3.pddl \
                                      domains/ecai23/testing/adl/briefcase/pddl/instance_4.pddl \
                                      domains/ecai23/testing/adl/briefcase/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/adl/briefcase/
                                   
# Elevators
rm -rf domains/ecai23/testing/adl/elevators/stop/ \
       domains/ecai23/testing/adl/elevators/up/ \
       domains/ecai23/testing/adl/elevators/down/ \
       domains/ecai23/testing/adl/elevators/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/adl/elevators/pddl/domain.pddl \
                                   -i domains/ecai23/testing/adl/elevators/pddl/instance_1.pddl \
                                      domains/ecai23/testing/adl/elevators/pddl/instance_2.pddl \
                                      domains/ecai23/testing/adl/elevators/pddl/instance_3.pddl \
                                      domains/ecai23/testing/adl/elevators/pddl/instance_4.pddl \
                                      domains/ecai23/testing/adl/elevators/pddl/instance_5.pddl \
                                   -o domains/ecai23/testing/adl/elevators/
                                   
# Maintenance
rm -rf domains/ecai23/testing/adl/maintenance/workat/ \
       domains/ecai23/testing/adl/maintenance/plans/
PYTHONHASHSEED=1 python preprocess/generate_plan.py -d domains/ecai23/testing/adl/maintenance/pddl/domain.pddl \
                                   -i domains/ecai23/testing/adl/maintenance/pddl/instance_1.pddl \
                                      domains/ecai23/testing/adl/maintenance/pddl/instance_2.pddl \
                                   -o domains/ecai23/testing/adl/maintenance/                                       
