//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_REGISTER_CMP_H__
#define __INSTRUCTIONS_RAM_REGISTER_CMP_H__
#include "register_action.h"

namespace instructions {
    class RegisterCmp : public RegisterAction {
        /// cmp(func_name(pointers),func_name(pointers2)).
        /// Returns the difference between the first and second fact values after interpreting pointers.
        /// The func_names are the same, but pointers are different.
    public:
        RegisterCmp(Function *f,
                    const std::vector<variables::Pointer*> &pointers1,
                    const std::vector<variables::Pointer*> &pointers2) :
                        RegisterAction("cmp", f, pointers1), _pointers2(pointers2){}

        [[nodiscard]] bool is_applicable(Instance *ins, ProgramState *ps) const override{
            // Always true by default
            return true;
        }

        [[nodiscard]] bool is_conditional() const override{
            return true;
        }

        [[nodiscard]] value_t apply(Instance *ins, ProgramState *ps) override{
            ps->set_line(ps->get_line()+1);
            auto state = ps->get_state();
            std::vector<Object*> objs1, objs2;
            for(const auto& p : _pointers) objs1.emplace_back(p->get_object());
            for(const auto& p : _pointers2) objs2.emplace_back(p->get_object());
            auto fact1 = std::make_unique<variables::StateVariable>(_f, objs1);
            auto fact2 = std::make_unique<variables::StateVariable>(_f, objs2);
            return state->get_value(fact1.get()) - state->get_value(fact2.get());
        }

        [[nodiscard]] std::string get_right_fact_name(bool full_info) const{
            std::vector<std::string> ptr_names2;
            ptr_names2.reserve(_pointers2.size());
            for(const auto &ptr : _pointers2)
                if(full_info) ptr_names2.emplace_back(ptr->get_name()+":"+ptr->get_type()->get_name());
                else ptr_names2.emplace_back(ptr->get_name());
            return _f->get_name() + "(" + utils::join(ptr_names2, ",") + ")";
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            return _name + "(" + get_fact_name(full_info) + "," + get_right_fact_name(full_info) + ")";
        }


    protected:
        std::vector<variables::Pointer*> _pointers2;
    };
}
#endif //__INSTRUCTIONS_RAM_REGISTER_CMP_H__
