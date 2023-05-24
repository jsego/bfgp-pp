//
// Created by js on 30/05/22.
//

#ifndef __INSTRUCTIONS_NOT_H__
#define __INSTRUCTIONS_NOT_H__

#include "../instruction.h"
#include "variables/variable.h"
#include "../../expressions/operations/bitvec/not.h"

namespace instructions::bitvec {
    class Not : public Instruction {
    public:
        Not(id_type lhs_ptr_id, id_type rhs_ptr_id, std::shared_ptr<StateDescriptor> sd) {
            // assume there is a unique predicate type named "vector"
            auto lhs_ptr_name = sd->get_pointer_name(lhs_ptr_id);
            auto rhs_ptr_name = sd->get_pointer_name(rhs_ptr_id);
            auto pred_id = sd->get_type_id("vector");
            vec_id_t lhs_id = {lhs_ptr_id};
            vec_id_t rhs_id = {rhs_ptr_id};
            auto lhs = std::make_unique<variables::Variable>("vector("+lhs_ptr_name+")", NAME_VAR_TYPE_PREDICATE, pred_id, lhs_id);
            auto rhs = std::make_unique<variables::Variable>("vector("+rhs_ptr_name+")", NAME_VAR_TYPE_PREDICATE, pred_id, rhs_id);
            _op = std::make_unique<expressions::effects::bitvec::Not>(sd, std::move(lhs), std::move(rhs));
        };

        ~Not() override = default;

        value_t apply(ProgramState* ps) override {
            auto s = ps->get_state();
            auto line = ps->get_line();
            auto ret = _op->get_effect(s);
            _op->set_effect(s, ret);
            ps->set_line(line+1);
            return ret;
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            std::string ret;
            if( full_info ) ret = "[INSTRUCTION][NOT]:\n";
            return ret+_op->get_lhs()->to_string(false)+" = not(" + _op->get_rhs()->to_string(false) +")\n";
        }

    private:
        std::unique_ptr<expressions::effects::bitvec::Not> _op;
    };
}

#endif //__INSTRUCTIONS_NOT_H__
