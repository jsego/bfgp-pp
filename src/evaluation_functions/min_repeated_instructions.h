//
// Created by js on 26/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_MIN_REPEATED_INSTRUCTIONS_H__
#define __EVALUATION_FUNCTIONS_MIN_REPEATED_INSTRUCTIONS_H__

#include "evaluation_function.h"

namespace evaluation_functions {
    class MinRepeatedInstructions : public EvaluationFunction {
    public:
        MinRepeatedInstructions() : EvaluationFunction("mri") {}

        ~MinRepeatedInstructions() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Return the number of repeated instructions
            std::map<std::string, value_t > instruction_counter;
            value_t max_repetitions = 0;
            for(const auto &ins : p->get_instructions()){
                if(ins != nullptr){
                    auto ins_key = ins->to_string(false);
                    instruction_counter[ins_key]++;
                    max_repetitions = std::max(max_repetitions, instruction_counter[ins_key]);
                }
            }
            return max_repetitions;
        }
    };
}
#endif //__EVALUATION_FUNCTIONS_MIN_REPEATED_INSTRUCTIONS_H__
