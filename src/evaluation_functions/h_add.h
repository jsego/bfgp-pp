//
// Created by js on 24/10/22.
//

#ifndef __EVALUATION_FUNCTIONS_H_ADD_H__
#define __EVALUATION_FUNCTIONS_H_ADD_H__

#include "evaluation_function.h"
#include "../relaxations/relaxed_planning_graph.h"

namespace evaluation_functions{
    class HAdd : public EvaluationFunction{
    public:
        HAdd() : EvaluationFunction("hadd") {};
        ~HAdd() override = default;

        // Computing the h_add heuristic per node in the search
        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
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
                auto rpg = std::make_unique<relaxation::RelaxedPlanningGraph>(
                        gpp->get_generalized_domain()->get_domain(), ins);
                rpg->build_relaxed_graph(s);
                /*for(const auto& g : rpg->get_goal_facts()){
                    while(not s->get_fact(g)){

                    }
                }*/
                res += rpg->get_num_layers();
            }
            return res;
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_H_ADD_H__
