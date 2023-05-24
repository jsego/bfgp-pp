//
// Created by js on 1/10/22.
//

#ifndef __CARRY_FLAG_H__
#define __CARRY_FLAG_H__

#include "flag.h"

namespace variables {
    class CarryFlag : public Flag {
    public:
        CarryFlag() : Flag("cf") {}
        CarryFlag(CarryFlag *cf) : Flag(cf->get_name()) {}

        ~CarryFlag() override = default;

        // ToDo: test this method
        [[nodiscard]] std::unique_ptr<Variable> copy_var() override{
            return std::make_unique<CarryFlag>(this);
        }

        [[nodiscard]] std::unique_ptr<CarryFlag> copy(){
            return std::make_unique<CarryFlag>(this);
        }

        void set_value(const value_t &res) override {
            _value = (res > 0);
        }
    };
}

#endif //__CARRY_FLAG_H__
