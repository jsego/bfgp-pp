//
// Created by js on 1/09/22.
//

#ifndef __THEORIES_CORE_ITE_H__
#define __THEORIES_CORE_ITE_H__

#include "../../expressions/effects/assign.h"
#include "../../instructions/bitvec/ite.h"
#include "../../expressions/conditions/equals.h"

namespace theory::core{
    class ITE{
    public:
        ITE() = default;

        ~ITE() = default;

        void ite_instructions(std::vector< std::vector< std::shared_ptr<expressions::conditions::Condition> > > &features,
                              std::vector<std::vector<std::shared_ptr<instructions::Instruction> > > &instructions ){
            // In the first line, an ITE cannot be programmed since it previously requires a TEST
            // and the last line is only for an END instruction
            int program_lines = instructions.size();
            for(int line = 1; line+1 < program_lines; line++){
                vec_id_t lhs_ptr_ids = {sd->get_type_id("ptr-goal")};
                if(line+2 < program_lines ) lhs_ptr_ids.emplace_back(sd->get_type_id("ptr-res-"+std::to_string(line)));

                vec_id_t rhs_ptr_ids = {sd->get_type_id("ptr-input")};
                for(int prev_line = 0; prev_line < line; prev_line++)
                    rhs_ptr_ids.emplace_back(sd->get_type_id("ptr-res-"+std::to_string(prev_line)));

                auto pred_id = sd->get_type_id("vector");
                for(const auto& lhs_ptr_id : lhs_ptr_ids) {
                    auto lhs_reg_name = "vector(" + sd->get_pointer_name(lhs_ptr_id) +")";
                    vec_id_t lhs_ptr_params = {lhs_ptr_id};
                    for (const auto &rhs_true_ptr_id: rhs_ptr_ids) {
                        auto rhs_true_reg_name = "vector(" + sd->get_pointer_name(rhs_true_ptr_id) + ")";
                        vec_id_t rhs_true_params = {rhs_true_ptr_id};
                        for(const auto &rhs_false_ptr_id : rhs_ptr_ids ) {
                            if( rhs_true_ptr_id == rhs_false_ptr_id ) continue; // avoid assign the same value in ite
                            auto rhs_false_reg_name = "vector(" + sd->get_pointer_name(rhs_false_ptr_id) + ")";
                            vec_id_t rhs_false_params = {rhs_false_ptr_id};
                            // Precondition: NO CONDITIONS
                            // Effect: res = (zf?var1:var2)
                            auto assign_true =
                                    std::make_unique<expressions::effects::Assign>(sd,
                                                                                   std::make_unique<variables::Variable>(lhs_reg_name,NAME_VAR_TYPE_PREDICATE,pred_id,lhs_ptr_params),
                                                                                   std::make_unique<variables::Variable>(rhs_true_reg_name,NAME_VAR_TYPE_PREDICATE,pred_id,rhs_true_params));
                            auto assign_false =
                                    std::make_unique<expressions::effects::Assign>(sd,
                                                                                   std::make_unique<variables::Variable>(lhs_reg_name,NAME_VAR_TYPE_PREDICATE,pred_id,lhs_ptr_params),
                                                                                   std::make_unique<variables::Variable>(rhs_false_reg_name,NAME_VAR_TYPE_PREDICATE,pred_id,rhs_false_params));
                            auto ins_ite = std::make_shared<instructions::bitvec::ITE>(std::move(assign_true), std::move(assign_false));
                            ins_ite->add_cond(features[0][0] ); // only ZF = 1 in simple version
                            instructions[line].emplace_back(ins_ite);
                        }
                    }
                }
            }
        }

        static void generate_features(std::shared_ptr<StateDescriptor> &sd,
                                      std::vector< std::vector< std::shared_ptr<expressions::conditions::Condition> > > &features) {
            // Set only one conditions ZF
            std::vector<std::shared_ptr<expressions::conditions::Condition> > conds;

            conds.emplace_back(
                    std::make_shared<expressions::conditions::Equals>(sd,
                            std::make_unique<variables::Variable>("zf", NAME_VAR_TYPE_POINTER, sd->get_type_id("zf")),
                            std::make_unique<variables::Variable>("1", NAME_VAR_TYPE_CONSTANT, 1)));

            features = {
                    {conds[0]}, // zf
            };
        }
    };
}

#endif //__THEORIES_CORE_ITE_H__
