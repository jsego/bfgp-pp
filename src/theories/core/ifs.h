//
// Created by js on 1/09/22.
//

#ifndef __THEORIES_CORE_IFS_H__
#define __THEORIES_CORE_IFS_H__

#include "../../grounder.h"
#include "../../generalized_domain.h"
#include "../../expressions/conditions/condition.h"
#include "../../instructions/if.h"
#include "../../instructions/planning_action.h"
#include "../../expressions/effects/compare.h"
#include "../../expressions/conditions/equals.h"


namespace theory::core{
    class Ifs{
    public:
        Ifs() = default;

        ~Ifs() = default;

        static void make_ifs(Grounder *gr, GeneralizedDomain *gd){
            auto all_flags = gd->get_flags();
            std::vector<std::vector<value_t>> all_groundings;
            std::vector<value_t> current_grounding(all_flags.size());
            gr->ground_flags(all_flags, all_groundings, current_grounding);  // ground all flags combinations
            // create an IF for each destination line (>1) & grounding
            for(size_t dest_line = 2; dest_line < gd->get_program_lines(); dest_line++){
                for(const auto& grounding : all_groundings) {
                    // Avoid zf = 1 & cf = 1 which is unconditional jump
                    if(grounding.size()>1u and
                    std::all_of(grounding.begin(),grounding.end(),
                                [](const auto& v){return v==1;})) continue;
                    auto if_ins = std::make_unique<instructions::If>(dest_line);
                    for(size_t idx=0;idx<all_flags.size(); idx++)
                        if_ins->add_cond(all_flags[idx], grounding[idx]);
                    gd->add_instruction(std::move(if_ins));
                }
            }
        }
    };
}

#endif //__THEORIES_CORE_IFS_H__
