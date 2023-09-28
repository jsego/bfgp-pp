# Run generators
./scripts/ecai23/generator_training_adl.sh
./scripts/ecai23/generator_training_cellular.sh
./scripts/ecai23/generator_training_ram.sh
./scripts/ecai23/generator_training_strips.sh
# Run synthesis
./scripts/ecai23/synthesis.sh
./scripts/ecai23/generator_testing_adl.sh
./scripts/ecai23/generator_testing_cellular.sh
./scripts/ecai23/generator_testing_ram.sh
./scripts/ecai23/generator_testing_strips.sh
# Run validation
./scripts/ecai23/validate.sh
