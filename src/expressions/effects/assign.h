//
// Created by js on 25/05/22.
//

#ifndef __OPERATIONS_ASSIGN_H__
#define __OPERATIONS_ASSIGN_H__

#include "effect.h"

namespace expressions::effects{

    class Assign : public Effect {
    public:
        explicit Assign(std::unique_ptr<variables::Variable> lhs = nullptr,
                        std::unique_ptr<variables::Variable> rhs = nullptr) :
                Effect("=", std::move(lhs), std::move(rhs)) {}

        explicit Assign(Assign *eff) :
                Effect(eff->get_operator_name(),
                       std::move(eff->get_lhs()->copy_var()),
                       std::move(eff->get_rhs()->copy_var())){}

        ~Assign() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Assign>(this);
        }

        [[nodiscard]] std::unique_ptr<Effect> copy_effect() override{
            return std::make_unique<Assign>(this);
        }

        value_t get_effect(State* s) const override {
            /// =. returns the _rhs value
            return get_value(_rhs.get(), s);
        }

        /// Uses the default set_effect
        //void set_effect(State *s, const value_t& value) override {}
    };
}

#endif //__OPERATIONS_ASSIGN_H__
