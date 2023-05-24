//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_MAX_LOOP_LINES_H__
#define __EVALUATION_FUNCTIONS_MAX_LOOP_LINES_H__

#include "evaluation_function.h"
#include "../instructions/for.h"

namespace evaluation_functions {
    class MaxLoopLines : public EvaluationFunction {
    public:
        MaxLoopLines() : EvaluationFunction("mll") {}

        ~MaxLoopLines() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Maximize number of lines covered by program loops
            auto instructions = p->get_instructions();
            std::vector<bool> covered(instructions.size(), false);
            for (size_t i = 0; i < instructions.size(); i++) {
                // CPP: count the size of the for loop
                auto f = dynamic_cast<instructions::For*>(instructions[i]);
                if(f)
                    for (size_t j = i; j <= f->get_destination_line(); j++) covered[j] = true;
                // Assembler: count only on backward gotos
                auto g = dynamic_cast<instructions::Goto*>(instructions[i]);
                if(g and g->get_destination_line()<i)
                    for(size_t j=g->get_destination_line(); j<=i; j++) covered[j]=true;
            }
            return -(value_t) count(covered.begin(), covered.end(), true);
        }

    };
}

#endif //__EVALUATION_FUNCTIONS_MAX_LOOP_LINES_H__
