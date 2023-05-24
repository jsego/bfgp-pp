//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_CLEAR_POINTER_H__
#define __INSTRUCTIONS_RAM_CLEAR_POINTER_H__

#include "pointer_action.h"

namespace instructions {
    class PointerClear : public PointerAction {
    public:
        PointerClear(variables::Pointer* ptr) : PointerAction("clear",{ptr}){}
        ~PointerClear() = default;

        bool is_applicable(Instance* ins, ProgramState *ps) const override{
            // It is always applicable
            return true;
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            // There must be just one pointer in the class
            auto new_value = value_t{0};
            _pointers[0]->set_value(new_value);
            auto typed_objs = ins->get_typed_objects(_pointers[0]->get_type()->get_name());
            _pointers[0]->set_object(typed_objs[new_value]);
            ps->set_line(ps->get_line()+1);
            return new_value;
        }
    };
}

#endif //__INSTRUCTIONS_RAM_CLEAR_POINTER_H__
