//
// Created by js on 1/09/22.
//

#ifndef __THEORIES_BITVEC_H__
#define __THEORIES_BITVEC_H__

#include "theory.h"
#include "./core/terminal.h"
#include "./core/ite.h"
#include "../instructions/bitvec/not.h"
#include "../instructions/bitvec/arba.h"
#include "../instructions/bitvec/ehad.h"
#include "../instructions/bitvec/shesh.h"
#include "../instructions/bitvec/smol.h"
#include "../instructions/bitvec/and.h"
#include "../instructions/bitvec/or.h"
#include "../instructions/bitvec/xor.h"
#include "../instructions/bitvec/add.h"
#include "../generalized_domain.h"

namespace theory {
    class Bitvec : public Theory {
    public:
        Bitvec() : Theory("Bitvec"){}

        static void build_theory(GeneralizedDomain* gd){
            _instructions.resize(program_lines );
            auto sd = _domain->get_state_descriptor();

            /// Assume the main data structure is vector
            auto pred_vector_id = sd->get_type_id("vector");

            /// 0. Adding extra pointers (in bitvec, pointers are constant/fixed):
            /// - zero, one, input and goal pointers (although they must be in the domain)
            /// - one per each line in [0, n-2], assuming each pointer is of type object
            vec_str_t base_ptr_names = {"ptr-zero", "ptr-one", "ptr-input", "ptr-goal"};
            for(const auto& ptr_name : base_ptr_names ){
                if(not sd->is_pointer(ptr_name)){
                    sd->add_pointer("object", ptr_name);
                }
            }
            for(int line = 0; line+2 < program_lines; line++){
                sd->add_pointer("object","ptr-res-"+std::to_string(line));
            }

            /// 1. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(_instructions);

            // ?. Call STRIPS constructor
            // auto strips = std::make_unique<core::STRIPS>(d, _instructions_line);

            // ToDo: move the next instruction creation to core
            for(int line = 0; line+2 < program_lines; line++){
                vec_id_t lhs_ptr_ids = {sd->get_type_id("ptr-res-" + std::to_string(line)),
                                        sd->get_type_id("ptr-goal")};
                vec_id_t rhs_ptr_ids = {sd->get_type_id("ptr-input"),
                                        sd->get_type_id("ptr-zero"),
                                        sd->get_type_id("ptr-one")};
                for(int prev_line = 0; prev_line < line; prev_line++)
                    rhs_ptr_ids.emplace_back(sd->get_type_id("ptr-res-"+std::to_string(prev_line)));

                /// 3. Add Bitvec Operators
                for(const auto& lhs_ptr_id : lhs_ptr_ids) {
                    for (size_t idx1 = 0; idx1 < rhs_ptr_ids.size(); idx1++) {
                        auto rhs_ptr_id = rhs_ptr_ids[idx1];
                        _instructions[line].emplace_back(
                                std::make_shared<instructions::bitvec::Not>(lhs_ptr_id, rhs_ptr_id, sd));
                        _instructions[line].emplace_back(
                                std::make_shared<instructions::bitvec::Ehad>(lhs_ptr_id, rhs_ptr_id, sd));
                        _instructions[line].emplace_back(
                                std::make_shared<instructions::bitvec::Arba>(lhs_ptr_id, rhs_ptr_id, sd));
                        _instructions[line].emplace_back(
                                std::make_shared<instructions::bitvec::Shesh>(lhs_ptr_id, rhs_ptr_id, sd));
                        _instructions[line].emplace_back(
                                std::make_shared<instructions::bitvec::Smol>(lhs_ptr_id, rhs_ptr_id, sd));
                        for (size_t idx2 = idx1+1; idx2 < rhs_ptr_ids.size(); idx2++) {
                            auto rhs_ptr_id2 = rhs_ptr_ids[idx2];
                            _instructions[line].emplace_back(
                                    std::make_shared<instructions::bitvec::And>(lhs_ptr_id, rhs_ptr_id, rhs_ptr_id2, sd));
                            _instructions[line].emplace_back(
                                    std::make_shared<instructions::bitvec::Or>(lhs_ptr_id, rhs_ptr_id, rhs_ptr_id2, sd));
                            _instructions[line].emplace_back(
                                    std::make_shared<instructions::bitvec::Xor>(lhs_ptr_id, rhs_ptr_id, rhs_ptr_id2, sd));
                            _instructions[line].emplace_back(
                                    std::make_shared<instructions::bitvec::Add>(lhs_ptr_id, rhs_ptr_id, rhs_ptr_id2, sd));
                        }
                    }
                }

                /// 4. Add test(register) before an ite
                for(const auto& rhs_ptr_id : rhs_ptr_ids){
                    auto register_name = "vector(" + sd->get_pointer_name(rhs_ptr_id) + ")";
                    // test(register) = cmp(register,0). Test if a register is 0
                    auto cmp_act = std::make_shared<Action>("test",
                                                            vec_str_t({register_name}),
                                                            NAME_VAR_TYPE_PREDICATE);
                    // NO CONDS
                    auto cmp_op =
                            std::make_unique<expressions::effects::Compare>(sd,
                                                                            std::make_unique<variables::Variable>(register_name,
                                                                                                                  NAME_VAR_TYPE_PREDICATE,
                                                                                                                  pred_vector_id,
                                                                                                                  vec_id_t({rhs_ptr_id})),
                                                                            std::make_unique<variables::Variable>("1", NAME_VAR_TYPE_CONSTANT, 1));
                    cmp_act->add_operation(std::move(cmp_op));

                    auto cmp_ins = std::make_shared<instructions::PlanningAction>(cmp_act);
                    _instructions[line].emplace_back(cmp_ins);
                }
            }

            /// 5. Call ITE constructor
            auto ite = std::make_unique<core::ITE>();
            /// 5.a Generate ITE features
            ite->generate_features(sd, _features);
            /// 5.b  Build ITE instructions
            ite->ite_instructions(sd, _features, _instructions);
        }
    };
}

#endif //__THEORIES_BITVEC_H__
