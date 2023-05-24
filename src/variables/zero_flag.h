//
// Created by js on 1/10/22.
//

#ifndef __ZERO_FLAG_H__
#define __ZERO_FLAG_H__

#include "flag.h"

namespace variables {
    class ZeroFlag : public Flag {
    public:
        ZeroFlag() : Flag("zf") {}
        ZeroFlag(ZeroFlag *zf) : Flag(zf->get_name()) {}

        ~ZeroFlag() override = default;

        // ToDo: test this method
        [[nodiscard]] std::unique_ptr<Variable> copy_var() override{
            return std::make_unique<ZeroFlag>(this);
        }

        [[nodiscard]] std::unique_ptr<ZeroFlag> copy(){
            return std::make_unique<ZeroFlag>(this);
        }

        void set_value(const value_t &res) override {
            _value = (res == 0);
        }
    };
}

#endif //__ZERO_FLAG_H__
