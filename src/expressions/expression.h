#ifndef __EXPRESSION_H__
#define __EXPRESSION_H__

#include "../variables/variable.h"
#include "../variables/state_variable.h"
#include "../variables/constant_value.h"

namespace expressions {
    class Expression {
    public:
        //FIXME: change var "name" to "operator", and "effects" (and its namespace) to "effects"
        explicit Expression(const std::string &op = "",
                            std::unique_ptr<variables::Variable> lhs = nullptr,
                            std::unique_ptr<variables::Variable> rhs = nullptr) :  // FIXME: rhs could be an Expression
                _operator_name(op), _lhs(std::move(lhs)), _rhs(std::move(rhs)) {}

        explicit Expression(Expression *expression):
            _operator_name(expression->get_operator_name()),
            _lhs(expression->get_lhs()->copy_var()),
            _rhs(expression->get_rhs()->copy_var()){}

        /// Owns _lhs and _rhs
        virtual ~Expression() = default;

        [[nodiscard]] virtual std::unique_ptr<Expression> copy_expression(){
            return std::make_unique<Expression>(this);
        }

        [[nodiscard]] virtual std::string get_operator_name() const {
            return _operator_name;
        }

        // FIXME: it is not the most efficient to check for the kind of variable to retrieve a value
        [[nodiscard]] value_t get_value(variables::Variable* v, State *s) const{
            auto state_variable = dynamic_cast<variables::StateVariable*>(v);
            if(state_variable) return s->get_value(state_variable);
            auto constant_value = dynamic_cast<variables::ConstantValue*>(v);
            if(constant_value) return constant_value->get_value();
            // add new variable types here
            return value_t{0}; // default value
        }

        void update_object_references(const std::vector<Object*> &new_obj_refs){
            if(_lhs) _lhs->update_object_references(new_obj_refs);
            if(_rhs) _rhs->update_object_references(new_obj_refs);
        }

        void set_pointer_references(const std::vector<variables::Variable*> &new_ptr_refs){
            if(_lhs) _lhs->set_pointer_references(new_ptr_refs);
            if(_rhs) _rhs->set_pointer_references(new_ptr_refs);
        }

        [[nodiscard]] variables::Variable* get_lhs() const{
            return _lhs.get();
        }

        [[nodiscard]] variables::Variable* get_rhs() const{
            return _rhs.get();
        }

        [[nodiscard]] virtual std::string to_string(bool full_info) const {
            return (full_info?"[EXPRESSION]: (":"(") +
                    (_lhs?_lhs->to_string(false):"") +
                    _operator_name +
                    (_rhs?_rhs->to_string(false):"") + ")\n";
        }

    protected:
        std::string _operator_name;
        std::unique_ptr<variables::Variable> _lhs;
        std::unique_ptr<variables::Variable> _rhs; // FIXME (Issue #48): rhs could be an Expression
    };
}
#endif
