//
// Created by js on 8/03/23.
//

#ifndef __EVALUATION_FUNCTIONS_ACCUMULATED_COST_H__
#define __EVALUATION_FUNCTIONS_ACCUMULATED_COST_H__

#include "evaluation_function.h"

namespace evaluation_functions {

    class AccumulatedCost : public EvaluationFunction {
    public:
        AccumulatedCost() : EvaluationFunction("ac") {}

        ~AccumulatedCost() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Return the number of steps taken by the current program in the gpp problem
            auto vps = p->run( gpp );

            // Error when running the program over active instances
            if (vps.empty()) return INF;

            return p->get_num_of_steps();
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_ACCUMULATED_COST_H__
