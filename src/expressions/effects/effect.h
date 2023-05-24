#ifndef __OPERATION_H__
#define __OPERATION_H__

#include "../../utils/common.h"
#include "../../state.h"
#include "../expression.h"

namespace expressions::effects {
    class Effect : public Expression {
    public:
        explicit Effect(const std::string &operator_name = "",
                        std::unique_ptr<variables::Variable> lhs = nullptr,
                        std::unique_ptr<variables::Variable> rhs = nullptr) :
                Expression(operator_name, std::move(lhs), std::move(rhs)) {}

        explicit Effect(Effect *eff) :
                Expression(eff->get_operator_name(),
                           std::move(eff->get_lhs()->copy_var()),
                           std::move(eff->get_rhs()->copy_var())){}

        ~Effect() override = default;

        [[nodiscard]] std::unique_ptr<Expression> copy_expression() override{
            return std::make_unique<Effect>(this);
        }

        [[nodiscard]] virtual std::unique_ptr<Effect> copy_effect(){
            return std::make_unique<Effect>(this);
        }

        [[nodiscard]] virtual value_t get_effect(State *s) const{
            /// Return the _rhs state variable value by default
            return get_value(_rhs.get(), s);
        }

        virtual void set_effect(State *s, const value_t& value){
            /// If _lhs is a state var, update it in s with value, otherwise do nothing
            auto state_var = dynamic_cast<variables::StateVariable*>(_lhs.get());
            if(state_var) s->set_value(state_var, value);
        }

        [[nodiscard]] virtual std::string to_string(bool full_info) const {
            return (full_info?"[EFFECT]: (":"(") +
                    (_lhs?_lhs->to_string(false):"") +
                    _operator_name +
                    (_rhs?_rhs->to_string(false):"") + ")";
        }
    };
}

#endif
