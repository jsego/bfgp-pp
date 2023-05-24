//
// Created by js on 27/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_NUM_EMPTY_INSTRUCTIONS_H
#define __EVALUATION_FUNCTIONS_NUM_EMPTY_INSTRUCTIONS_H
#include "evaluation_function.h"

namespace evaluation_functions {
    class NumEmptyInstructions : public EvaluationFunction {
    public:
        NumEmptyInstructions() : EvaluationFunction("nei") {}

        ~NumEmptyInstructions() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Return the number of repeated instructions
            value_t n_empty_ins = 0;
            for(const auto &ins : p->get_instructions()){
                if(ins == nullptr)
                    n_empty_ins++;
            }
            return n_empty_ins;
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_NUM_EMPTY_INSTRUCTIONS_H
