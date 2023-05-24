//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_POINTER_ACTION_H__
#define __INSTRUCTIONS_RAM_POINTER_ACTION_H__

#include "../../utils/bfgp_utils.h"
#include "../../variables/pointer.h"
#include "../instruction.h"

namespace instructions{
    class PointerAction : public Instruction{
    public:
        explicit PointerAction(
                const std::string &name,
                const std::vector<variables::Pointer*>& pointers  ) :
                Instruction(name), _pointers(pointers) {}

        ~PointerAction() override = default;

        [[nodiscard]] bool is_applicable(Instance* ins, ProgramState *ps ) const override{
            // By default, the instruction is applicable
            return true;
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            // By default, it returns a 0 value
            ps->set_line(ps->get_line()+1);
            return value_t{0};
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            std::string ret = _name + "(";
            std::vector<std::string> ptr_names;
            ptr_names.reserve(_pointers.size());
            for(const auto &ptr : _pointers) {
                if(full_info) ptr_names.emplace_back(ptr->get_name() + ":" + ptr->get_type()->get_name());
                else ptr_names.emplace_back(ptr->get_name());
            }
            return _name + "(" + utils::join(ptr_names, ",") + ")";
        }

        [[nodiscard]] std::vector<variables::Pointer*> get_pointers() const{
            return _pointers;
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            return (full_info?"[INSTRUCTION]: ":"") + get_name(full_info);
        }

    protected:
        std::vector<variables::Pointer*> _pointers;
    };
}

#endif //__INSTRUCTIONS_RAM_POINTER_ACTION_H__
