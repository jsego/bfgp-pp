//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_MAX_NESTED_LOOPS_H__
#define __EVALUATION_FUNCTIONS_MAX_NESTED_LOOPS_H__

#include "evaluation_function.h"
#include "../instructions/for.h"

namespace evaluation_functions {
    class MaxNestedLoop : public EvaluationFunction {
    public:
        MaxNestedLoop() : EvaluationFunction("mnl") {}

        ~MaxNestedLoop() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Compute nested gotos (there could be multiple strategies)
            auto instructions = p->get_instructions();
            vec_value_t affected_lines(instructions.size(), 0);
            for (size_t line = 0; line < instructions.size(); line++) {
                size_t destination_line;
                auto f = dynamic_cast<instructions::For*>(instructions[line]);
                if (f) destination_line = f->get_destination_line();
                auto g = dynamic_cast<instructions::Goto*>(instructions[line]);
                if(g) destination_line = g->get_destination_line();
                if(f or (g and destination_line < line)){
                    auto aux_line = destination_line;
                    int dir = (aux_line > line ? -1 : 1);
                    while (aux_line != line) {
                        affected_lines[aux_line]++;
                        aux_line += dir;
                    }
                    affected_lines[line]++;
                }
            }
            return *std::max_element(affected_lines.begin(), affected_lines.end());
        }
    };
}


#endif //__EVALUATION_FUNCTIONS_MAX_NESTED_LOOPS_H__
