//
// Created by js on 31/08/22.
//

#ifndef __THEORY_STRIPS_H__
#define __THEORY_STRIPS_H__

#include "../../grounder.h"
#include "../../generalized_domain.h"

namespace theory::core{
    class STRIPS{
        /// The STRIPS class encapsulates all planning actions grounded over pointers as instructions
    public:
        STRIPS(Grounder *grounder, GeneralizedDomain* gd){
            auto dom = gd->get_domain();
            assert(dom != nullptr);
            auto actions = dom->get_actions(); // original planning actions
            for(const auto& act : actions){
                std::vector<ObjectType*> arg_types;
                for(const auto& o : act->get_parameters()){
                    arg_types.emplace_back(o->get_type());
                }
                auto all_ptrs = gd->get_pointers();
                std::vector<std::vector<variables::Pointer*>> ptr_groundings;
                std::vector<variables::Pointer*> current_grounding(arg_types.size());
                grounder->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);

                for(const auto& grounding : ptr_groundings){
                    // copy action schema (with references to new parameters)
                    std::vector<variables::Variable*> var_grounding;
                    for(const auto& ptr : grounding)
                        var_grounding.emplace_back(ptr);
                    gd->add_instruction(std::make_unique<instructions::PlanningAction>(
                            act->copy_with_substitution(var_grounding)));
                }
            }
        }
    };
}

#endif //__THEORY_STRIPS_H__
