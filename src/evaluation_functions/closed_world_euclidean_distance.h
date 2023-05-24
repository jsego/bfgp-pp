//
// Created by js on 24/05/22.
//

#ifndef __EVALUATION_FUNCTIONS_CLOSED_WORLD_EUCLIDEAN_DISTANCE_H__
#define __EVALUATION_FUNCTIONS_CLOSED_WORLD_EUCLIDEAN_DISTANCE_H__

#include "evaluation_function.h"

namespace evaluation_functions {
    /// ToDo: test it
    class ClosedWorldEuclideanDistance : public EvaluationFunction {
    public:
        ClosedWorldEuclideanDistance() : EvaluationFunction("cwed") {}

        ~ClosedWorldEuclideanDistance() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Computing squared distance to goal after each execution.
            /// This is closed-world assumption and that goals are equalities
            auto vps = p->run( gpp );

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
                auto goal_state = ins->get_goal_state();
                std::set<std::string> visited; // FIXME: inefficient checking strings instead of ids

                // Add differences from S->GOAL
                for(const auto& f : s->get_facts()){
                    auto f_name = f->get_name();
                    if(f_name.size() > 8u and f_name.substr(0,8) == "(action_") continue;
                    auto goal_val = goal_state->get_value(f);
                    auto f_val = f->get_value();
                    res += (goal_val-f_val)*(goal_val-f_val);
                    if(goal_val!=f_val) visited.insert(f->get_name());
                }
                // Add unvisited differences from GOAL->S
                for(const auto& f : goal_state->get_facts()){
                    if(visited.find(f->get_name()) != visited.end()) continue;
                    auto s_val = s->get_value(f);
                    auto f_val = f->get_value();
                    res += (s_val-f_val)*(s_val-f_val);
                }
            }
            return res;
        }
    };
}
#endif //__EVALUATION_FUNCTIONS_CLOSED_WORLD_EUCLIDEAN_DISTANCE_H__
