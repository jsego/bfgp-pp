//
// Created by js on 31/08/22.
//

#ifndef __THEORY_ACTION_SCHEMAS_H__
#define __THEORY_ACTION_SCHEMAS_H__

#include "theory.h"
#include "./core/strips.h"
#include "./core/ram.h"
#include "./core/fors.h"
#include "./core/terminal.h"
#include "./core/ifs.h"

#include "../generalized_domain.h"
#include "../variables/zero_flag.h"
#include "../variables/carry_flag.h"

namespace theory{
    class ActionSchemas : public Theory{
    public:
        ActionSchemas() : Theory("ActionSchemas"){}

        [[nodiscard]] bool is_action_theory() const override{return true;}

        static void build_theory(GeneralizedDomain *gd){
            auto grounder = std::make_unique<Grounder>();

            /// 1. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(gd);

            /// 2. Call Fors constructor (in increasing and decreasing order)
            //auto for_loops = std::make_unique<core::Fors>();
            //for_loops->make_fors(gd);

            /// 3. Call STRIPS constructor
            //auto strips = std::make_unique<core::STRIPS>(grounder.get(), gd);

            /// 4. Call RAM constructor
            auto ram = std::make_unique<core::RAM>();
            /// 4.a Pointer modifiers (can be inferred from the instance)
            //ram->inc_ptr(gd);
            //ram->dec_ptr(gd);
            //ram->set_ptr(gd);
            /// 4.b Register conditionals and modifiers
            ram->test_reg(grounder.get(), gd, {"action_"});
            //ram->cmp_regs(grounder.get(), gd);
            ram->set_reg(grounder.get(), gd, {"action_"}); // either to 0 or 1
            /// 4.c Generate features
            gd->add_flag(std::make_unique<variables::ZeroFlag>());
            //gd->add_flag(std::make_unique<variables::CarryFlag>());

            /// 5.(PRE) ActionSchemas has a fix upperbound of program lines, so fix it here (right before IFs):
            size_t n_test_ins = 0u, n_set_ins = 0u;
            for(const auto& ins : gd->get_instructions()){
                auto test_ins = dynamic_cast<instructions::RegisterTest*>(ins);
                if(test_ins){++n_test_ins; continue;}
                auto set_ins = dynamic_cast<instructions::RegisterSet*>(ins);
                if(set_ins){++n_set_ins;}
            }
            // Upper bound in program lines = 1 + 2 * TEST + 1/2 * SET; since there is at least one END instruction,
            // each TEST is followed by an IF, and only one of the two possible SET instructions (0 or 1) can be
            // assigned to each fact
            assert( (n_set_ins&1)==0u );
            gd->set_program_lines(1u + 2*n_test_ins + (n_set_ins/2));

            /// 5. Call Ifs constructor
            auto ifs = std::make_unique<core::Ifs>();
            ifs->make_ifs(grounder.get(), gd);
        }

        // ToDo: would it be better to add a is_conditional flag in instruction.h and derived classes?
        static bool is_conditional_name(const std::string &ins_name) {
            return ins_name.substr(0, 4) == "test";
        }

        static std::vector<value_t> evaluate_test_instruction(GeneralizedDomain *gd,
                                                              instructions::Instruction *instruction,
                                                              Program *prog,
                                                              Instance *instance){
            auto ps = prog->make_program_state(gd, instance->get_initial_state());
            prog->reset_program_state(ps.get(), instance);
            auto res = instruction->apply(instance, ps.get());
            prog->update_flags(ps.get(), res);
            std::vector<value_t> flag_res;
            for(const auto& f : ps->get_flags())
                flag_res.emplace_back((f->get_value()>0?1:0));
            return flag_res;
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override{
            /// 0. END constraints
            auto ins_end = dynamic_cast<instructions::End*>(new_ins);
            if(ins_end){
                /// If it is the last line, then it must be programmed
                if(program_line+1 == p->get_num_instructions()) return true;
                /// In any other case, it must be programmed after a SET instruction
                if(program_line>0) {
                    auto prev_ins_set = dynamic_cast<instructions::RegisterSet *>(p->get_instruction(program_line - 1));
                    if(prev_ins_set) return true;
                }
                /// Otherwise is wrong
                return false;
            }

            /// 1. IF syntactic constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);

            /// 1.a if the previous instruction is TEST, the current instruction must be an IF
            bool is_prev_cond = program_line>0 and
                                is_conditional_name(p->get_instruction(program_line-1)->get_name(false));

            if(ins_if == nullptr and is_prev_cond) return false;

            if (ins_if) {
                /// 1.b An IF cannot be programmed in the first line, or after program_lines-4
                if(program_line == 0) return false;
                if(program_line > p->get_num_instructions()-4) return false;

                /// 1.c An IF must be programmed after a TEST or CMP instruction
                auto prev_ins = p->get_instruction(program_line-1);
                if(not is_conditional_name(prev_ins->get_name(false))) return false;

                /// 1.d An IF must be a forward jump to last line
                auto dest_line = ins_if->get_destination_line();
                if(dest_line + 1 != p->get_num_instructions()) return false;
                return true;
            }

            /// 2. TEST must be programmed right after an IF and not in the last 4 lines
            auto new_ins_name = new_ins->get_name(false);
            if(is_conditional_name(new_ins_name)){
                /// 2.a First line can be used for a conditional
                if(program_line == 0) return true;
                /// 2.b Last 4 lines cannot be used by a conditional
                if(program_line + 4 >= p->get_num_instructions()) return false;
                /// 2.c In any other case the previous instruction must be an IF
                auto prev_ins_if = dynamic_cast<instructions::If*>(p->get_instruction(program_line-1));
                if(prev_ins_if == nullptr) return false;
                /// 2.d Explore TEST instructions in lexicographically ascending order
                for(size_t line=0;line<program_line;line++){
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(line));
                    if(prev_ins_test and prev_ins_test->get_id() >= new_ins->get_id()){
                        return false;
                    }
                }
                return true;
            }

            /// 3. SET constraints
            auto ins_set_reg = dynamic_cast<instructions::RegisterSet*>(new_ins);
            if(ins_set_reg){
                auto current_name = ins_set_reg->get_name(false);
                auto current_fact_name = ins_set_reg->get_fact_name(false);
                /// 3.a At least one IF required, thus program_line >= 2
                if(program_line < 2) return false;
                /// 3.b Previous instruction must be either an IF or SET
                auto prev_ins = p->get_instruction(program_line-1);
                auto prev_ins_if = dynamic_cast<instructions::If*>(prev_ins);
                auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(prev_ins);
                if(prev_ins_if == nullptr and prev_ins_set == nullptr) return false;

                /// (OLD) 3.c If the previous instruction is a SET, check that the modified fact is different
                //if(prev_ins_set and prev_ins_set->get_fact_name(false) == current_fact_name) return false;
                /// 3.c The current_fact_name must be different from any previous SET
                for(size_t prev_line = program_line-1; prev_line > 0; --prev_line){
                    prev_ins_set = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(prev_line));
                    if(prev_ins_set == nullptr) break;
                    if(prev_ins_set->get_fact_name(false) == current_fact_name) return false;
                }

                /// 3.d For each SET(*,0) over a fact, the same fact must appear in a TEST instruction
                /*if(ins_set_reg->get_value()==0) {
                    bool test_fact_found = false;
                    for (size_t line = 0; line < program_line; line++) {
                        auto prev_ins_test = dynamic_cast<instructions::RegisterTest *>(p->get_instruction(line));
                        if (prev_ins_test and prev_ins_test->get_fact_name(false) == current_fact_name) {
                            test_fact_found = true;
                            break;
                        }
                    }
                    if (not test_fact_found) return false;
                }*/

                /// 3.e Explore SET instructions in lexicographical ascending order
                /*for(size_t line=0; line < program_line; line++){
                    auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(line));
                    if(prev_ins_set and prev_ins_set->get_id() >= new_ins->get_id()) return false;
                }*/
            }

            // Any other case is correct
            return true;
        }

        [[nodiscard]] bool check_semantic_constraints(GeneralizedPlanningProblem *gpp, Program *p, size_t program_line,
                                                      instructions::Instruction *new_ins) override{
            /// 1. TEST semantic constraints
            auto ins_test = dynamic_cast<instructions::RegisterTest*>(new_ins);
            if(ins_test){
                /// 1.a. The new instruction can only use pointers of the action in init (inefficient)
                auto ptrs_new_ins = ins_test->get_pointers();
                for(size_t instance_id = 0; instance_id < gpp->get_num_instances(); ++instance_id){
                    //if(gpp->is_progressive() and (not gpp->is_instance_active(instance_id))) continue;
                    auto facts = gpp->get_instance(instance_id)->get_initial_state()->get_facts();
                    for(const auto& f : facts){
                        if(f->get_function()->get_name().find("action_") == std::string::npos) continue;
                        auto params_act = f->get_function()->get_parameters();
                        std::map<std::string,int> pointer_counter;
                        std::set<std::string> ptrs_names_act;
                        for(const auto& param : params_act){
                            auto type_name = param->get_type()->get_name();
                            ptrs_names_act.insert("ptr_" + type_name + "_" + std::to_string(pointer_counter[type_name]));
                            pointer_counter[type_name] += 1;
                        }

                        for(const auto& ptr_new_ins : ptrs_new_ins){
                            if(ptrs_names_act.find(ptr_new_ins->get_name()) == ptrs_names_act.end())
                                return false;  // the pointer used in the new instruction does not exist in the action
                        }
                    }
                }

                /// 1.b. If it is a TEST, all instances must agree on the fact value
                auto gd = gpp->get_generalized_domain();
                auto flag_evals = evaluate_test_instruction(gd, new_ins, p, gpp->get_instance(0));
                for(size_t instance_id = 1; instance_id < gpp->get_num_instances(); instance_id++){
                    auto new_flag_evals = evaluate_test_instruction(gd, new_ins, p, gpp->get_instance(instance_id));
                    if(flag_evals != new_flag_evals){
//std::cout << "A. NOT ALL INSTANCES AGREE ON " << program_line << ". " << new_ins->to_string(false) << "\n" << p->to_string(false) << std::endl;
                        return false;
                    }
                }
            }

            /// 2. If it is an IF, it must ZF=0 if all instances agree on TRUE, and ZF=1 if all instances agree on FALSE
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);
            if(ins_if){
                assert(program_line > 0);
                auto prev_test_ins = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-1));
                assert(prev_test_ins != nullptr);
                auto gd = gpp->get_generalized_domain();
                std::vector<value_t> flag_evals;
                for(const auto& c : ins_if->get_conds())
                    flag_evals.emplace_back(c.second);
                for(size_t instance_id = 0; instance_id < gpp->get_num_instances(); instance_id++){
                    auto new_flag_evals = evaluate_test_instruction(gd, prev_test_ins, p, gpp->get_instance(instance_id));
                    if(flag_evals != new_flag_evals) {
//std::cout << "B. NOT ALL INSTANCES AGREE ON " << program_line << ". " << new_ins->to_string(false) << "\n" << p->to_string(false) << std::endl;
                        return false;
                    }
                }
            }

            /// Otherwise, it is a semantically correct instruction
            return true;
        }
    };
}

#endif //__THEORY_ACTION_SCHEMAS_H__
