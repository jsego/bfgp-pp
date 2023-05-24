//
// Created by js on 31/05/22.
//

#ifndef __INSTRUCTIONS_SMOL_H__
#define __INSTRUCTIONS_SMOL_H__

#include "../instruction.h"
#include "variables/variable.h"
#include "../../expressions/operations/bitvec/shift_left.h"
#include "../../expressions/operations/assign.h"

namespace instructions::bitvec {
    class Smol : public Instruction {
    public:
        Smol(id_type lhs_ptr_id, id_type rhs_ptr_id, std::shared_ptr<StateDescriptor> sd) {
            /// Smol instruction: it assumes there is a unique predicate type named "vector"
            auto lhs_ptr_name = sd->get_pointer_name(lhs_ptr_id);
            auto rhs_ptr_name = sd->get_pointer_name(rhs_ptr_id);
            auto pred_id = sd->get_type_id("vector");
            vec_id_t lhs_id = {lhs_ptr_id};
            vec_id_t rhs_id = {rhs_ptr_id};

            /// Building the Assign operation
            auto lhs1 =
                    std::make_unique<variables::Variable>(
                            "vector(" + lhs_ptr_name + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            lhs_id);
            auto rhs1 =
                    std::make_unique<variables::Variable>(
                            "vector(" + rhs_ptr_name + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            rhs_id);
            _op_assign = std::make_unique<expressions::effects::Assign>(sd, std::move(lhs1), std::move(rhs1));

            /// Building the ShiftLeft operation
            auto lhs2 =
                    std::make_unique<variables::Variable>(
                            "vector(" + lhs_ptr_name + ")",
                            NAME_VAR_TYPE_PREDICATE,
                            pred_id,
                            lhs_id);
            auto rhs2 = std::make_unique<variables::Variable>("1", NAME_VAR_TYPE_CONSTANT, 1);
            _op_shift_left = std::make_unique<expressions::effects::bitvec::ShiftLeft>(sd, std::move(lhs2), std::move(rhs2));
        };

        ~Smol() override = default;

        value_t apply(ProgramState* ps) override {
            auto s = ps->get_state();
            auto line = ps->get_line();
            _op_assign->set_effect(s, _op_assign->get_effect(s));
            auto ret = _op_shift_left->get_effect(s);
            _op_shift_left->set_effect(s, ret);
            ps->set_line(line+1);
            return ret;
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            std::string ret;
            if( full_info )
                ret = "[INSTRUCTION][SMOL]:\n";
            return ret + _op_assign->get_lhs()->to_string(false) + " = smol(" +
                   _op_assign->get_rhs()->to_string(false) + ")\n";
        }

    private:
        std::unique_ptr<expressions::effects::Assign> _op_assign;
        std::unique_ptr<expressions::effects::bitvec::ShiftLeft> _op_shift_left;
    };
}
#endif //__INSTRUCTIONS_SMOL_H__
