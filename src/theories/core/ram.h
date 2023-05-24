//
// Created by js on 31/08/22.
//

#ifndef __THEORY_RAM_H__
#define __THEORY_RAM_H__

#include "../../generalized_domain.h"
#include "../../instructions/ram/pointer_inc.h"
#include "../../instructions/ram/pointer_dec.h"
#include "../../instructions/ram/pointer_clear.h"
#include "../../instructions/ram/pointer_set.h"
#include "../../instructions/ram/pointer_cmp.h"
#include "../../instructions/ram/register_assign.h"
#include "../../instructions/ram/register_cmp.h"
#include "../../instructions/ram/register_set.h"
#include "../../instructions/ram/register_test.h"
#include "../../instructions/ram/goto.h"



namespace theory::core {
    class RAM {
        /// The Random Access Machine (RAM) class, add all allowed theories for pointer modifications,
        /// memory access and manipulation
    public:
        RAM() = default;

        ~RAM() = default;

        static void inc_ptr(GeneralizedDomain *gd) {
            /// inc(pointer). Increase a pointer by 1
            for(const auto& ptr : gd->get_pointers()){
                gd->add_instruction(std::make_unique<instructions::PointerInc>(ptr));
            }
        }

        static void dec_ptr(GeneralizedDomain *gd) {
            /// dec(pointer). Decrease a pointer by 1
            for(const auto& ptr : gd->get_pointers()){
                gd->add_instruction(std::make_unique<instructions::PointerDec>(ptr));
            }
        }

        static void clear_ptr(GeneralizedDomain *gd) {
            /// clear(pointer). Clear a pointer to 0
            for(const auto& ptr : gd->get_pointers()){
                gd->add_instruction(std::make_unique<instructions::PointerClear>(ptr));
            }
        }

        static void set_ptr(GeneralizedDomain *gd) {
            /// set(pointer1,pointer2). Assign pointer2 value to pointer1
            for(const auto& ptr : gd->get_pointers()){
                for(const auto& ptr2 : gd->get_pointers()){
                    if(ptr == ptr2 or ptr->get_type() != ptr2->get_type()) continue;
                    gd->add_instruction(std::make_unique<instructions::PointerSet>(ptr, ptr2));
                }
            }
        }

        static void cmp_ptrs(GeneralizedDomain *gd) {
            /// cmp(pointer1,pointer2). Compare pointer1 to pointer2
            auto all_ptrs = gd->get_pointers();
            // Only needs to compare in one direction, e.g., cmp(b,a) can also be captured by cmp(a,b)
            for(size_t p1 = 0; p1 < all_ptrs.size(); p1++){
                for(size_t p2 = p1+1; p2<all_ptrs.size(); p2++){
                    gd->add_instruction(
                            std::make_unique<instructions::PointerCmp>(all_ptrs[p1], all_ptrs[p2]));
                }
            }
        }

        static void set_reg(Grounder *gr, GeneralizedDomain *gd, const std::vector<std::string>& excluded_prefixes = {}) {
            /// test(func_name(pointer1,...,pointerN).  Returns the fact value after interpreting pointers.
            for(const auto& func : gd->get_domain()->get_functions()){
                auto func_name = func->get_name();
                if(is_excluded(func_name, excluded_prefixes)) continue;
                std::vector<ObjectType*> arg_types;
                for(const auto& obj : func->get_parameters())
                    arg_types.emplace_back(obj->get_type());
                auto all_ptrs = gd->get_pointers();
                std::vector<std::vector<variables::Pointer*>> ptr_groundings;
                std::vector<variables::Pointer*> current_grounding(arg_types.size());
                gr->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);
                for(const auto& grounding : ptr_groundings) {
                    gd->add_instruction(std::make_unique<instructions::RegisterSet>(func, grounding, value_t{0}));
                    gd->add_instruction(std::make_unique<instructions::RegisterSet>(func, grounding, value_t{1}));
                }
            }
        }

        static bool is_excluded(const std::string& name, const std::vector<std::string>& excluded_prefixes){
            if(excluded_prefixes.empty()) return false;
            for(const auto& prefix : excluded_prefixes){
                if(prefix.size() <= name.size() and prefix == name.substr(0,prefix.size())) return true;
            }
            return false;
        }

        static void test_reg(Grounder *gr, GeneralizedDomain *gd, const std::vector<std::string> exclude_prefixes = {}) {
            /// test(func_name(pointer1,...,pointerN).  Returns the fact value after interpreting pointers.
            for(const auto& func : gd->get_domain()->get_functions()){
                auto func_name = func->get_name();
                if(is_excluded(func_name, exclude_prefixes)) continue;
                std::vector<ObjectType*> arg_types;
                for(const auto& obj : func->get_parameters())
                    arg_types.emplace_back(obj->get_type());
                auto all_ptrs = gd->get_pointers();
                std::vector<std::vector<variables::Pointer*>> ptr_groundings;
                std::vector<variables::Pointer*> current_grounding(arg_types.size());
                gr->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);
                for(const auto& grounding : ptr_groundings)
                    gd->add_instruction(std::make_unique<instructions::RegisterTest>(func, grounding));
            }
        }

        static void cmp_regs(Grounder *gr, GeneralizedDomain *gd, const std::vector<std::string> exclude_prefixes = {}) {
            /// cmp(func_name(pointers),func_name(pointers2)). Difference between two fact values
            auto all_ptrs = gd->get_pointers();
            for(const auto& func : gd->get_domain()->get_functions()){
                auto func_name = func->get_name();
                if(is_excluded(func_name, exclude_prefixes)) continue;
                std::vector<ObjectType*> arg_types;
                for(const auto& obj : func->get_parameters())
                    arg_types.emplace_back(obj->get_type());
                std::vector<std::vector<variables::Pointer*>> ptr_groundings;
                std::vector<variables::Pointer*> current_grounding(arg_types.size());
                gr->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);
                // Only needs to compare in one direction, e.g., cmp(b,a) can also be captured by cmp(a,b)
                for(size_t gr1=0; gr1<ptr_groundings.size();gr1++)
                    for(size_t gr2=gr1+1; gr2<ptr_groundings.size(); gr2++)
                        gd->add_instruction(
                                std::make_unique<instructions::RegisterCmp>(
                                        func, ptr_groundings[gr1], ptr_groundings[gr2]));
            }
        }

        static void assign_regs(Grounder *gr, GeneralizedDomain *gd, const std::vector<std::string> exclude_prefixes = {}) {
            /// assign(func_name(pointers),func_name(pointers2)). Assigns right fact value to the left one
            auto all_ptrs = gd->get_pointers();
            for(const auto& func : gd->get_domain()->get_functions()){
                auto func_name = func->get_name();
                if(is_excluded(func_name, exclude_prefixes)) continue;
                std::vector<ObjectType*> arg_types;
                for(const auto& obj : func->get_parameters())
                    arg_types.emplace_back(obj->get_type());
                std::vector<std::vector<variables::Pointer*>> ptr_groundings;
                std::vector<variables::Pointer*> current_grounding(arg_types.size());
                gr->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);
                // Since it can be done from pre- to post-state, any combination is valid
                for(size_t gr1=0; gr1<ptr_groundings.size();gr1++)
                    for(size_t gr2=0; gr2<ptr_groundings.size(); gr2++)
                        gd->add_instruction(
                                std::make_unique<instructions::RegisterAssign>(
                                        func, ptr_groundings[gr1], ptr_groundings[gr2]));
            }
        }

        static void goto_ins(Grounder *gr, GeneralizedDomain *gd){
            /// goto(dest_line,!(cond_flag1 & ... & cond_flagN)).
            /// Jumps to dest_line if some condition evals to false, otherwise moves to the next line.
            auto all_flags = gd->get_flags();
            std::vector<std::vector<value_t>> all_groundings;
            std::vector<value_t> current_grounding(all_flags.size());
            gr->ground_flags(all_flags, all_groundings, current_grounding);  // ground all flags combinations
            // create a goto for each line & grounding
            for(size_t line = 0; line < gd->get_program_lines(); line++){
                for(const auto& grounding : all_groundings) {
                    auto goto_line = std::make_unique<instructions::Goto>(line);
                    for(size_t pos = 0; pos < grounding.size(); pos++)
                        goto_line->add_cond(all_flags[pos], grounding[pos]);
                    gd->add_instruction(std::move(goto_line));
                }
            }
        }
    };
}



#endif //__THEORY_RAM_H__
