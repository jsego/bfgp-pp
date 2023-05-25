#ifndef __ACTION_H__
#define __ACTION_H__

#include "utils/common.h"
#include "object_types.h"
#include "state.h"
#include "expressions/conditions/condition.h"
#include "expressions/effects/effect.h"

enum class ActionType{Math, Memory};

class Action{
public:
    /// Base constructor of an action name and type
	explicit Action(const std::string &name = "", const ActionType& act_type = ActionType::Math) :
        _name(name), _action_type(act_type){}

    /// Constructor to copy action data from another action
    explicit Action(Action *a): Action(a->get_name(), a->get_type()){
        // Copy params
        std::vector<Object*> params;
        for(const auto& par : a->get_parameters()) {
            auto par_copy = par->copy();
            params.emplace_back(par_copy.get());
            _parameters.emplace_back(std::move(par_copy));
        }
        // Copy preconditions
        for(const auto& prec : a->get_preconditions()) {
            auto prec_copy = prec->copy_condition();
            prec_copy->update_object_references(params);
            _preconditions.emplace_back(std::move(prec_copy));
        }
        // Copy effects
        for(const auto& eff : a->get_effects()) {
            auto eff_copy = eff->copy_effect();
            eff_copy->update_object_references(params);
            _effects.emplace_back(std::move(eff_copy));
        }
    }

    explicit Action(Action *a, const std::vector<Object*> &objects) : Action(a->get_name(), a->get_type()){
        // Build new arguments
        std::vector<Object*> new_params;
        for(const auto& obj : objects) {
            auto new_obj = obj->copy();
            new_params.emplace_back(new_obj.get());
            _parameters.emplace_back(std::move(new_obj));
        }
        // Copy and update preconditions
        for(const auto& prec : a->get_preconditions()) {
            auto prec_copy = prec->copy_condition();
            prec_copy->update_object_references(new_params);
            _preconditions.emplace_back(std::move(prec_copy));
        }
        // Copy effects
        for(const auto& eff : a->get_effects()) {
            auto eff_copy = eff->copy_effect();
            eff_copy->update_object_references(new_params);
            _effects.emplace_back(std::move(eff_copy));
        }
    }

    /// Constructor to copy an action and substitute parameters with the given pointers
    explicit Action(Action *a, const std::vector<variables::Variable*> &pointers):
        Action(a->get_name(),a->get_type()){
        // Set new pointer params
        _pointer_parameters.clear();
        _pointer_parameters.reserve(pointers.size());
        for(auto& var_ptr : pointers) {
            auto ptr = dynamic_cast<variables::Pointer*>(var_ptr);
            assert(ptr != nullptr);
            _pointer_parameters.emplace_back(ptr);
        }
        // Copy preconditions
        for(const auto& prec : a->get_preconditions()) {
            auto prec_copy = prec->copy_condition();
            prec_copy->set_pointer_references(pointers);
            _preconditions.emplace_back(std::move(prec_copy));
        }
        // Copy effects
        for(const auto& eff : a->get_effects()) {
            auto eff_copy = eff->copy_effect();
            eff_copy->set_pointer_references(pointers);
            _effects.emplace_back(std::move(eff_copy));
        }
    }

    /// Owns _preconditions and _effects
	virtual ~Action() = default;

    [[nodiscard]] std::unique_ptr<Action> copy(){
        return std::make_unique<Action>(this);
    }

    [[nodiscard]] std::unique_ptr<Action> copy_with_substitution(const std::vector<Object*> &objects){
        /// Copy this action and substitute the parameters with the given objects
        /// (assuming they are correct in number and order)
        return std::make_unique<Action>(this, objects);
    }

    [[nodiscard]] std::unique_ptr<Action> copy_with_substitution(const std::vector<variables::Variable*> &pointers){
        /// Copy this action and substitute the parameters with the given pointers
        /// (assuming they are correct in number and order)
        return std::make_unique<Action>(this, pointers);
    }
	
	[[nodiscard]] virtual bool is_applicable(State *s) const{
		for(const auto & precondition : _preconditions){
			if( not precondition->eval_condition(s) ) {
                return false;
            }
		}
        return true;
	}
	
	virtual value_t apply(State *s) {
        vec_value_t num_effects(_effects.size(), 0 );

        // Copy all effects in a local vector
		for( size_t i = 0; i < _effects.size(); i++ )
			num_effects[i] = (_effects[i]->get_effect(s));

		// Following the planning community convention
		// first apply the negative effects, then positives
        for(size_t i=0; i<_effects.size(); i++)
            if(num_effects[i]==0) _effects[i]->set_effect(s,0);
        for(size_t i=0;i<_effects.size();i++)
            if(num_effects[i]>0) _effects[i]->set_effect(s,num_effects[i]);

		// Return 0 by default if there are no effects, e.g., CMP action, otherwise return the last effect
		if( num_effects.empty() ) return 0;
		return num_effects[int(num_effects.size())-1];
	}

    virtual void add_pointer(variables::Pointer* ptr){
        _pointer_parameters.emplace_back(ptr);
    }

    virtual void add_parameter(std::unique_ptr<Object> param){
        _parameters.emplace_back(std::move(param));
    }
	
	virtual void add_condition(std::unique_ptr<expressions::conditions::Condition> cond ){
        // ToDo: check that each condition argument matches one of the action argument types
		_preconditions.emplace_back( std::move(cond) );
	}

	virtual void add_effect(std::unique_ptr<expressions::effects::Effect> eff ){
        // ToDo: check that each effect argument matches one of the action argument types
		_effects.emplace_back( std::move(eff) );
	}

	[[nodiscard]] virtual std::string get_name() const{
		return _name;
	}

    [[nodiscard]] virtual std::string get_signature(bool full_info) const{
        auto name = _name + "(";
        if(not _pointer_parameters.empty()){
            // Action grounded over pointer parameters
            for (const auto &ptr_param: _pointer_parameters)
                name += (ptr_param == *_pointer_parameters.begin() ? "" : ",") + ptr_param->get_name() +
                        (full_info?":" +ptr_param->get_type()->to_string(false):"");
        }
        else {
            for (const auto &param: _parameters)
                name += (param == *_parameters.begin() ? "" : ",") + param->get_name() +
                        (full_info?":" +param->get_type()->to_string(false):"");
        }
        name += ")";
        return name;
    }
	
	[[nodiscard]] virtual ActionType get_type() const{
		return _action_type;
	}

    [[nodiscard]] virtual id_type get_next_parameter_id() const{
        return (id_type)_parameters.size();
    }

    [[nodiscard]] virtual Object* get_parameter(size_t idx) const{
        assert(idx < _parameters.size());
        return _parameters[idx].get();
    }

    // ToDo: to test (inefficient)
    [[nodiscard]] virtual Object* get_parameter(const std::string& name) const{
        for(const auto& p : _parameters)
            if(p->get_name() == name)
                return p.get();
        return nullptr;
    }

    // ToDo: inefficient, often used only to get their names
    [[nodiscard]] virtual std::vector<Object*> get_parameters() const{
        std::vector<Object*> parameters;
        for(const auto& pars : _parameters){
            parameters.emplace_back(pars.get());
        }
        return parameters;
    }

    [[nodiscard]] virtual size_t get_num_parameters() const{
        return _parameters.size();
    }

    // ToDo: inefficient, often used only to get their names
	[[nodiscard]] virtual std::vector<expressions::conditions::Condition*> get_preconditions() const{
        std::vector<expressions::conditions::Condition*> v_conds;
        for( const auto& prec : _preconditions){
            v_conds.emplace_back(prec.get());
        }
	    return v_conds;
	}

    // ToDo: inefficient, often used only to get their names
	[[nodiscard]] virtual std::vector<expressions::effects::Effect*> get_effects() const{
        std::vector<expressions::effects::Effect*> v_effs;
        for( const auto& eff : _effects){
            v_effs.emplace_back(eff.get());
        }
        return v_effs;
	}
	
	[[nodiscard]] virtual std::string to_string(bool full_info ) const{
		if( !full_info ) return get_signature(full_info);
        std::string ret = "[ACTION]: " + get_signature(full_info) + "\n";
		ret += "[TYPE]: " + (_action_type==ActionType::Math?std::string("math"):std::string("memory")) + "\n";
		ret += "[PRECONDITIONS]:";
		for(const auto& prec : _preconditions){
			ret += " " + prec->to_string(false);
		}
		ret += "\n[EFFECTS]:";
		for(const auto& eff : _effects){
			ret += " " + eff->to_string(false);
		}
		return ret;
	}

    [[nodiscard]] virtual std::string to_pddl_grounded() const{
        auto pddl_grounded = std::string("(") + _name;
        if(not _pointer_parameters.empty()){
            // Action grounded over pointer parameters
            for (const auto &ptr_param: _pointer_parameters)
                pddl_grounded += " " + ptr_param->get_object()->get_name();
        }
        pddl_grounded += ")";
        return pddl_grounded;
    }
	
protected:
    std::string _name;
    ActionType _action_type;
    std::vector<variables::Pointer*> _pointer_parameters;
    std::vector<std::unique_ptr<Object>> _parameters;
    std::vector< std::unique_ptr<expressions::conditions::Condition> > _preconditions;
    std::vector< std::unique_ptr<expressions::effects::Effect> > _effects;
};

#endif
