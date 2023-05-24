//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_REGISTER_ASSIGN_H__
#define __INSTRUCTIONS_RAM_REGISTER_ASSIGN_H__

#include "register_action.h"

namespace instructions {
    class RegisterAssign : public RegisterAction {
        /// assign(func_name(pointers),func_name(pointers2)).
        /// Returns the assignment from second fact to the first one interpreted over pointers.
        /// The func_names are the same, but pointers are different.
    public:
        RegisterAssign(Function *f,
                       const std::vector<variables::Pointer*> &pointers1,
                       const std::vector<variables::Pointer*> &pointers2) :
                RegisterAction("assign", f, pointers1), _pointers2(pointers2){}

        [[nodiscard]] bool is_applicable(Instance *ins, ProgramState *ps) const override{
            // Always true by default
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
            state->set_value(fact1.get(),state->get_value(fact2.get()));
            return state->get_value(fact2.get());
        }

        [[nodiscard]] value_t apply_from_pre(Instance *ins, ProgramState *post_state, ProgramState *pre_state){
            post_state->set_line(post_state->get_line()+1);
            auto post_s = post_state->get_state();
            auto pre_s = pre_state->get_state();
            std::vector<Object*> objs1, objs2;
            for(const auto& p : _pointers) objs1.emplace_back(p->get_object());
            for(const auto& p : _pointers2) objs2.emplace_back(p->get_object());
            auto fact1 = std::make_unique<variables::StateVariable>(_f, objs1);
            auto fact2 = std::make_unique<variables::StateVariable>(_f, objs2);
            auto val = pre_s->get_value(fact2.get());
            post_s->set_value(fact1.get(), val);
            return val;
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
#endif //__INSTRUCTIONS_RAM_REGISTER_ASSIGN_H__
