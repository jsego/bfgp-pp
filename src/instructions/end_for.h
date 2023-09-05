//
// Created by js on 25/05/22.
//

#ifndef __INSTRUCTIONS_END_FOR_H__
#define __INSTRUCTIONS_END_FOR_H__

#include "instruction.h"
#include "../variables/pointer.h"

namespace instructions{
    class EndFor : public Instruction{
    public:
        explicit EndFor(variables::Pointer* ptr, size_t orig_line, int modifier = 1 ):
                _ptr(ptr), _orig_line(orig_line), _mod(modifier){}

        ~EndFor() override = default;

        [[nodiscard]] variables::Pointer* get_pointer() const{
            return _ptr;
        }

        [[nodiscard]] size_t get_original_line() const{
            return _orig_line;
        }

        [[nodiscard]] int get_modifier() const{
            return _mod;
        }

        bool is_applicable(Instance *ins, ProgramState* ps ) const override{
            /// An ENDFOR instruction is always applicable
            return true;
        }

        value_t apply(Instance *ins, ProgramState* ps ) override{
            /// Update pointer values that are indexing objects
            auto line = ps->get_line();
            auto ptr_val = _ptr->get_value();
            auto var_domain = ins->get_typed_variable_domain(_ptr->get_type()->get_name());

            if( ptr_val+_mod >= 0 and ptr_val+_mod < var_domain ){
                ps->set_line(_orig_line + 1); // jump to FOR line + 1
                _ptr->set_value(ptr_val + _mod); // update pointer value
                _ptr->set_object(ins->get_typed_objects(_ptr->get_type()->get_name())[ptr_val+_mod]);
            }
            else{ // the pointer modification is invalid, hence move to the next line
                ps->set_line(line + 1);
            }

            return 0;
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            return "endfor(" + _ptr->get_name() + (_mod>0?"++":"--") + "," + std::to_string( _orig_line ) + ")";
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override{
            return (full_info?"[INSTRUCTION]: ":"") + get_name(full_info);
        }

    private:
        variables::Pointer *_ptr;
        size_t _orig_line;
        int _mod;
    };
}
#endif //__INSTRUCTIONS_END_FOR_H__
