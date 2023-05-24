//
// Created by js on 25/05/22.
//

#ifndef __OPERATIONS_BITVEC_SHIFT_LEFT_H__
#define __OPERATIONS_BITVEC_SHIFT_LEFT_H__

#include "../effect.h"

namespace expressions::effects::bitvec{

    class ShiftLeft : public Effect {
    public:
        explicit ShiftLeft(std::unique_ptr<variables::Variable> lhs = nullptr,
                           std::unique_ptr<variables::Variable> rhs = nullptr) :
                Effect("<<=", std::move(lhs), std::move(rhs)) {}

        explicit ShiftLeft(ShiftLeft *eff) :
                Effect(eff->get_operator_name(),
                       std::move(eff->get_lhs()->copy_var()),
                       std::move(eff->get_rhs()->copy_var())){}

        ~ShiftLeft() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<ShiftLeft>(this);
        }

        [[nodiscard]] std::unique_ptr<Effect> copy_effect() override{
            return std::make_unique<ShiftLeft>(this);
        }

        value_t get_effect(State* s) const override {
            /// <<=. returns the _lhs bits shifted to the left _rhs times
            auto l_value = get_value(_lhs.get(), s);
            auto r_value = get_value(_rhs.get(), s);
            return (value_t)(((uvalue_t)l_value) << ((uvalue_t)r_value)); // assume the type is Unsigned Long Long
        }

        /// Uses the default set_effect
        //void set_effect(State* s, T value) const override {}
    };

}
#endif //__OPERATIONS_BITVEC_SHIFT_LEFT_H__
