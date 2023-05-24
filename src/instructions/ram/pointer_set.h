//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_SET_POINTER_H__
#define __INSTRUCTIONS_RAM_SET_POINTER_H__

#include "pointer_action.h"

namespace instructions {
    class PointerSet : public PointerAction {
    public:
        PointerSet(variables::Pointer* ptr1, variables::Pointer* ptr2) : PointerAction("set",{ptr1,ptr2}){}
        ~PointerSet() = default;

        bool is_applicable(Instance* ins, ProgramState *ps) const override{
            // It is always applicable
            return true;
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            // There must be two pointers in the class, and they are not update but just the difference is returned
            _pointers[0]->set_value(_pointers[1]->get_value());
            _pointers[0]->set_object(_pointers[1]->get_object());
            ps->set_line(ps->get_line()+1);
            return _pointers[0]->get_value();
        }
    };
}

#endif //__INSTRUCTIONS_RAM_SET_POINTER_H__
