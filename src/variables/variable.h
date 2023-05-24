//
// Created by js on 25/09/22.
//

#ifndef __VARIABLE_H__
#define __VARIABLE_H__

#include "../utils/common.h"
#include "../object.h"

namespace variables {
    class Variable {
    public:
        explicit Variable(const std::string &name, const value_t &value) : _name(name), _value(value) {}
        explicit Variable(Variable *var): _name(var->get_name()), _value(var->get_value()){}

        virtual ~Variable() = default;

        [[nodiscard]] virtual std::unique_ptr<Variable> copy_var(){
            return std::make_unique<Variable>(this);
        }

        virtual void set_pointer_references(const std::vector<Variable*> &pointers){
            /// Do nothing by default - generally accessible but only useful for state variables
        }

        virtual void update_object_references(const std::vector<Object*> &new_obj_refs ){
            /// Do nothing by default - generally accessible but only useful for state variables
        }

        virtual void set_name(const std::string &name){
            _name = name;
        }

        virtual void set_value(const value_t &value) {
            _value = value;
        }

        [[nodiscard]] virtual value_t get_value() const {
            return _value;
        }

        [[nodiscard]] virtual std::string get_name() const {
            return _name;
        }

        [[nodiscard]] virtual std::string to_string(bool full_info) const {
            return (full_info ? "[VARIABLE]: " : "") + _name + (full_info?"="+std::to_string(_value):"");
        }

    protected:
        std::string _name;
        value_t _value;
    };
}
#endif //__VARIABLE_H__
