//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_CMP_POINTER_H__
#define __INSTRUCTIONS_RAM_CMP_POINTER_H__

#include "pointer_action.h"

namespace instructions {
    class PointerCmp : public PointerAction {
    public:
        PointerCmp(variables::Pointer* ptr1, variables::Pointer* ptr2) : PointerAction("cmp",{ptr1,ptr2}){}
        ~PointerCmp() = default;

        bool is_applicable(Instance* ins, ProgramState *ps) const override{
            // It is always applicable
            return true;
        }

        [[nodiscard]] bool is_conditional() const override{
            return true;
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            // There must be two pointers in the class, and they are not update but just the difference is returned
            ps->set_line(ps->get_line()+1);
            return _pointers[0]->get_value() - _pointers[1]->get_value();
        }
    };
}

#endif //__INSTRUCTIONS_RAM_CMP_POINTER_H__
