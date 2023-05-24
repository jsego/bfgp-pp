//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_REGISTER_ACTION_H__
#define __INSTRUCTIONS_RAM_REGISTER_ACTION_H__

#include "../instruction.h"

namespace instructions {
    // ToDo: finish checking this class and finish implementation of derived ones
    class RegisterAction : public Instruction {
    public:
        RegisterAction(const std::string &name, Function *f, const std::vector<variables::Pointer*> &pointers) :
            Instruction(name), _f(f), _pointers(pointers){}

        [[nodiscard]] bool is_applicable(Instance *ins, ProgramState *ps) const override{
            // Always true by default
            return true;
        }

        [[nodiscard]] value_t apply(Instance *ins, ProgramState *ps) override{
            ps->set_line(ps->get_line()+1);
            return value_t{0};
        }

        [[nodiscard]] virtual std::string get_fact_name(bool full_info) const{
            std::vector<std::string> ptr_names;
            ptr_names.reserve(_pointers.size());
            for(const auto &ptr : _pointers)
                if(full_info) ptr_names.emplace_back(ptr->get_name()+":"+ptr->get_type()->get_name());
                else ptr_names.emplace_back(ptr->get_name());
            return _f->get_name()  + "(" + utils::join(ptr_names, ",") +")";
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            return _name + "(" + get_fact_name(full_info) + ")";
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            return (full_info?"[INSTRUCTION]: ":"") + get_name(full_info);
        }

        [[nodiscard]] std::vector<variables::Pointer*> get_pointers() const{
            return _pointers;
        }

    protected:
        Function *_f;
        std::vector<variables::Pointer*> _pointers;
    };
}

#endif //__INSTRUCTIONS_RAM_REGISTER_ACTION_H__
