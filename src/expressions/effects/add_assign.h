//
// Created by js on 25/05/22.
//

#ifndef __OPERATIONS_ADD_ASSIGN_H__
#define __OPERATIONS_ADD_ASSIGN_H__

#include "effect.h"

namespace expressions::effects {

    class AddAssign : public Effect {
    public:
        explicit AddAssign(std::unique_ptr<variables::Variable> lhs = nullptr,
                           std::unique_ptr<variables::Variable> rhs = nullptr) :
                Effect("+=", std::move(lhs), std::move(rhs)) {}

        explicit AddAssign(AddAssign* eff):
                Effect(eff->get_operator_name(),
                       std::move(eff->get_lhs()->copy_var()),
                       std::move(eff->get_rhs()->copy_var())){}

        ~AddAssign() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<AddAssign>(this);
        }

        [[nodiscard]] std::unique_ptr<Effect> copy_effect() override{
            return std::make_unique<AddAssign>(this);
        }

        value_t get_effect(State* s) const override {
            /// +=. returns the addition between two state variables
            auto l_value = get_value(_lhs.get(), s);
            auto r_value = get_value(_rhs.get(), s);
            return l_value + r_value;
        }

        /// Uses the default set_effect
        //void set_effect(State *s, const value_t& value) override {}
    };

}

#endif //__OPERATIONS_ADD_ASSIGN_H__
