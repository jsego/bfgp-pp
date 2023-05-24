//
// Created by js on 27/05/22.
//

#ifndef __INSTRUCTIONS_BITVEC_ITE_H__
#define __INSTRUCTIONS_BITVEC_ITE_H__

#include "../instruction.h"

namespace instructions::bitvec{
    class ITE : public Instruction{
    public:
        ITE(std::unique_ptr<expressions::effects::Effect> true_op,
            std::unique_ptr<expressions::effects::Effect> false_op) :
        _true_op(std::move(true_op)), _false_op(std::move(false_op)){};

        ~ITE() override = default;

        [[nodiscard]] value_t apply(Instance *ins, ProgramState* ps) override{
            auto s = ps->get_state();

            bool evals_true = true;
            for( size_t idx = 0; evals_true && idx < _conds.size(); idx++ ){
                evals_true &= (_conds[idx].first->get_value()==_conds[idx].second);
            }

            value_t ret;
            if( evals_true ){
                ret =  _true_op->get_effect(s);
                _true_op->set_effect(s,ret);
            }
            else{
                ret = _false_op->get_effect(s);
                _false_op->set_effect(s, ret);
            }
            ps->set_line(ps->get_line()+1);
            return ret;
        }

        [[nodiscard]] std::string to_string(bool full_info) const override{
            std::string ret;
            if( full_info ) ret = "[INSTRUCTION]: [ITE]:\n";
            else ret = "ite(";

            for(const auto& cond : _conds)
                ret += "("+ cond.first->get_name() + "=" + std::to_string(cond.second) +")";

            if( !full_info ) {
                auto t_op = _true_op->to_string(false);
                auto f_op = _false_op->to_string(false);
                if(t_op[(int)t_op.size()-1] == '\n') t_op = t_op.substr(0,(int)t_op.size()-1);
                if(f_op[(int)f_op.size()-1] == '\n') f_op = f_op.substr(0, (int)f_op.size()-1);
                ret += "?" + t_op + ":" + f_op + ")\n";
            }
            else{
                ret += "IF TRUE => " + _true_op->to_string(false) + "\n";
                ret += "IF FALSE => " + _false_op->to_string(false) + "\n";
            }

            return ret;

        }
    private:
        std::vector<std::pair<variables::Flag*,value_t>> _conds;  // (flag1=value1)&(flag2=value2)&...
        std::unique_ptr<expressions::effects::Effect> _true_op;
        std::unique_ptr<expressions::effects::Effect> _false_op;
    };
}

#endif //__INSTRUCTIONS_BITVEC_ITE_H__
