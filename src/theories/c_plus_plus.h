//
// Created by js on 31/08/22.
//

#ifndef __THEORY_C_PLUS_PLUS_H__
#define __THEORY_C_PLUS_PLUS_H__

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
    class CPlusPlus : public Theory{
    public:
        CPlusPlus() : Theory("CPP"){}

        static void build_theory(GeneralizedDomain *gd){
            auto grounder = std::make_unique<Grounder>();

            /// 1. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(gd);

            /// 2. Call Fors constructor (in increasing and decreasing order)
            auto for_loops = std::make_unique<core::Fors>();
            for_loops->make_fors(gd, 1);
            for_loops->make_fors(gd, -1);

            /// 3. Call STRIPS constructor
            auto strips = std::make_unique<core::STRIPS>(grounder.get(), gd);

            /// 4. Call RAM constructor
            auto ram = std::make_unique<core::RAM>();
            /// 4.a Pointer modifiers
            ram->inc_ptr(gd);
            ram->dec_ptr(gd);
            ram->set_ptr(gd);
            /// 4.b Pointer and Register comparison
            ram->cmp_ptrs(gd);
            ram->test_reg(grounder.get(), gd);
            ram->cmp_regs(grounder.get(), gd);
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

        bool check_if_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins){
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);
            auto prev_ins = (program_line>0?p->get_instruction(program_line-1): nullptr);
            if(ins_if){
                /// 2.a An IF cannot be programmed in the first line
                if(program_line == 0) return false;

                /// 2.b An IF must be programmed after a TEST or CMP instruction
                if((nullptr == prev_ins) or (not prev_ins->is_conditional())) return false;

                /// 2.c An IF must be a forward jump and size>1, i.e., destination line >= program line + 2
                auto dest_line = ins_if->get_destination_line();
                if(dest_line < program_line+2) return false;

                /// 2.d An IF cannot be programmed in the last two lines
                if(program_line+2 >= p->get_num_instructions()) return false;

                /// 2.e Structured programming requires that the IF either encapsulates loops or is encapsulated by them
                for(size_t for_orig_line = 0; for_orig_line < dest_line; for_orig_line++){
                    auto for_ins = dynamic_cast<instructions::For*>(p->get_instruction(for_orig_line));
                    if(nullptr == for_ins) continue;  // Skip the instruction if it is not a FOR
                    auto for_dest_line = for_ins->get_destination_line();
                    if(for_dest_line < program_line) continue; // FOR and IF do not overlap
                    if(for_orig_line < program_line and dest_line <= for_dest_line) continue; // FOR encapsulates IF
                    if(program_line < for_orig_line and for_dest_line < dest_line) continue; // IF encapsulates FOR
                    // Otherwise, the IF and the FOR do not follow the structured programming paradigm
                    return false;
                }

                /// 2.f.1 Structured programming requires nested IF instructions to be well encapsulated
                for (size_t prev_if_orig_line = 0; prev_if_orig_line < dest_line; prev_if_orig_line++) {
                    auto ins_prev_if = dynamic_cast<instructions::If*>(p->get_instruction(prev_if_orig_line));
                    if(nullptr == ins_prev_if) continue; // Skip the instruction if it is not an IF
                    auto prev_if_dest_line = ins_prev_if->get_destination_line();
                    if(prev_if_dest_line < program_line) continue; // Both IFs do not overlap
                    // Previous IF instruction encapsulates the new IF instruction
                    if((prev_if_orig_line+1 < program_line) and (prev_if_dest_line >= dest_line)) continue;
                    // New IF instruction encapsulates the previous IF instruction
                    if((program_line+1 < prev_if_orig_line) and (dest_line >= prev_if_dest_line)) continue;
                    // Otherwise, the IF instructions do not follow the structured programming paradigm
                    return false;
                }
                /// 2.f.2 (Special case) destination line of the new IF cannot contain an IF instruction
                if(dynamic_cast<instructions::If*>(p->get_instruction(dest_line))) return false;

                return true;
            }
            /// 2.g If the previous instruction is a conditional, the current instruction must be an IF
            if((nullptr != prev_ins) and prev_ins->is_conditional()) return false;
            return true;
        }

        bool check_conditional_constraints(Program *p, size_t program_line){
            /// 3.a A conditional instruction cannot be programmed in the last two lines
            if(program_line + 2 >= p->get_num_instructions()) return false;

            /// 3.b A conditional instruction cannot be programmed in...
            for(size_t line = 0; line < program_line; line++){
                /// 3.b.1 the last two lines of a FOR loop
                auto for_ins = dynamic_cast<instructions::For*>(p->get_instruction(line));
                if(for_ins and line < program_line and program_line < for_ins->get_destination_line() and
                    for_ins->get_destination_line() <= program_line+2) return false;
                /// 3.b.2 the last line of an IF instruction
                auto if_ins = dynamic_cast<instructions::If*>(p->get_instruction(line));
                if(if_ins and line < program_line and program_line < if_ins->get_destination_line() and
                    if_ins->get_destination_line() <= program_line+1) return false;
            }

            return true;
        }

        bool check_pointer_action_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins){
            auto pa = dynamic_cast<instructions::PointerAction*>(new_ins);
            /// 4.a check only PointerActions that are not TEST or CMP
            if(nullptr == pa or pa->is_conditional()) return true;

            /// 4.b check whether there is a loop that contains this PointerAction where both modify the same pointer
            auto pa_modified_ptr = pa->get_pointers()[0];
            for(size_t line = 0; line < program_line; line++){
                auto for_ins = dynamic_cast<instructions::For*>(p->get_instruction(line));
                if(nullptr == for_ins) continue;
                // Return false if the new instruction is inside a loop and modify the loop pointer
                if(program_line < for_ins->get_destination_line() and (for_ins->get_pointer() == pa_modified_ptr))
                    return false;
            }
            return true;
        }

        bool check_for_pointer_constraints(variables::Pointer* ptr1, variables::Pointer* ptr2){
            /// Returns true when the given pointers are of different types, or if ptr1 is lexicographically smaller
            /// than ptr2 when they are of the same type. Otherwise, it returns false.
            if(ptr1->get_type() != ptr2->get_type()) return true;
            if(ptr1->get_name() < ptr2->get_name()) return true;
            return false;
            // ToDo (Issue #2): the idea is to force exploration of typed pointers in a specific and unique order
        }

        bool check_for_constraints(Program *p, size_t program_line, instructions::For *for_ins){
            auto for_ptr = for_ins->get_pointer();
            auto dest_line = for_ins->get_destination_line();
            /// 5.a A FOR is a forward jump with size>1
            if(dest_line < program_line+2) return false;

            /// 5.b Structured programming require FOR loops either to not overlap or to be one inside the other
            for(size_t line = 0; line < dest_line; line++){
                auto prev_for_ins = dynamic_cast<instructions::For*>(p->get_instruction(line));
                if(nullptr == prev_for_ins) continue;
                auto prev_for_ptr = prev_for_ins->get_pointer();
                auto prev_dest_line = prev_for_ins->get_destination_line();
                /// 5.b.1 FOR loops do not overlap
                if(prev_dest_line < program_line) continue;
                /// 5.b.2 Otherwise, they overlap, but they cannot modify the same pointer
                if(prev_for_ptr == for_ptr) return false;
                /// 5.b.3 Previous FOR is inside the new FOR, and if they modify the same pointer types, the new FOR
                ///       must use a lexicographically smaller one
                if(program_line < line and
                   prev_dest_line < dest_line and
                   check_for_pointer_constraints(for_ptr, prev_for_ptr)) continue;
                /// 5.b.4 New FOR is inside previous FOR, and if they modify the same pointer types, the previous FOR
                ///       must use a lexicographically smaller one
                if(line < program_line and
                   dest_line < prev_dest_line and
                   check_for_pointer_constraints(prev_for_ptr, for_ptr)) continue;
                /// 5.b.5 Any other case is an incorrect loop nesting
                return false;
            }

            /// 5.c Structure programming requires FOR and IF instructions to be one inside the other
            for(size_t line=0; line < dest_line; line++){
                auto if_ins = dynamic_cast<instructions::If*>(p->get_instruction(line));
                if(nullptr == if_ins) continue;
                auto if_dest_line = if_ins->get_destination_line();
                if(if_dest_line <= program_line) continue; // The FOR and the IF do not overlap
                if(line < program_line and dest_line < if_dest_line) continue; // The FOR is inside the IF
                if(program_line < line and if_dest_line <= dest_line) continue; // The IF is inside the FOR
                return false; // Otherwise, they are not structured
            }

            /// 5.d FOR and PointerAction constraints
            if(program_line > 0){
                /// 5.d.1 If the previous instruction is a PointerAction, it shouldn't modify the same for_ptr
                auto ins_ptr = dynamic_cast<instructions::PointerAction*>(p->get_instruction(program_line - 1));
                if(ins_ptr and ins_ptr->get_pointers()[0] == for_ptr) return false;
            }
            /// 5.d.2 A FOR cannot be programmed if there is a PointerAction inside that modify the same pointer
            for(size_t line = program_line+1; line < dest_line; line++){
                auto pa = dynamic_cast<instructions::PointerAction*>(p->get_instruction(line));
                if(nullptr == pa or pa->is_conditional()) continue;
                if(pa->get_pointers()[0] == for_ptr) return false;
            }

            return true;
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override{
            /// 1. EndFor syntactic constraints
            auto endfor_ins = dynamic_cast<instructions::EndFor*>(new_ins);
            bool endfor_constraints = check_endfor_constraints(p, program_line, new_ins);
            if(endfor_ins) return endfor_constraints;  // If the instruction is an EndFor return its result
            else if(not endfor_constraints) return false; // Return false if it should be an EndFor, but it is not

            /// 2. IF syntactic constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);
            bool if_constraints = check_if_constraints(p, program_line, new_ins);
            if(ins_if) return if_constraints; // If the instruction is an IF return its result
            else if(not if_constraints) return false; // Return false if it should be an IF, but it is not

            /// 3. TEST and CMP syntactic constraints
            if(new_ins->is_conditional())
                return check_conditional_constraints(p, program_line);

            /// 4. PointerAction syntactic constraints
            auto pa = dynamic_cast<instructions::PointerAction*>(new_ins);
            // If it is non-conditional PointerAction, return its results
            if(nullptr != pa and (not pa->is_conditional()))
                return check_pointer_action_constraints(p, program_line, new_ins);

            /// 5. FOR syntactic constraints
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            if(ins_for)
                return check_for_constraints(p, program_line, ins_for);

            // Any other case is correct
            return true;
        }

        /*[[nodiscard]] bool check_semantic_constraints(
         * GeneralizedPlanningProblem *gpp,
         * Program *p,
         * size_t program_line,
         * instructions::Instruction *new_ins){
            /// (ToDo) Issue #9: do not loop over single object pointers
        }*/
    };
}

#endif //__THEORY_C_PLUS_PLUS_H__
