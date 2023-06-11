//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_A_STAR_H__
#define __EVALUATION_FUNCTIONS_A_STAR_H__

#include "evaluation_function.h"

namespace evaluation_functions {

    class AStar : public EvaluationFunction {
    public:
        AStar() : EvaluationFunction("astar") {}

        ~AStar() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Computing squared distance to goal after each execution.
            /// This assumes that goals are equalities.
            auto vps = p->run( gpp );

            // Error when running the program over active instances
            if (vps.empty()) return INF;

            value_t res = 0;
            id_type active_instances_local_idx = 0;
            for(const auto& idx : gpp->get_active_instance_idxs()){
                auto ins = gpp->get_instance(idx);
                auto s = vps[active_instances_local_idx++]->get_state();
                for (const auto &g: ins->get_goal_condition()) {
                    auto lhs = g->get_value(g->get_lhs(), s);
                    auto rhs = g->get_value(g->get_rhs(), s);
                    res += ((lhs - rhs) * (lhs - rhs));  // note: care with overflow operation
                }
            }
            return res + p->get_num_of_steps(); // e = h + c
        }
    };
}
#endif //__EVALUATION_FUNCTIONS_A_STAR_H__
