#ifndef __CONDITION_H__
#define __CONDITION_H__

#include "../../state.h"
#include "../expression.h"

namespace expressions::conditions  {
    class Condition : public Expression {
    public:
        explicit Condition(const std::string &operator_name = "",
                           std::unique_ptr<variables::Variable> lhs = nullptr,
                           std::unique_ptr<variables::Variable> rhs = nullptr) :
                Expression(operator_name, std::move(lhs), std::move(rhs)) {
        }

        explicit Condition(Condition *prec) :
                Expression(prec->get_operator_name(),
                           std::move(prec->get_lhs()->copy_var()),
                           std::move(prec->get_rhs()->copy_var())){}

        ~Condition() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Condition>(this);
        }

        [[nodiscard]] virtual std::unique_ptr<Condition> copy_condition(){
            return std::make_unique<Condition>(this);
        }

        virtual bool eval_condition(State *s) const {
            return true;
        }

        [[nodiscard]] std::string to_string(bool full_info) const override {
            return (full_info?"[CONDITION]: (": "(") +
                    (_lhs?_lhs->to_string(false):"") +
                    _operator_name +
                    (_rhs?_rhs->to_string(false):"") + ")";
        }
    };
}

#endif
