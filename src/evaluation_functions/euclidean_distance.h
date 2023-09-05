//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_EUCLIDEAN_DISTANCE_H__
#define __EVALUATION_FUNCTIONS_EUCLIDEAN_DISTANCE_H__

#include "evaluation_function.h"

namespace evaluation_functions {

    class EuclideanDistance : public EvaluationFunction {
    public:
        EuclideanDistance() : EvaluationFunction("ed") {}

        ~EuclideanDistance() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Computing squared distance to goal after each execution.
            /// This assumes that goals are equalities.
            //auto vps = p->run( gpp );
            auto vps = p->get_program_states();

            // Error when running the program over active instances
            if (vps.empty()) return INF;

            value_t res = 0;
            //for (size_t i = 0; i < vps.size(); i++) {
            //    if(gpp->is_progressive() and (not gpp->is_instance_active(i))) continue;
            //    auto ins = gpp->get_instance(i);
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
            return res;
        }
    };
}
#endif //__EVALUATION_FUNCTIONS_EUCLIDEAN_DISTANCE_H__
