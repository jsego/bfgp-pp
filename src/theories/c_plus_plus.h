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

        typedef std::tuple<std::string, int, size_t, size_t> loop_pattern_t;

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


        // ToDo: CPP specific function
        static std::vector<loop_pattern_t> get_loops_pattern(Program* p) {
            std::vector<loop_pattern_t> loops_pattern;
            auto instructions = p->get_instructions();
            for (size_t line = 0; line < instructions.size(); line++) {
                auto ins_for = dynamic_cast<instructions::For*>(instructions[line]);
                if (ins_for) {
                    loops_pattern.emplace_back(
                            std::make_tuple(
                                    ins_for->get_pointer()->get_type()->get_name(),
                                    ins_for->get_modifier(),
                                    line,
                                    ins_for->get_destination_line()));
                }
            }
            return loops_pattern;
        }

        // ToDo: would it be better to add a is_conditional flag in instruction.h and derived classes?
        static bool is_conditional_name(const std::string &ins_name) {
            return ((ins_name.substr(0, 4) == "test") or
                    (ins_name.substr(0, 3) == "cmp"));
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override{
            /// Issue #8: do not loop over single object pointers (ToDo: no access to pointer domain from the instance)

            auto endfor_ins = dynamic_cast<instructions::EndFor*>(new_ins);
            if(endfor_ins) return false;
            //if (dynamic_cast<instructions::EndFor*>(new_ins)) return false;  // EndFor only programmed once For is programmed

            /// 1. IF syntactic constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);

            /// 1.a if the previous instruction is CMP or TEST, the current instruction must be an IF
            auto prev_ins = (program_line>0?p->get_instruction(program_line-1): nullptr);
            //bool is_prev_cond = program_line>0 and
            //                    is_conditional_name(p->get_instruction(program_line-1)->get_name(false));
            if(ins_if == nullptr and prev_ins != nullptr and is_conditional_name(prev_ins->get_name(false)))
                return false;

            if (ins_if) {
                /// 1.b An IF cannot be programmed in the first line
                if(program_line == 0) return false;

                /// 1.c An IF must be programmed after a TEST or CMP instruction
                //auto prev_ins = p->get_instruction(program_line-1);
                //if(not is_conditional_name(prev_ins->get_name(false))) return false;
                if(prev_ins == nullptr or not is_conditional_name(prev_ins->get_name(false))) return false;

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
            bool is_cond = is_conditional_name(new_ins->get_name(false));
            if(is_cond and program_line + 2 < p->get_num_instructions()) { // A conditional cannot be programmed in the last two lines
                for (auto next_line = program_line+1; next_line<program_line+3; next_line++) {
                    auto next_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(next_line));
                    if (next_endfor) return false;
                }
            }
            else if(is_cond) return false;

            /// 3. If it is a PointerAction, it must be checked that the pointer is not inside a loop that modifies it
            auto pa = dynamic_cast<instructions::PointerAction*>(new_ins);
            if ((not is_cond) and pa) { /// conditionals should not be checked, since they do not modify pointers
                auto pa_ptrs = pa->get_pointers();
                for(int prev_line = int(program_line)-1; prev_line >= 0; prev_line--){
                    auto prev_for = dynamic_cast<instructions::For*>(p->get_instruction(prev_line));
                    if(nullptr == prev_for) continue;
                    if((prev_for->get_destination_line() > program_line) and (prev_for->get_pointer() == pa_ptrs[0]))
                        return false;
                }
            }

            /// 4. FOR syntactic constraints
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            if (ins_for) {
                auto for_ptr = ins_for->get_pointer();
                auto dest_line = ins_for->get_destination_line();
                /// 4.a A FOR is a forward jump with size>1
                if(dest_line < program_line+2) return false;

                for (int prev_line = program_line - 1; prev_line >= 0; prev_line--) {
                    auto prev_for = dynamic_cast<instructions::For*>(p->get_instruction(prev_line));
                    if (prev_for) {
                        auto prev_for_ptr = prev_for->get_pointer();
                        auto prev_dest_line = prev_for->get_destination_line();
                        /// If they are not nested continue
                        if( prev_dest_line < program_line ) continue;
                        /// 4.b Otherwise, current FOR must be exactly inside previous FOR
                         if( prev_dest_line <= dest_line ) return false;
                        /// 4.c Nested loops cannot be over the same pointer variables
                        if( for_ptr == prev_for_ptr ) return false;
                    }
                }

                /// 4.d A previous IF instruction can not end up in the middle of a FOR instruction
                for (int prev_line = program_line - 1; prev_line >= 0; prev_line--) {
                    auto prev_if = dynamic_cast<instructions::If*>(p->get_instruction(prev_line));
                    if (prev_if) {
                        auto dest_if_line = prev_if->get_destination_line();
                        if (program_line < dest_if_line and dest_if_line <= dest_line) return false;
                    }
                }

                if(program_line > 0) {
                    /// 4.e If the previous instruction is a PointerAction, it shouldn't modify the same for_ptr
                    auto ins_ptr = dynamic_cast<instructions::PointerAction*>(p->get_instruction(program_line - 1));
                    if(ins_ptr and ins_ptr->get_pointers()[0] == for_ptr) return false;
                }

                /// 4.X This must be the last constraint to check
                // Check at this point if the loop pattern is new, getting the current loop pattern variables and
                // adding them to the partial program loop pattern.
                auto new_loop_pattern = get_loops_pattern(p);
                // Add new tuple
                new_loop_pattern.emplace_back(std::make_tuple(ins_for->get_pointer()->get_type()->get_name(),
                                                              ins_for->get_modifier(),
                                                              program_line,
                                                              dest_line));
                if(_loop_patterns.find(new_loop_pattern) != _loop_patterns.end())
                    return false;
            }

            // Any other case is correct
            return true;
        }

        void update(Program *p, instructions::Instruction *last_ins) override{
            auto ins_for = dynamic_cast<instructions::For*>(last_ins);
            if(ins_for)
                _loop_patterns.insert(get_loops_pattern(p));
        }

    private:
        std::set<std::vector<loop_pattern_t>> _loop_patterns;
    };
}

#endif //__THEORY_C_PLUS_PLUS_H__
