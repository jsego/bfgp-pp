//
// Created by js on 3/06/22.
//

#ifndef __EVALUATION_FUNCTIONS_CLOSEST_HAMMING_DISTANCE_H__
#define __EVALUATION_FUNCTIONS_CLOSEST_HAMMING_DISTANCE_H__
#include "evaluation_function.h"

namespace evaluation_functions {

    class ClosestHammingDistance : public EvaluationFunction {
        /// Evaluation function for computing the closest hamming distance between two bitvec variables
    public:
        ClosestHammingDistance() : EvaluationFunction("chd") {}

        ~ClosestHammingDistance() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Computing the closest hamming distance to goal after each execution.
            /// This assumes that goals are vector(ptr_goal) = [value].
            // ToDo: this is currently wrong. Run p only once, then compare the goal condition over each ptr_res_i
            //  memory location, and get the minimum for each instance. Then, accumulate all the results.

            auto vps = p->run(gpp);
            vec_value_t best_res(gpp->get_num_instances(), MaxValue);
            auto gd = gpp->get_generalized_domain();
            auto  pointers = gd->get_pointers(); // get all pointer ids of type object (possibly create a function to get pointers of a type)
            // Assume all objects are used in a vector func
            auto vec_func = gd->get_domain()->get_function("vector");

            //for (size_t i = 0; i < vps.size(); i++) {
            //    if(gpp->is_progressive() and (not gpp->is_instance_active(i))) continue;
            //    auto ins = gpp->get_instance(i);
            id_type active_instances_local_idx = 0;
            for(const auto& idx : gpp->get_active_instance_idxs()){
                auto ins = gpp->get_instance(idx);
                auto s = vps[active_instances_local_idx]->get_state();
                assert(ins->get_goal_condition().size() == 1u); // There should be only vector(ptr_goal) = ... as goal
                auto goal_cond = ins->get_goal_condition()[0];
                auto goal_expected_val = goal_cond->get_value(goal_cond->get_rhs(), s);
                // ToDo: continue from here...
                for(const auto& ptr : pointers ){
                    auto state_var = std::make_unique<variables::StateVariable>(vec_func,
                                                                                std::vector<Object*>({ptr->get_object()}));
                    auto prev_var_val = s->get_value(state_var.get());
                    value_t current_hamming_dist(0);
                    auto aux = (uvalue_t)goal_expected_val ^ (uvalue_t)prev_var_val;
                    while(aux){
                        current_hamming_dist += (value_t)(aux & 1);
                        aux>>=1;
                    }
                    best_res[active_instances_local_idx] = std::min(best_res[active_instances_local_idx], current_hamming_dist);
                }
                ++active_instances_local_idx;
            }

            if( std::all_of(best_res.begin(), best_res.end(), [](value_t v){return v == MaxValue;})){
                return MaxValue;
            }
            return std::accumulate(best_res.begin(), best_res.end(), 0);
        }
    };
}
#endif //__EVALUATION_FUNCTIONS_CLOSEST_HAMMING_DISTANCE_H__
