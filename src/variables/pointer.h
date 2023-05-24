//
// Created by js on 1/10/22.
//

#ifndef __POINTER_H__
#define __POINTER_H__

#include "../utils/common.h"
#include "../object_types.h"
#include "variable.h"

namespace variables {
    class Pointer : public Variable {
        /// It is a state variable that refers to an indexed typed object of an instance
    public:
        explicit Pointer(const std::string &name, ObjectType *obj_type) : Variable(name, 0), _type(obj_type) {}

        explicit Pointer(variables::Pointer* p) : Variable(p->get_name(),p->get_value()), _type(p->get_type()){}

        ~Pointer() = default;

        [[nodiscard]] std::unique_ptr<Variable> copy_var() override{
            return std::make_unique<Pointer>(this);
        }

        [[nodiscard]] std::unique_ptr<Pointer> copy(){
            return std::make_unique<Pointer>(this);
        }

        void set_object(Object *obj){
            _obj = obj;
        }

        [[nodiscard]] Object *get_object() const {
            return _obj;
        }

        [[nodiscard]] ObjectType *get_type() const {
            return _type;
        }

        [[nodiscard]] std::string to_string(bool full_info) const {
            return (full_info ? "[POINTER]: (" : "(") + _name + "=" + std::to_string(_value) + ")";
        }

    private:
        ObjectType *_type;  // type of objects addressed by the pointer
        Object *_obj; // object addressed by the pointer
        //value_t value; // value corresponds to the indexed element in [0,|Objects:_type|)
    };
}
#endif //__POINTER_H__
