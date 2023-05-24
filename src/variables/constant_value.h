//
// Created by js on 24/09/22.
//

#ifndef __CONSTANT_VALUE_H__
#define __CONSTANT_VALUE_H__

#include "variable.h"

namespace variables {
    class ConstantValue : public Variable {
    public:
        explicit ConstantValue(const value_t &value) : Variable(std::to_string(value), value) {}

        explicit ConstantValue(ConstantValue *c) : Variable(c->get_name(), c->get_value()) {}

        ~ConstantValue() override = default;

        // ToDo: test this method
        [[nodiscard]] std::unique_ptr<Variable> copy_var() override{
            return std::make_unique<ConstantValue>(this);
        }

        [[nodiscard]] std::unique_ptr<ConstantValue> copy(){
            return std::make_unique<ConstantValue>(this);
        }

        // constant getter is the same as variable getter

        void set_value(const value_t &value) override {}  // constants cannot be modified

        [[nodiscard]] std::string to_string(bool full_info) const override {
            return (full_info ? "[CONSTANT]: " : "") + std::to_string(_value);
        }
    };
}
#endif //__CONSTANT_VALUE_H__
