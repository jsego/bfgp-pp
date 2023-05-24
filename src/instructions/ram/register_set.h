//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_REGISTER_SET_H__
#define __INSTRUCTIONS_RAM_REGISTER_SET_H__

#include "register_action.h"

namespace instructions {
    class RegisterSet : public RegisterAction {
        /// set(func_name(pointer1,...,pointerN),value_t). Assign value_t to the fact over pointers and returns it.
    public:
        RegisterSet(Function *f, const std::vector<variables::Pointer*> &pointers, value_t value) :
            RegisterAction("set", f, pointers), _val(value){}

        [[nodiscard]] bool is_applicable(Instance *ins, ProgramState *ps) const override{
            // Always true by default
            return true;
        }

        [[nodiscard]] value_t apply(Instance *ins, ProgramState *ps) override{
            ps->set_line(ps->get_line()+1);
            auto state = ps->get_state();
            std::vector<Object*> objs;
            for(const auto& p : _pointers){
                objs.emplace_back(p->get_object());
            }
            auto fact = std::make_unique<variables::StateVariable>(_f, objs, _val);
            state->set_value(fact.get(), _val);
            return _val;
        }

        [[nodiscard]] value_t get_value() const{
            return _val;
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            return _name + "(" + get_fact_name(full_info) + ","+std::to_string(_val)+")";
        }

    private:
        value_t _val;
    };
}
#endif // __INSTRUCTIONS_RAM_REGISTER_SET_H__
