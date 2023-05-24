//
// Created by js on 2/09/22.
//

#ifndef __RELAXATIONS_RELAXED_ACTION_H__
#define __RELAXATIONS_RELAXED_ACTION_H__

#include "../action.h"
#include "relaxed_state.h"

namespace relaxation{
    class RelaxedAction {
        /// A Relaxed Action is an Action grounded with the objects of the instance
        /// that checks its applicability and applies effects to a Relaxed State
    public:
        explicit RelaxedAction( Action *act ){
            /// 0. Copy the name, action type and parameters (they must be objects)
            _name = act->get_name();
            _action_type = act->get_type();
            std::vector<Object*> new_params;
            for(const auto& o : act->get_parameters()){
                auto obj = o->copy();
                new_params.emplace_back(obj.get());
                _parameters.emplace_back(std::move(obj));
            }
            /// 1. Build precondition facts from grounded action act
            for(const auto& prec : act->get_preconditions()){
                auto sv = dynamic_cast<variables::StateVariable*>(prec->get_lhs());
                assert(sv != nullptr);
                auto cv = dynamic_cast<variables::ConstantValue*>(prec->get_rhs());
                assert(cv != nullptr);
                auto fact = std::make_unique<variables::StateVariable>(sv);
                fact->set_value(cv->get_value());
                fact->update_object_references(new_params);
                _preconditions.emplace_back(std::move(fact));
            }

            /// 2. Build effect facts from grounded action act
            for(const auto& eff : act->get_effects()){
                auto sv = dynamic_cast<variables::StateVariable*>(eff->get_lhs());
                assert(sv != nullptr);
                auto cv = dynamic_cast<variables::ConstantValue*>(eff->get_rhs());
                assert(cv != nullptr);
                auto fact = std::make_unique<variables::StateVariable>(sv);
                fact->set_value(cv->get_value());
                fact->update_object_references(new_params);
                _effects.emplace_back(std::move(fact));
            }

            /// 3. Save the action hasn't been applied
            _applied = false;
        }
        ~RelaxedAction() = default;

        void set_applied(bool applied){
            _applied = applied;
        }

        [[nodiscard]] bool get_applied() const{
            return _applied;
        }

        [[nodiscard]] std::vector<variables::StateVariable*> get_prec_facts() const{
            // FIXME (Issue #47): inefficient method
            std::vector<variables::StateVariable*> prec_facts;
            for(const auto& prec : _preconditions)
                prec_facts.emplace_back(prec.get());
            return prec_facts;
        }

        [[nodiscard]] std::vector<variables::StateVariable*> get_effect_facts() const{
            // FIXME (Issue #47): inefficient method
            std::vector<variables::StateVariable*> eff_facts;
            for(const auto& eff : _effects)
                eff_facts.emplace_back(eff.get());
            return eff_facts;
        }


        bool is_applicable(RelaxedState *s) const{
            /// Return the applicability of a relaxed action over a relaxed state
            for(const auto& cond: _preconditions){
                if(not s->has_fact(cond.get())) return false;
            }
            return true;
        }

        /* ToDo: uncomment this when implementing Landmarks
        bool has_effect(variables::StateVariable *sv){
            /// Check if the action is has a specific fact in effects
            for(const auto& eff : _effects){
                if( sv->get_function() == eff->get_function() and
                    sv->get_objects() == eff->get_objects() and
                    sv->get_value() == eff->get_value() )
                    return true;
            }
            return false;
        }*/

        void apply( RelaxedState *s ){
            for(const auto& eff : _effects){
                s->add_fact(eff.get());
            }
            _applied = true;
        }

        [[nodiscard]] std::string get_name() const{
            return _name;
        }

        [[nodiscard]] std::string get_signature() const{
            std::string output = _name +"(";
            for(size_t idx = 0; idx < _parameters.size(); idx++)
                output += (idx?",":"") + _parameters[idx]->get_name();
            output += ")";
            return output;
        }

        [[nodiscard]] std::string to_string() const{
            std::string output = "[RELAXED-ACTION]: " + get_signature() + "\n";
            output += "[PRECONDITIONS]:";
           for(const auto& sv : _preconditions)
               output += " " + sv->to_string(true);
            output += "\n[EFFECTS]:";
            for(const auto& sv : _effects)
                output += " " + sv->to_string(true);
            return output;
        }

    private:
        std::string _name;
        ActionType _action_type;
        std::vector<std::unique_ptr<Object>> _parameters;
        std::vector<std::unique_ptr<variables::StateVariable>> _preconditions;
        std::vector<std::unique_ptr<variables::StateVariable>> _effects;
        bool _applied;

    };
}

#endif //__RELAXATIONS_RELAXED_ACTION_H__
