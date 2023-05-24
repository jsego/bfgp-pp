//
// Created by js on 25/05/22.
//

#ifndef __INSTRUCTIONS_PLANNING_ACTION_H__
#define __INSTRUCTIONS_PLANNING_ACTION_H__

#include "instruction.h"
#include "../action.h"

namespace instructions{
    class PlanningAction : public Instruction{
    public:
        explicit PlanningAction( std::unique_ptr<Action> act ) : Instruction(act->get_name()), _act(std::move(act)) {}

        ~PlanningAction() override = default;

        [[nodiscard]] bool is_applicable(Instance* ins, ProgramState *ps ) const override{
            return _act->is_applicable(ps->get_state());
        }

        value_t apply(Instance* ins, ProgramState *ps ) override{
            auto s = ps->get_state();
            auto line = ps->get_line();
            value_t res = 0;

            // Conditional effects
            if(is_applicable(ins, ps) ){
                res = _act->apply(s);
            }
            ps->set_line(line + 1);
            return res;
        }

        [[nodiscard]] std::string get_name(bool full_info) const override{
            return _act->get_signature(full_info);
        }

        [[nodiscard]] ActionType get_type() const override{
            return _act->get_type();
        }

        [[nodiscard]] virtual Action* get_action() const{
            return _act.get();
        }

        [[nodiscard]] virtual std::vector<Object*> get_arguments() const{
            return _act->get_parameters();
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override {
            return (full_info?"[INSTRUCTION]: ":"") + _act->to_string(full_info);
        }

    private:
        std::unique_ptr<Action> _act;
    };
}

#endif //__INSTRUCTIONS_PLANNING_ACTION_H__
