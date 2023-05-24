//
// Created by js on 25/05/22.
//

#ifndef __INSTRUCTIONS_FOR_H__
#define __INSTRUCTIONS_FOR_H__

#include "instruction.h"
#include "../variables/pointer.h"

namespace instructions{
    class For : public Instruction{
    public:
        explicit For(variables::Pointer* ptr, size_t dest, int modifier = 1 ):
                _ptr(ptr), _dest_line(dest), _mod(modifier){}

        ~For() override = default;

        [[nodiscard]] size_t get_destination_line() const{
            return _dest_line;
        }

        [[nodiscard]] variables::Pointer* get_pointer() const{
            return _ptr;
        }

        [[nodiscard]] int get_modifier() const{
            return _mod;
        }

        [[nodiscard]] bool is_applicable(Instance *ins, ProgramState *ps) const override{
            /// A FOR instruction is always applicable
            return true;
        }

        value_t apply(Instance *ins, ProgramState* ps ) override{
            /// Used only to initialize the pointer variable either to 0 or max index
            auto line = ps->get_line();
            auto var_domain = ins->get_typed_variable_domain(_ptr->get_type()->get_name());
            assert(var_domain > 0);
            _ptr->set_value((_mod>0?0:var_domain-1));
            _ptr->set_object(ins->get_typed_objects(_ptr->get_type()->get_name())[_ptr->get_value()]);
            ps->set_line(line + 1);
            return 0;
        }


        [[nodiscard]] std::string get_name(bool full_info) const override{
            return "for(" + _ptr->get_name() + (_mod>0?"++":"--") + "," + std::to_string( _dest_line ) + ")";
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override{
            return (full_info?"[INSTRUCTION]: ":"") + get_name(full_info);
        }

    private:
        variables::Pointer *_ptr;
        size_t _dest_line;
        value_t _mod;
    };
}

#endif //__INSTRUCTIONS_FOR_H__
