//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_LOOP_LINES_COUNTER_H__
#define __EVALUATION_FUNCTIONS_LOOP_LINES_COUNTER_H__

#include "evaluation_function.h"
#include "../instructions/for.h"

namespace evaluation_functions {
    class LoopLinesCounter : public EvaluationFunction {
    public:
        LoopLinesCounter() : EvaluationFunction("llc") {}

        ~LoopLinesCounter() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Counting number of times lines are covered by loops of a program
            value_t line_counter = 0;
            auto instructions = p->get_instructions();
            for (size_t i = 0; i < instructions.size(); i++) {
                auto f = dynamic_cast<instructions::For*>(instructions[i]);
                if (f) line_counter += value_t(1+f->get_destination_line() - i);
                auto g = dynamic_cast<instructions::Goto*>(instructions[i]);
                if(g and g->get_destination_line()<i) line_counter += value_t(1+i-g->get_destination_line());
            }
            return -line_counter;
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_LOOP_LINES_COUNTER_H__
