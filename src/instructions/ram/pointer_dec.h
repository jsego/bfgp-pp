//
// Created by js on 6/10/22.
//

#ifndef __INSTRUCTIONS_RAM_DEC_POINTER_H__
#define __INSTRUCTIONS_RAM_DEC_POINTER_H__

#include "pointer_action.h"

namespace instructions {
    class PointerDec : public PointerAction {
    public:
        PointerDec(variables::Pointer* ptr) : PointerAction("dec",{ptr}){}
        ~PointerDec() = default;

        bool is_applicable(Instance* ins, ProgramState *ps) const override{
            // There must be just one pointer in the class
            return _pointers[0]->get_value() > 0;
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            // There must be just one pointer in the class
            value_t new_value = is_applicable(ins, ps) ? _pointers[0]->get_value() - 1 : value_t{0};
            _pointers[0]->set_value(new_value);
            auto typed_objs =
                    ins->get_typed_objects(_pointers[0]->get_type()->get_name());
            _pointers[0]->set_object(typed_objs[new_value]);
            ps->set_line(ps->get_line() + 1); // always progress one line
            return new_value;
        }
    };
}

#endif //__INSTRUCTIONS_RAM_DEC_POINTER_H__
