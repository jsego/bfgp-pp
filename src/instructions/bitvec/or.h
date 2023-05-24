//
// Created by js on 2/06/22.
//

#ifndef __INSTRUCTIONS_OR_H__
#define __INSTRUCTIONS_OR_H__


#include "../instruction.h"
#include "variables/variable.h"
#include "../../expressions/operations/bitvec/or.h"
#include "../../expressions/operations/assign.h"

namespace instructions::bitvec {
    class Or : public Instruction {
    public:
        Or(id_type lhs_ptr_id, id_type rhs_ptr_id1, id_type rhs_ptr_id2, std::shared_ptr<StateDescriptor> sd) {
            /// Or instruction: it assumes there is a unique predicate type named "vector"
            auto pred_id = sd->get_type_id("vector");
            auto lhs_ptr_name = sd->get_pointer_name(lhs_ptr_id);
            auto rhs_ptr_name1 = sd->get_pointer_name(rhs_ptr_id1);
            auto rhs_ptr_name2 = sd->get_pointer_name(rhs_ptr_id2);
            vec_id_t lhs_id = {lhs_ptr_id};
            vec_id_t rhs_id1 = {rhs_ptr_id1};
            vec_id_t rhs_id2 = {rhs_ptr_id2};

            /// Building the Assign operation
            auto lhs1 =
                    std::make_unique<variables::Variable>(
                            "vector(" + lhs_ptr_name + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            lhs_id);
            auto rhs1 =
                    std::make_unique<variables::Variable>(
                            "vector(" + rhs_ptr_name1 + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            rhs_id1);
            _op_assign = std::make_unique<expressions::effects::Assign>(sd, std::move(lhs1), std::move(rhs1));

            /// Building the Or operation
            auto lhs2 =
                    std::make_unique<variables::Variable>(
                            "vector(" + lhs_ptr_name + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            lhs_id);

            auto rhs2 =
                    std::make_unique<variables::Variable>(
                            "vector("+rhs_ptr_name2+")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            rhs_id2);
            _op_or = std::make_unique<expressions::effects::bitvec::Or>(sd, std::move(lhs2), std::move(rhs2));
        };

        ~Or() override = default;

        value_t apply(ProgramState* ps) override {
            auto s = ps->get_state();
            auto line = ps->get_line();
            _op_assign->set_effect(s, _op_assign->get_effect(s));
            auto ret  =_op_or->get_effect(s);
            _op_or->set_effect(s, ret);
            ps->set_line(line+1);
            return ret;
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            std::string ret;
            if( full_info ) ret = "[INSTRUCTION][OR]:\n";
            return ret + _op_or->get_lhs()->to_string(false) + " = or(" +
                   _op_assign->get_rhs()->to_string(false) + "," + _op_or->get_rhs()->to_string(false) + ")\n";
        }

    private:
        std::unique_ptr<expressions::effects::Assign> _op_assign;
        std::unique_ptr<expressions::effects::bitvec::Or> _op_or;
    };
}

#endif //__INSTRUCTIONS_OR_H__
