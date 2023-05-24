//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_LOOP_COUNTER_H__
#define __EVALUATION_FUNCTIONS_LOOP_COUNTER_H__

#include "evaluation_function.h"
#include "../instructions/for.h"

namespace evaluation_functions {
    class LoopCounter : public EvaluationFunction {
    public:
        LoopCounter() : EvaluationFunction("lc") {}

        ~LoopCounter() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            // Compute number of loops of a program
            value_t res = 0;
            auto instructions = p->get_instructions();
            for (const auto &ins: instructions) {
                if (dynamic_cast<instructions::For*>(ins)) res++;
                else if(dynamic_cast<instructions::Goto*>(ins)) res++; // ToDo: possibly with dest_line < current_line
            }
            return res;
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_LOOP_COUNTER_H__
