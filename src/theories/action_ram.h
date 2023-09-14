//
// Created by js on 31/08/22.
//

#ifndef __THEORY_ACTION_RAM_H__
#define __THEORY_ACTION_RAM_H__

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
    class ActionRAM : public Theory{
    public:
        ActionRAM() : Theory("ActionRAM"){}

        [[nodiscard]] bool is_action_theory() const override{return true;}

        static void build_theory(GeneralizedDomain *gd){
            auto grounder = std::make_unique<Grounder>();

            /// 1. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(gd);

            /// 2. Call Fors constructor (in increasing and decreasing order)
            auto for_loops = std::make_unique<core::Fors>();
            for_loops->make_fors(gd, 1);
            for_loops->make_fors(gd, -1);

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
            ram->cmp_regs(grounder.get(), gd, {"action_"});
            ram->set_reg(grounder.get(), gd, {"action_"});
            ram->assign_regs(grounder.get(), gd, {"action_"});
            /// 4.c Generate features
            gd->add_flag(std::make_unique<variables::ZeroFlag>());
            gd->add_flag(std::make_unique<variables::CarryFlag>());

            /// 5. Call Ifs constructor
            auto ifs = std::make_unique<core::Ifs>();
            ifs->make_ifs(grounder.get(), gd);
        }

        bool check_endfor_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins){
            auto endfor_ins = dynamic_cast<instructions::EndFor*>(new_ins);
            if(endfor_ins) {
                auto orig_line = endfor_ins->get_original_line();
                if(program_line <= orig_line) return false;
                auto for_ins = dynamic_cast<instructions::For*>(p->get_instruction(orig_line));
                if(nullptr == for_ins) return false;
                if(program_line != for_ins->get_destination_line()) return false;
                if(for_ins->get_pointer() != endfor_ins->get_pointer()) return false;
                if(for_ins->get_modifier() != endfor_ins->get_modifier()) return false;
                return true;
            }
            // Otherwise, only EndFor instructions can be programmed in For destination lines
            for(size_t prev_line = 0; prev_line < program_line; ++prev_line){
                auto for_ins = dynamic_cast<instructions::For*>(p->get_instruction(prev_line));
                if(nullptr == for_ins) continue;
                if(for_ins->get_destination_line() == program_line) return false;
            }
            return true;
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override {
            auto endfor_ins = dynamic_cast<instructions::EndFor*>(new_ins);
            bool endfor_constraints = check_endfor_constraints(p, program_line, new_ins);
            if(endfor_ins) return endfor_constraints;  // If the instruction is an EndFor return its result
            else if(not endfor_constraints) return false; // Return false if it should be an EndFor, but it is not

            /// 1. IF syntactic constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);

            /// 1.a if the previous instruction is CMP or TEST, the current instruction must be an IF
            instructions::Instruction* prev_ins = (program_line>0?p->get_instruction(program_line-1): nullptr);
            if((nullptr == ins_if) and prev_ins and prev_ins->is_conditional())
                return false;

            if (ins_if) {
                /// 1.b An IF cannot be programmed in the first line
                if(program_line == 0) return false;

                /// 1.c An IF must be programmed after a TEST or CMP instruction
                if(nullptr == prev_ins) return false;
                if(not prev_ins->is_conditional()) return false;

                /// 1.d An IF must be a forward jump and size>1, i.e., destination line >= program line + 2
                auto dest_line = ins_if->get_destination_line();
                if(dest_line < program_line+2) return false;

                /// 1.e An IF cannot be programmed in the last two lines
                if(program_line+2 >= p->get_num_instructions()) return false;

                /// 1.f Structured programming requires that loops programmed before the IF
                /// do not end inside the IF instruction
                for (auto next_line = program_line + 1; next_line < dest_line; next_line++) {
                    if (dynamic_cast<instructions::EndFor*>(p->get_instruction(next_line)))
                        return false;
                }

                /// 1.g Structured programming requires previous IF instructions to jump before the starting
                /// line of the current IF, or to the same destination line or after
                for (size_t prev_line = 0; prev_line < program_line; prev_line++) {
                    auto ins_prev_if = dynamic_cast<instructions::If*>(p->get_instruction(prev_line));
                    if (ins_prev_if) {
                        auto prev_dest_line = ins_prev_if->get_destination_line();
                        if((prev_dest_line >= program_line) and (prev_dest_line < dest_line)) return false;
                    }
                }
            }

            /// 2. Issue #10: if the instruction is a TEST or CMP but there is an ENDFOR in the next two lines, skip it
            bool is_cond = new_ins->is_conditional();
            if(is_cond and program_line + 2 < p->get_num_instructions()) { // A conditional cannot be programmed in the last two lines
                for (auto next_line = program_line+1; next_line<program_line+3; next_line++) {
                    auto next_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(next_line));
                    if (next_endfor) return false;
                }
            }
            else if(is_cond) return false;

            /// 3. If it is a PointerAction, it must be checked that the pointer is not inside a loop that modifies it
            auto pa = dynamic_cast<instructions::PointerAction*>(new_ins);
            if (pa) {
                auto pa_ptrs = pa->get_pointers();
                for(auto next_line = program_line+1; next_line < p->get_num_instructions(); next_line++){
                    auto next_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(next_line));
                    if(next_endfor and next_endfor->get_pointer() == pa_ptrs[0]) return false;
                }
            }

            /// 4. FOR syntactic constraints
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            if (ins_for) {
                auto for_ptr = ins_for->get_pointer();
                auto dest_line = ins_for->get_destination_line();
                /// 4.a A FOR is a forward jump with size>1
                if (dest_line < program_line + 2) return false;

                for (int prev_line = int(program_line) - 1; prev_line >= 0; prev_line--) {
                    auto prev_for = dynamic_cast<instructions::For *>(p->get_instruction(prev_line));
                    if (prev_for) {
                        auto prev_for_ptr = prev_for->get_pointer();
                        auto prev_dest_line = prev_for->get_destination_line();
                        /// If they are not nested continue
                        if (prev_dest_line < program_line) continue;
                        /// 4.b Otherwise, current FOR must be exactly inside previous FOR
                        if (prev_dest_line <= dest_line) return false;
                        /// 4.c Nested loops cannot be over the same pointer variables
                        if (for_ptr == prev_for_ptr) return false;
                    }
                }

                /// 4.d A previous IF instruction can not end up in the middle of a FOR instruction
                for (int prev_line = int(program_line) - 1; prev_line >= 0; prev_line--) {
                    auto prev_if = dynamic_cast<instructions::If *>(p->get_instruction(prev_line));
                    if (prev_if) {
                        auto dest_if_line = prev_if->get_destination_line();
                        if (program_line < dest_if_line and dest_if_line <= dest_line) return false;
                    }
                }

                if (program_line > 0) {
                    /// 4.e If the previous instruction is a PointerAction, it shouldn't modify the same for_ptr
                    auto ins_ptr = dynamic_cast<instructions::PointerAction *>(p->get_instruction(program_line - 1));
                    if (ins_ptr and ins_ptr->get_pointers()[0] == for_ptr) return false;
                }
            }
            // Any other case is correct
            return true;
        }


        [[nodiscard]] bool check_semantic_constraints(GeneralizedPlanningProblem *gpp, Program *p, size_t program_line,
                                                      instructions::Instruction *new_ins) override{
            /// All true by default
            return true;
        }

    };
}

#endif //__THEORY_ACTION_RAM_H__
