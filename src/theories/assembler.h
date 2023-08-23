//
// Created by js on 31/08/22.
//

#ifndef __THEORY_ASSEMBLER_H__
#define __THEORY_ASSEMBLER_H__

#include "theory.h"
#include "../generalized_domain.h"
#include "../grounder.h"
#include "./core/ram.h"
#include "./core/strips.h"
#include "./core/terminal.h"
#include "../variables/zero_flag.h"
#include "../variables/carry_flag.h"

namespace theory {
    class Assembler : public Theory{
    public:
        Assembler() : Theory( "Assembler"){}

        static void build_theory(GeneralizedDomain *gd){
            auto grounder = std::make_unique<Grounder>();

            /// 1. Call STRIPS constructor
            auto strips = std::make_unique<core::STRIPS>(grounder.get(), gd);

            /// 2. Call RAM constructor
            auto ram = std::make_unique<core::RAM>();
            /// 2.a Pointer modifiers
            ram->inc_ptr(gd);
            ram->dec_ptr(gd);
            //ram->clear_ptr(gd); // ToDo: test whether clear should be included or not
            ram->set_ptr(gd);
            /// 2.b Pointer and Register comparison
            ram->cmp_ptrs(gd);
            ram->test_reg(grounder.get(), gd);
            ram->cmp_regs(grounder.get(), gd);
            /// 2.c Generate features
            gd->add_flag(std::make_unique<variables::ZeroFlag>());
            gd->add_flag(std::make_unique<variables::CarryFlag>());
            /// 2.d Goto instructions: forward (if or conditional), backward (loops)
            ram->goto_ins(grounder.get(), gd);

            /// 3. Call END constructor
            auto terminal = std::make_unique<core::Terminal>(gd);
        }

        // ToDo: would it be better to add a is_conditional flag in instruction.h and derived classes?
        static bool is_conditional_name(const std::string &ins_name) {
            return ((ins_name.substr(0, 4) == "test") or
                    (ins_name.substr(0, 3) == "cmp"));
        }

        [[nodiscard]] bool check_syntax_constraints(Program *p, size_t program_line, instructions::Instruction *new_ins) override{
            // 1. Check that in last line, only END can be programmed
            auto ins_end = dynamic_cast<instructions::End*>(new_ins);
            if(ins_end == nullptr and program_line+1 == p->get_num_instructions()) return false;

            // 2. Check that GOTO instructions can only be programmed after math instruction, and they
            // cannot jump to the same line or the next one, and no previous GOTO can directly jump to it
            auto ins_goto = dynamic_cast<instructions::Goto*>(new_ins);
            auto prev_ins = (program_line>0?p->get_instruction(program_line-1): nullptr);
            if(ins_goto){
                if(program_line == 0) return false;
                if(prev_ins and prev_ins->get_type() != ActionType::Math) return false;
                auto dest_line = ins_goto->get_destination_line();
                if(dest_line == program_line or dest_line == program_line+1) return false;
                for(size_t line=0; line < p->get_num_instructions(); ++line ){
                    if(line == program_line ) continue;
                    auto prev_goto = dynamic_cast<instructions::Goto*>(p->get_instruction(line));
                    if(not prev_goto) continue;
                    auto prev_dest_line = prev_goto->get_destination_line();
                    // don't let goto instructions jump to new one
                    if(prev_dest_line == program_line) return false;
                    // don't jump to a goto instruction
                    if(line == dest_line) return false;
                    // [EXTRA] syntactic constraints for well-structured planning programs
                    // if the new goto is inside a goto loop, new dest. line in the loop or right after
                    if( prev_dest_line < program_line and program_line < line and
                       (dest_line < prev_dest_line or line+1 < dest_line )) return false;
                    // the same must hold the other way around
                    if( dest_line < line and line < program_line and
                       (prev_dest_line < dest_line or program_line+1 < prev_dest_line)) return false;
                    // if the new goto is inside a conditional goto, new dest. line exactly into the conditional
                    if( line < program_line and program_line < prev_dest_line and
                        (dest_line <= line or prev_dest_line < dest_line)) return false;
                    // the same must hold the other way around
                    if( program_line < line and line < dest_line and
                        (prev_dest_line <= program_line or dest_line < prev_dest_line)) return false;


                }
            }
            // 3. Check if the instruction is not a GOTO, but the previous one is TEST or CMP (which forces the next one
            // to be a GOTO instruction)
            else if(prev_ins and is_conditional_name(prev_ins->get_name(false))){
                return false;
            }

            // 4. Check that only PlanningActions, GOTOs or ENDs can be programmed in line [n-2]
            auto ins_pa = dynamic_cast<instructions::PlanningAction*>(new_ins);
            if(program_line+2 == p->get_num_instructions() and (not (ins_pa or ins_goto or ins_end))) return false;

            // 5. Issue #57, trivial syntactic constraints among consecutive RAM instructions
            //if(false && program_line > 0) {
            if(program_line > 0) {
                // Get all relevant previous interpretations
                auto prev_ins_clear = dynamic_cast<instructions::PointerClear*>(p->get_instruction(program_line-1));
                auto prev_ins_set = dynamic_cast<instructions::PointerSet*>(p->get_instruction(program_line-1));
                auto prev_ins_inc = dynamic_cast<instructions::PointerInc*>(p->get_instruction(program_line-1));
                auto prev_ins_dec = dynamic_cast<instructions::PointerDec*>(p->get_instruction(program_line-1));

                // Get all relevant current interpretations
                auto ins_clear = dynamic_cast<instructions::PointerClear*>(new_ins);
                auto ins_set = dynamic_cast<instructions::PointerSet*>(new_ins);
                auto ins_inc = dynamic_cast<instructions::PointerInc*>(new_ins);
                auto ins_dec = dynamic_cast<instructions::PointerDec*>(new_ins);

                // 5.a & 5.b: [program_line-1]. clear(x) | inc(x) | dec(x) | set(x,*); [program_line]. clear(x) | set(x,*);
                if(prev_ins_clear or prev_ins_inc or prev_ins_dec or prev_ins_set){
                    auto prev_ins_pointer_act = dynamic_cast<instructions::PointerAction*>(p->get_instruction(program_line-1));
                    auto prev_pointers = prev_ins_pointer_act->get_pointers();
                    if(ins_clear and ins_clear->get_pointers()[0] == prev_pointers[0]) return false;
                    if(ins_set and ins_set->get_pointers()[0] == prev_pointers[0]) return false;
                }
                // 5.c: [program_line-1]. inc(x); [program_line]. dec(x);
                if(prev_ins_inc and ins_dec and prev_ins_inc->get_pointers()[0] == ins_dec->get_pointers()[0]) return false;
                // 5.d: [program_line-1]. dec(x); [program_line]. inc(x);
                if(prev_ins_dec and ins_inc and prev_ins_dec->get_pointers()[0] == ins_inc->get_pointers()[0]) return false;

            }

            // Any other case is correct
            return true;
        }
    };
}

#endif //__THEORY_ASSEMBLER_H__
