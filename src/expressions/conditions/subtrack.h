//
// Created by js on 25/05/22.
//

#ifndef __CONDITIONS_SUBTRACK_H__
#define __CONDITIONS_SUBTRACK_H__

#include "condition.h"

namespace expressions::conditions {

    class Subtract : public Condition {
    public:
        explicit Subtract(std::unique_ptr<variables::Variable> lhs = nullptr,
                          std::unique_ptr<variables::Variable> rhs = nullptr) :
                Condition("-", std::move(lhs), std::move(rhs))  {}

        explicit Subtract(Subtract *prec) :
                Condition(prec->get_operator_name(),
                          std::move(prec->get_lhs()->copy_var()),
                          std::move(prec->get_rhs()->copy_var())){}

        ~Subtract() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Subtract>(this);
        }

        [[nodiscard]] std::unique_ptr<Condition> copy_condition() override{
            return std::make_unique<Subtract>(this);
        }

        [[nodiscard]] bool eval_condition(State *s) const override {
            auto l_val = get_value(_lhs.get(), s);
            auto r_val = get_value(_rhs.get(), s);
            return l_val >= r_val;
        }
    };
}
#endif //__CONDITIONS_SUBTRACK_H__
