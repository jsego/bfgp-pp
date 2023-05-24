//
// Created by js on 25/05/22.
//

#ifndef __OPERATIONS_BITVEC_NOT_H__
#define __OPERATIONS_BITVEC_NOT_H__

#include "../effect.h"

namespace expressions::effects::bitvec{
    class Not : public Effect {
    public:
        explicit Not(std::unique_ptr<variables::Variable> lhs = nullptr,
                     std::unique_ptr<variables::Variable> rhs = nullptr) :
                Effect("=~", std::move(lhs), std::move(rhs)) {}

        explicit Not(Not *eff) :
                Effect(eff->get_operator_name(),
                       std::move(eff->get_lhs()->copy_var()),
                       std::move(eff->get_rhs()->copy_var())){}

        ~Not() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Not>(this);
        }

        [[nodiscard]] std::unique_ptr<Effect> copy_effect() override{
            return std::make_unique<Not>(this);
        }

        value_t get_effect(State* s) const override {
            /// =~. returns the logical negation of the _rhs (which requires a state variable of the same size with all bits to 1)
            auto r_value = get_value(_rhs.get(), s);
            // negate an integer = XOR(integer, max integer); since INT_MAX is all 1s.
            return (value_t)(((uvalue_t)r_value) ^ MaxUValue); // ToDo: the standard is (Unsigned Long Long) values
        }

        /// Uses the default set_effect
        //void set_effect(State* s, T value) const override {}
    };
}

#endif //__OPERATIONS_BITVEC_NOT_H__
