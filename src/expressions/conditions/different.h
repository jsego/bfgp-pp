//
// Created by js on 25/05/22.
//

#ifndef __CONDITIONS_DIFFERENT_H__
#define __CONDITIONS_DIFFERENT_H__

#include "condition.h"

namespace expressions::conditions {

    class Different : public Condition {
    public:
        explicit Different(std::unique_ptr<variables::Variable> lhs = nullptr,
                           std::unique_ptr<variables::Variable> rhs = nullptr) :
                Condition("!=", std::move(lhs), std::move(rhs))  {}

        explicit Different(Different *prec) :
                Condition(prec->get_operator_name(),
                          std::move(prec->get_lhs()->copy_var()),
                          std::move(prec->get_rhs()->copy_var())){}

        ~Different() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Different>(this);
        }

        [[nodiscard]] std::unique_ptr<Condition> copy_condition() override{
            return std::make_unique<Different>(this);
        }

        [[nodiscard]] bool eval_condition(State *s) const override {
            auto l_val = get_value(_lhs.get(), s);
            auto r_val = get_value(_rhs.get(), s);
            return l_val != r_val;
        }
    };
}

#endif //__CONDITIONS_DIFFERENT_H__
