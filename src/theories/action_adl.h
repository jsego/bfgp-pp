//
// Created by js on 31/08/22.
//

#ifndef __THEORY_ACTION_ADL_H__
#define __THEORY_ACTION_ADL_H__

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
    class ActionADL : public Theory{
    public:
        typedef std::tuple<std::string, int, size_t, size_t> loop_pattern_t;

        ActionADL() : Theory("ActionADL"){}

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
            //ram->inc_ptr(gd);
            //ram->dec_ptr(gd);
            //ram->set_ptr(gd);
            //ram->cmp_ptrs(gd);
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

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override {
            /// Issue #8: do not loop over single object pointers (ToDo: no access to pointer domain from the instance)
            //bool print_data = false;
            //if(program_line == 0 and new_ins->get_name(true)=="for(ptr_object_0++,3)")

            /// 0. END constraints
            auto new_ins_end = dynamic_cast<instructions::End*>(new_ins);
            if(new_ins_end){
                /// 0.a It cannot be programmed after an IF or TEST
                if(program_line>0u) {
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-1));
                    auto prev_ins_if = dynamic_cast<instructions::If*>(p->get_instruction(program_line-1));
                    if((prev_ins_test != nullptr) or (prev_ins_if != nullptr)) return false;
                }
                /// 0.b It cannot be programmed inside a FOR
                for(size_t line=0u; line < program_line; line++){
                    auto prev_for = dynamic_cast<instructions::For*>(p->get_instruction(line));
                    if(prev_for and prev_for->get_destination_line() > program_line) return false;
                }

                /// Otherwise, it is syntactically correct
                return true;
            }

            auto endfor_ins = dynamic_cast<instructions::EndFor*>(new_ins);
            if(endfor_ins) return false;
            //if (dynamic_cast<instructions::EndFor*>(new_ins)) return false;  // EndFor only programmed once For is programmed

            /// 1. IF syntactic constraints
            auto ins_if = dynamic_cast<instructions::If*>(new_ins);

            /// 1.a if the previous instruction is TEST, the current instruction must be an IF
            if(program_line>0){
                auto prev_ins_regtest = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-1));
                if(ins_if == nullptr and prev_ins_regtest) return false;
            }

            if (ins_if) {
                /// 1.b An IF cannot be programmed in the first line
                if(program_line == 0) return false;

                /// 1.c An IF must be programmed after a TEST instruction
                auto prev_ins_regtest = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-1));
                if(prev_ins_regtest == nullptr) return false;

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

                /// 1.h Only ENDs or ENDFORs can be destination lines
                auto dest_ins_end = dynamic_cast<instructions::End*>(p->get_instruction(dest_line));
                auto dest_ins_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(dest_line));
                if(dest_ins_end == nullptr and dest_ins_endfor == nullptr) return false;

            }

            /// 2. RegisterTest syntactic constraints
            auto ins_test = dynamic_cast<instructions::RegisterTest*>(new_ins);
            /// 2.X first line is always a test (at least one precondition per action)
            if(program_line==0){
                if(ins_test) return true;
                else return false;
            }

            if(ins_test and program_line + 2 < p->get_num_instructions()) {
                /// 2.a Issue #10: if the instruction is a TEST but there is an ENDFOR in the next two lines, skip it
                for (auto next_line = program_line+1; next_line<program_line+3; next_line++) {
                    auto next_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(next_line));
                    if (next_endfor) return false;
                }

                /// 2.b If it is a nested IF, check the previous test is lexicographically smaller
                if(program_line > 1u){
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(program_line-2));
                    if(prev_ins_test and prev_ins_test->get_id() >= ins_test->get_id()) { return false; }
                }
                /*/// 2.b (Intermediate alternative) All TEST instructions must be different
                for(size_t line=0u; line<program_line; line++){
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(line));
                    if(prev_ins_test and prev_ins_test->get_id() == ins_test->get_id()) return false;
                }*/
                /*/// 2.b (Stronger alternative) All TEST instructions must in lexicographical order
                for(size_t line=0u; line<program_line; line++){
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest*>(p->get_instruction(line));
                    if(prev_ins_test and prev_ins_test->get_id() >= ins_test->get_id()) return false;
                }*/

                /*/// 2.c (Stronger alternative) TESTs cannot be programmed after SET
                if(program_line>0u){
                    auto prev_ins_regset = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(program_line-1));
                    if(prev_ins_regset) return false;
                }*/
                /// 2.d TESTs can only be programmed after an IF or FOR
                if(program_line > 0){ // Should always be the case
                    auto prev_ins_if = dynamic_cast<instructions::If*>(p->get_instruction(program_line-1));
                    auto prev_ins_for = dynamic_cast<instructions::For*>(p->get_instruction(program_line-1));
                    if(prev_ins_if == nullptr and prev_ins_for == nullptr) return false;
                }
            }
            /// 2.Y A conditional cannot be programmed in the last two lines
            else if(ins_test) return false;

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

                /*/// 4.f A FOR can only be programmed after an IF or another FOR / ENDFOR // ToDo: comment this to get ELEVATOR-STOP
                if(program_line > 0){
                    auto prev_ins_if = dynamic_cast<instructions::If*>(p->get_instruction(program_line-1));
                    auto prev_ins_for = dynamic_cast<instructions::For*>(p->get_instruction(program_line-1));
                    auto prev_ins_endfor = dynamic_cast<instructions::EndFor*>(p->get_instruction(program_line-1));
                    if((prev_ins_if == nullptr) and (prev_ins_for == nullptr) and (prev_ins_endfor == nullptr)) return false;
                    /// If it is nested in a previous FOR, but not in a sequence of FORs, then is wrong
                    for(size_t line=0; line< program_line; line++){
                        auto prev_line_ins_for = dynamic_cast<instructions::For*>(p->get_instruction(line));
                        if(prev_line_ins_for and prev_line_ins_for->get_destination_line() > program_line and prev_ins_for == nullptr) return false;
                    }
                }*/

                /// 4.X This must be the last constraint to check // ToDo: uncomment this to get ELEVATOR-STOP
                std::set<loop_pattern_t> new_loop_pattern;
                for(size_t line=0;line<program_line;line++){
                    auto prev_for = dynamic_cast<instructions::For*>(p->get_instruction(line));
                    if(prev_for){
                        new_loop_pattern.insert(std::make_tuple(
                                prev_for->get_pointer()->get_type()->get_name(),
                                prev_for->get_modifier(),
                                line,
                                prev_for->get_destination_line()
                                ));
                    }
                }
                // Check at this point if the loop pattern is new, getting the current loop pattern variables and
                // adding them to the partial program loop pattern. If new add it, otherwise continue.
                auto last_loop_pattern = std::make_tuple(ins_for->get_pointer()->get_type()->get_name(),
                                                         ins_for->get_modifier(),
                                                         program_line,
                                                         ins_for->get_destination_line());
                new_loop_pattern.insert(last_loop_pattern);
                auto it = _loop_patterns.find(new_loop_pattern);
                if(it == _loop_patterns.end() ) _loop_patterns.insert(new_loop_pattern);
                else return false;
            }

            /// 5. SET syntactic constraints
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

                /*/// 3.c If the previous instruction is a SET, check that the modified fact is different
                if(prev_ins_set and prev_ins_set->get_fact_name(false) == current_fact_name) return false;*/
                /// (Stronger alternative) 3.c Do not repeat SET instructions
                for(size_t line=0; line < program_line; line++){
                    auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(line));
                    if(prev_ins_set and prev_ins_set->get_id() == new_ins->get_id()) return false;
                }

                /// 3.d For each SET(*,0) over a fact, the same fact must appear in a TEST instruction
                if(ins_set_reg->get_value()==0) {
                    bool test_fact_found = false;
                    for (size_t line = 0; line < program_line; line++) {
                        auto prev_ins_test = dynamic_cast<instructions::RegisterTest *>(p->get_instruction(line));
                        if (prev_ins_test and prev_ins_test->get_fact_name(false) == current_fact_name) {
                            test_fact_found = true;
                            break;
                        }
                    }
                    if (not test_fact_found) return false;
                }
                /// 3.d For each SET, the same fact must appear in a previous TEST instruction
                /*bool test_fact_found = false;
                for (size_t line = 0; line < program_line; line++) {
                    auto prev_ins_test = dynamic_cast<instructions::RegisterTest *>(p->get_instruction(line));
                    if (prev_ins_test and prev_ins_test->get_fact_name(false) == current_fact_name) {
                        test_fact_found = true;
                        break;
                    }
                }
                if (not test_fact_found) return false;
                */

                /*/// 3.e Explore SET instructions in lexicographical ascending order
                for(size_t line=0; line < program_line; line++){
                    auto prev_ins_set = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(line));
                    if(prev_ins_set and prev_ins_set->get_id() >= new_ins->get_id()) return false;
                }*/
                /// 3.e (Intermediate) Explore sequence of SET instructions in lexicographical ascending order
                ///     and do not repeat fact names
                if(program_line>0){
                    auto prev_ins_set  = dynamic_cast<instructions::RegisterSet*>(p->get_instruction(program_line-1));
                    if(prev_ins_set and prev_ins_set->get_id() >= new_ins->get_id()) return false;
                    if(prev_ins_set and prev_ins_set->get_fact_name(false) == ins_set_reg->get_fact_name(false)) return false;
                }
            }

            // Any other case is correct
            return true;
        }


        [[nodiscard]] bool check_semantic_constraints(GeneralizedPlanningProblem *gpp, Program *p, size_t program_line,
                                                      instructions::Instruction *new_ins) override{
            /// 1. FOR semantic constraints: do not allow to modify pointers assigned by the action, e.g. ptr_object_0=2 when action_x(object2)
            auto gd = gpp->get_generalized_domain();
            auto gd_ptrs = gd->get_pointers();
            auto ins_for = dynamic_cast<instructions::For*>(new_ins);
            if(ins_for){
                auto ins_for_ptr = ins_for->get_pointer();
                size_t ins_for_ptr_id = 0u;
                for(size_t ptr_idx = 0u; ptr_idx < gd_ptrs.size(); ptr_idx++){
                    if(gd_ptrs[ptr_idx] == ins_for_ptr){
                        ins_for_ptr_id = ptr_idx; break;
                    }
                }
                for(auto instance_id = 0u; instance_id < gpp->get_num_instances(); instance_id++ ){
                    auto instance = gpp->get_instance(instance_id);
                    auto ps = p->make_program_state(gd, instance->get_initial_state());
                    auto v_ptr_assignment = p->reset_program_state(ps.get(), instance, true);
                    assert(ins_for_ptr_id < v_ptr_assignment.size());
                    if(v_ptr_assignment[ins_for_ptr_id]) return false; // Return false if the pointer has been used
                }
            }

            /// 2. TEST semantic constraints:
            /// 2.a Allow TESTs only used pointers so far
            auto ins_test = dynamic_cast<instructions::RegisterTest*>(new_ins);
            if(ins_test) {
                auto instance = gpp->get_instance(0u); // The same pointers should be initially used in every instance
                auto ps = p->make_program_state(gd, instance->get_initial_state());
                auto ptr_used = p->reset_program_state(ps.get(), instance, true);
                /// 3.a Allow SETs only on used pointers so far
                for (size_t line = 0u; line < program_line; line++) {
                    auto prev_ins_for = dynamic_cast<instructions::For *>(p->get_instruction(line));
                    if (prev_ins_for and program_line < prev_ins_for->get_destination_line()) {
                        // Search pointer idx
                        auto for_ptr = prev_ins_for->get_pointer();
                        for (size_t ptr_id = 0u; ptr_id < gd_ptrs.size(); ptr_id++) {
                            if (for_ptr == gd_ptrs[ptr_id]) {
                                ptr_used[ptr_id] = true;
                                break;
                            }
                        }
                    }
                }
                // Check current pointers
                auto ins_test_ptrs = ins_test->get_pointers();
                for (const auto &ins_ptr: ins_test_ptrs) {
                    for (size_t ptr_id = 0u; ptr_id < gd_ptrs.size(); ptr_id++) {
                        if (ins_ptr == gd_ptrs[ptr_id]) {
                            if (not ptr_used[ptr_id]) return false;
                        }
                    }
                }
            }

            /// 3. SET semantic constraints
            auto ins_regset = dynamic_cast<instructions::RegisterSet*>(new_ins);
            if(ins_regset){
                auto instance = gpp->get_instance(0u); // The same pointers should be initially used in every instance
                auto ps = p->make_program_state(gd, instance->get_initial_state());
                auto ptr_used = p->reset_program_state(ps.get(), instance, true);
                /// 3.a Allow SETs only on used pointers so far
                for(size_t line=0u; line < program_line; line++){
                    auto prev_ins_for = dynamic_cast<instructions::For*>(p->get_instruction(line));
                    if(prev_ins_for and program_line < prev_ins_for->get_destination_line()){
                        // Search pointer idx
                        auto for_ptr = prev_ins_for->get_pointer();
                        for (size_t ptr_id=0u; ptr_id<gd_ptrs.size(); ptr_id++) {
                            if(for_ptr == gd_ptrs[ptr_id]){
                                ptr_used[ptr_id] = true; break;
                            }
                        }
                    }
                }
                // Check current pointers
                auto ins_regset_ptrs = ins_regset->get_pointers();
                for(const auto& ins_ptr : ins_regset_ptrs) {
                    for (size_t ptr_id=0u; ptr_id<gd_ptrs.size(); ptr_id++) {
                        if(ins_ptr == gd_ptrs[ptr_id]){
                            if(not ptr_used[ptr_id]) return false;
                        }
                    }
                }
            }

            /// Always true by default
            return true;
        }
    private:
        //std::set<loop_pattern_t> _loop_patterns;
        std::set<std::set<loop_pattern_t>> _loop_patterns;
    };
}

#endif //__THEORY_ACTION_ADL_H__
