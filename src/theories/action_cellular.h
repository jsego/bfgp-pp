//
// Created by js on 31/08/22.
//

#ifndef __THEORY_ACTION_CELLULAR_H__
#define __THEORY_ACTION_CELLULAR_H__

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
    class ActionCellular : public Theory{
    public:
        ActionCellular() : Theory("ActionCellular"){}

        [[nodiscard]] bool is_action_theory() const override{return true;}

        static void build_theory(GeneralizedDomain *gd){
            auto grounder = std::make_unique<Grounder>();

            /// 1. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(gd);

            /// 2. Call Fors constructor (in increasing and decreasing order)
            auto for_loops = std::make_unique<core::Fors>();
            for_loops->make_fors(gd, 1);

            /// 3. Call STRIPS constructor
            //auto strips = std::make_unique<core::STRIPS>(grounder.get(), gd);

            /// 4. Call RAM constructor
            auto ram = std::make_unique<core::RAM>();
            /// 4.a Pointer modifiers
            ram->inc_ptr(gd);
            ram->dec_ptr(gd);
            ram->set_ptr(gd);
            ram->cmp_ptrs(gd);
            /// 4.b Register conditionals and modifiers
            ram->test_reg(grounder.get(), gd, {"action_"});
            //ram->cmp_regs(grounder.get(), gd);
            ram->set_reg(grounder.get(), gd, {"action_"}); // either to 0 or 1
            /// 4.c Generate features
            gd->add_flag(std::make_unique<variables::ZeroFlag>());
            //gd->add_flag(std::make_unique<variables::CarryFlag>());

            /// 5. Call Ifs constructor
            auto ifs = std::make_unique<core::Ifs>();
            ifs->make_ifs(grounder.get(), gd);
        }

        void set_initial_program(GeneralizedPlanningProblem *gpp, Program *p){
            /// Minimum program example (>9 program lines):
            /// 0. FOR;
            /// 1. z2=z1; 2. z2--;
            /// 3. z3=z1; 4. z3++;
            /// 5. TEST; 6. IF; 7. SET_REG
            /// 8. ENDFOR 9. END
            auto gd = gpp->get_generalized_domain();
            size_t program_lines = gd->get_program_lines();
            std::vector<std::string> instruction_names = {
              "for(ptr_object_0++," + std::to_string(program_lines-2)+")",
              "set(ptr_object_1:object,ptr_object_0:object)",
              "dec(ptr_object_1:object)",
              "set(ptr_object_2:object,ptr_object_0:object)",
              "inc(ptr_object_2:object)"
            };
            int comb=0; // equivalent to bitset<3>
            for(size_t line = 5; line+2 < program_lines; comb++){
                size_t dest_line = line + 11u; // at least 11 instructions added
                //size_t dest_line = line + 7u; // at least 7 instructions added
                std::string dest_name = std::to_string(dest_line);
                instruction_names.emplace_back("test(cell(ptr_object_0:object))"); ++line; // [line].
                instruction_names.emplace_back("if((zf="+std::to_string(comb&1)+"),"+dest_name+ ")"); ++line; // [line+1].

                bool cmp_ptr_1 = ((comb>>1)&1)==0;
                bool cmp_ptr_2 = ((comb>>2)&1)==0;
                if(cmp_ptr_1){
                    // If left should be alive but left=center, jump to dest_line
                    instruction_names.emplace_back("cmp(ptr_object_0:object,ptr_object_1:object)"); ++line;
                    instruction_names.emplace_back("if((zf=0),"+dest_name+")"); ++line;
                }
                else{
                    // If left should be dead, ignore it if left=center, and jump to next_condition
                    instruction_names.emplace_back("cmp(ptr_object_0:object,ptr_object_1:object)"); ++line;
                    instruction_names.emplace_back("if((zf=0),"+std::to_string(line+3)+")"); ++line;
                }
                instruction_names.emplace_back("test(cell(ptr_object_1:object))"); ++line; // [line+2].
                instruction_names.emplace_back("if((zf="+std::to_string((comb>>1)&1)+"),"+dest_name+ ")"); ++line; // [line+3].
                if(cmp_ptr_2){
                    // If right should be alive but center=right, jump to dest_line
                    instruction_names.emplace_back("cmp(ptr_object_0:object,ptr_object_2:object)"); ++line;
                    instruction_names.emplace_back("if((zf=0),"+dest_name+")"); ++line;
                }
                else{
                    // If right should be dead, ignore it if center=right, and jump to set
                    instruction_names.emplace_back("cmp(ptr_object_0:object,ptr_object_2:object)"); ++line;
                    instruction_names.emplace_back("if((zf=0),"+std::to_string(line+3)+")"); ++line;
                }
                instruction_names.emplace_back("test(cell(ptr_object_2:object))"); ++line; // [line+4].
                instruction_names.emplace_back("if((zf="+std::to_string((comb>>2)&1)+"),"+dest_name+ ")"); ++line; // [line+5].
                instruction_names.emplace_back("empty"); ++line; // [line+6].
            }
            instruction_names.emplace_back("endfor(ptr_object_0++,0)");
            instruction_names.emplace_back("end");
            for(size_t idx=0u; idx < instruction_names.size(); idx++){
                if(instruction_names[idx] == "empty") continue;
                std::cout << "Checking... " <<  instruction_names[idx] << "\n";
                auto instruction = gd->get_instruction(instruction_names[idx]);
                assert(instruction != nullptr);
                p->set_instruction(idx, instruction);
            }
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override {
            /// 1. Only SET(register) are programmable in this theory
            auto ins_set = dynamic_cast<instructions::RegisterSet*>(new_ins);
            if(ins_set) return true;

            /// Otherwise is syntactically wrong
            return false;
        }


        [[nodiscard]] bool check_semantic_constraints(GeneralizedPlanningProblem *gpp, Program *p, size_t program_line,
                                                      instructions::Instruction *new_ins) override{
            /// 1. It must be a set, and only ptr_object_0 is writable
            auto ins_set = dynamic_cast<instructions::RegisterSet*>(new_ins);
            assert(ins_set != nullptr); // checked in syntax
            auto ptrs = ins_set->get_pointers();
            if(ptrs.size() != 1u) return false;
            if(ptrs[0]->get_name() != "ptr_object_0" ) return false;

            /// Otherwise, it is semantically correct
            return true;
        }
        /*[[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override{
            /// 0. END constraints
            auto ins_end = dynamic_cast<instructions::End*>(new_ins);
            if(ins_end){
                /// It must be programmed in the last line
                if(program_line+1u == p->get_num_instructions()) return true;
                /// In any other case, it must be programmed after an ENDFOR instruction
                if(program_line>2u) {
                    auto prev_ins_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(program_line-1));
                    if(prev_ins_endfor) return true;
                }
                /// Otherwise is syntactically wrong
                return false;
            }

            /// 1. FOR constraints (ENDFORs are automatically programmed with the FOR)
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            /// 1.a It must be programmed in the first line
            if(program_line == 0u and ins_for == nullptr) return false;
            if(ins_for){
                /// 1.b It must be programmed in the first line (check only first pointer is applied in semantics)
                if(program_line != 0u) return false;
                /// 1.c It must be at least of size 9 and the endfor must be in line n-2.
                if(ins_for->get_destination_line() < 8) return false;
                if(ins_for->get_destination_line()+2 != p->get_num_instructions()) return false;

                /// Otherwise is syntactically correct
                return true;
            }

            /// 2. POINTER_SET constraints
            auto ins_ptr_set = dynamic_cast<instructions::PointerSet*>(new_ins);
            /// 2.a must be programmed in lines 1. or 3.
            if(ins_ptr_set == nullptr and (program_line==1u or program_line==3u)) return false;
            if(ins_ptr_set){
                /// 2.b must only be in program lines 1. & 3. (check specific ptrs in semantics)
                if(program_line == 1u or program_line == 3u) return true;

                /// Otherwise is syntactically wrong
                return false;
            }

            /// 3. DEC pointer constraints
            auto ins_ptr_dec = dynamic_cast<instructions::PointerDec*>(new_ins);
            /// 3.a it must be programmed in line 2
            if(ins_ptr_dec==nullptr and program_line != 2u) return false;
            if(ins_ptr_dec){
                /// 3.b must be in program line 2
                if(program_line == 2u) return true;

                /// Otherwise is syntactically wrong
                return false;
            }

            /// 4. INC pointer
            auto ins_ptr_inc = dynamic_cast<instructions::PointerDec*>(new_ins);
            /// 4.a it must be programmed in line 4
            if(ins_ptr_inc == nullptr and program_line != 4u) return false;
            if(ins_ptr_inc){
                /// 4.b must be in program line 4
                if(program_line == 4u) return true;

                /// Otherwise is syntactically wrong
                return false;
            }

            /// 5. TEST register constraints
            auto ins_reg_test = dynamic_cast<instructions::RegisterTest*>(new_ins);
            if(ins_reg_test){
                /// 5.a at least must be programmed in program line 5 and last 4 lines cannot be used by a conditional
                if(program_line<5u or program_line>=p->get_num_instructions()-4) return false;

                /// 5.b previous instruction must be either INC(ptr); IF or SET
                auto prev_ins = p->get_instruction(program_line-1);
                auto prev_ins_if = dynamic_cast<instructions::If*>(prev_ins);
                auto prev_ins_inc = dynamic_cast<instructions::PointerInc*>(prev_ins);
                auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(prev_ins);
                if(prev_ins_if == nullptr and prev_ins_inc == nullptr and prev_ins_set == nullptr) return false;

                /// 5.d Explore nested TEST instructions in lexicographically ascending order
                for(auto line=int(program_line)-2;line>=0; line-=2){
                    // The order of instructions is TEST-IF,
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(line));
                    if(prev_ins_test){
                        if(prev_ins_test->get_id() >= new_ins->get_id()) return false;
                    }
                    else break;
                }

                /// Otherwise is syntactically correct
                return true;
            }

            /// 6. IF constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);

            /// 6.a if the previous instruction is TEST, the current instruction must be an IF
            bool is_prev_cond = false;
            if(program_line>0){
                auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-1));
                if(prev_ins_test) is_prev_cond = true;
            }

            if(ins_if == nullptr and is_prev_cond) return false;

            if(ins_if){
                /// 6.b An IF cannot be programmed in the first line, or after program_lines-4
                if(program_line == 0) return false;
                if(program_line > p->get_num_instructions()-4) return false;

                /// 6.c An IF must be programmed after a TEST instruction
                if(not is_prev_cond) return false;

                /// Otherwise is syntactically correct
                return true;
            }

            /// 7. SET register constraints
            auto ins_set_reg = dynamic_cast<instructions::RegisterSet*>(new_ins);
            if(ins_set_reg){
                auto current_name = ins_set_reg->get_name(false);
                auto current_fact_name = ins_set_reg->get_fact_name(false);
                /// 7.a cannot be programmed before line 7
                if(program_line < 7u) return false;
                /// 7.b Previous instruction must be an IF
                auto prev_ins = p->get_instruction(program_line-1);
                auto prev_ins_if = dynamic_cast<instructions::If*>(prev_ins);
                if(prev_ins_if == nullptr) return false;
                //auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(prev_ins);
                //if(prev_ins_if == nullptr and prev_ins_set == nullptr) return false;
            }

            // Any other case is correct
            return true;
        }

        [[nodiscard]] bool check_semantic_constraints(GeneralizedPlanningProblem *gpp, Program *p, size_t program_line,
                                                      instructions::Instruction *new_ins) override{
            /// 0. There must be exactly 3 pointers
            auto ptrs = gpp->get_generalized_domain()->get_pointers();
            if(ptrs.size() != 3u) return false;
            /// 1. Program lines 0. and n-2. only use pointer 0 (z1) in a for(z1++) [...] endfor(z1++)
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            if(program_line == 0){
                /// 1.a In the first line, only a for can be programmed
                if(ins_for == nullptr) return false;
                /// 1.b It must update the first pointer with ++
                if(ins_for->get_modifier()==1 or ins_for->get_pointer()==ptrs[0]) return true;
                /// 1.c Otherwise, it is a wrong for
                return false;
            }
            /// 1.d If it is not in the first line, FORs cannot be programmed
            if(ins_for) return false;

            /// 2. The program must match the following sketch: 1. z2=z1; 2. dec(z2); 3. z3=z1; 4. inc(z3);
            if(program_line==1){
                auto ins_assign = dynamic_cast<instructions::PointerSet*>(new_ins);
                if(ins_assign == nullptr) return false;
                auto ins_ptrs = ins_assign->get_pointers();
                return (ins_ptrs[0] == ptrs[1]) and (ins_ptrs[1] == ptrs[0]);
            }
            if(program_line==2){
                auto ins_dec = dynamic_cast<instructions::PointerDec*>(new_ins);
                if(ins_dec == nullptr) return false;
                auto ins_ptrs = ins_dec->get_pointers();
                return ins_ptrs.size()==1u and ins_ptrs[0]==ptrs[1];
            }
            if(program_line==3){
                auto ins_assign = dynamic_cast<instructions::PointerSet*>(new_ins);
                if(ins_assign == nullptr) return false;
                auto ins_ptrs = ins_assign->get_pointers();
                return (ins_ptrs[0] == ptrs[2]) and (ins_ptrs[1] == ptrs[0]);
            }
            if(program_line==4){
                auto ins_inc = dynamic_cast<instructions::PointerInc*>(new_ins);
                if(ins_inc == nullptr) return false;
                auto ins_ptrs = ins_inc->get_pointers();
                return ins_ptrs.size()==1u and ins_ptrs[0]==ptrs[2];
            }

            /// Otherwise, it is a semantically correct instruction
            return true;
        }*/
    };
}

#endif //__THEORY_ACTION_CELLULAR_H__
