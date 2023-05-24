//
// Created by js on 7/11/22.
//

#ifndef __EVALUATION_FUNCTIONS_MAX_IFS_H__
#define __EVALUATION_FUNCTIONS_MAX_IFS_H__

#include "evaluation_function.h"
#include "../instructions/if.h"
#include "../instructions/ram/register_test.h"

namespace evaluation_functions {
    class MaxIfs : public EvaluationFunction {
    public:
        MaxIfs() : EvaluationFunction("mi") {}

        ~MaxIfs() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Maximize number of lines with IF and TEST instructions
            auto instructions = p->get_instructions();
            value_t if_counter{0};
            for(const auto& ins : p->get_instructions()){
                auto ins_if = dynamic_cast<instructions::If*>(ins);
                if(ins_if) ++if_counter;
                auto ins_test = dynamic_cast<instructions::RegisterTest*>(ins);
                if(ins_test) ++if_counter;
            }
            return -if_counter;  // Returning the negated counter to maximize the number of IF instructions
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_MAX_IFS_H__
