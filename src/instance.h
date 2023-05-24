#ifndef __INSTANCE_H__
#define __INSTANCE_H__

#include "utils/common.h"
#include "state.h"
#include "expressions/conditions/condition.h"
#include "domain.h"

class Instance{
public:
	explicit Instance(const std::string &name = "", id_type instance_id = 0, Domain *dom = nullptr ) :
            _domain(dom), _name(name), _init(nullptr), _goal_state(std::make_unique<State>()), _instance_id(instance_id){
        // ToDo: test this part, which copies constants into the instance (possible bug when used in the domain actions)
        if(_domain)
            for(const auto&c : _domain->get_constants()){
                add_object(c->copy());
            }
    }

    /// Owns _objects, _init and _goal
	~Instance() = default;

    /// Setters
	void set_name(const std::string &name = ""){
		_name = name;
	}

    /*void set_instance_id(id_type instance_id ){
        _instance_id = instance_id;
    }*/

    void add_object(std::unique_ptr<Object> obj){
        /// Save the raw object pointer for its type name and all its ancestor type names in the hierarchy
        _typed_obj_to_idx[obj->get_name()] = _type_to_objs[obj->get_type()->get_name()].size();
        _type_to_objs[obj->get_type()->get_name()].emplace_back(obj.get());
        auto type_ancestors = obj->get_type()->get_ancestors();
        for(const auto& ta : type_ancestors)
            _type_to_objs[ta->get_name()].emplace_back(obj.get());

        /// Save the object index by its name
        _obj_to_idx[obj->get_name()] = _objects.size();

        /// Transfer object ownership to the instance
        _objects.emplace_back(std::move(obj));
    }

    // ToDo: it would be better to add fact by fact, and check its correctness with the domain functions
	void set_initial_state(std::unique_ptr<State> init ){
		_init = std::move(init);
	}

    // ToDo: check the condition is well-formed with the domain functions
	void add_goal_condition(std::unique_ptr<expressions::conditions::Condition> cond ){
        // Add it also as a fact // FIXME: this could cause errors when goal different from 'func(objs)=value'
        auto lhs_sv = dynamic_cast<variables::StateVariable*>(cond->get_lhs());
        auto rhs_cv = dynamic_cast<variables::ConstantValue*>(cond->get_rhs());
        assert( lhs_sv != nullptr and rhs_cv != nullptr);
        auto func = lhs_sv->get_function();
        auto objs = lhs_sv->get_objects();
        auto val = rhs_cv->get_value();
        auto fact = std::make_unique<variables::StateVariable>(func, objs, val);
        _goal_state->add_fact(std::move(fact));

        // Finally move the condition to _goal
        _goal.emplace_back( std::move(cond) );
	}

    /// Getters
    [[nodiscard]] std::string get_name() const{
		return _name;
	}

    [[nodiscard]] Domain* get_domain() const{
        return _domain;
    }

    [[nodiscard]] id_type get_next_obj_id() const{
        return (id_type)_objects.size();
    }
	
	[[nodiscard]] State* get_initial_state() const{
		return _init.get();
	}

    // ToDo: inefficient, is there a faster way to return raw pointers from a vector of unique_ptr?
    [[nodiscard]] std::vector<expressions::conditions::Condition*> get_goal_condition() const{
        std::vector<expressions::conditions::Condition*> goal_conds;
        for(const auto& g : _goal ){
            goal_conds.emplace_back(g.get());
        }
        return goal_conds;
	}
	
	[[nodiscard]] expressions::conditions::Condition* get_condition(id_type idx ) const{
        assert(idx < (id_type)_goal.size());
		return _goal[ idx ].get();
	}

    // FIXME (Issue #47): inefficient method
    [[nodiscard]] std::vector<Object*> get_raw_objects() const{
        std::vector<Object*> raw_obj_ptrs;
        for(const auto& obj : _objects)
            raw_obj_ptrs.emplace_back(obj.get());
        return raw_obj_ptrs;
    }

    [[nodiscard]] size_t get_typed_object_idx(Object *obj) const{
        auto it = _typed_obj_to_idx.find(obj->get_name());
        assert(it != _typed_obj_to_idx.end());
        return it->second;
    }

    [[nodiscard]] Object* get_object(size_t idx) const{
        /// Get a raw object pointer by its index
        assert(idx < _objects.size());
        return _objects[idx].get();
    }

    [[nodiscard]] Object* get_object(const std::string& name) const{
        /// Get a raw object pointer by its name
        auto it = _obj_to_idx.find(name);
        if(it == _obj_to_idx.end()) return nullptr;
        return get_object(it->second);
    }

    [[nodiscard]] std::vector<Object*> get_typed_objects(const std::string& name) const{
        /// Get all objects of a specific type
        auto it = _type_to_objs.find(name);
        if(it == _type_to_objs.end()) return {};
        return it->second;
    }

    [[nodiscard]] value_t get_typed_variable_domain(const std::string& type_name) const{
        auto it = _type_to_objs.find(type_name);
        if(it == _type_to_objs.end()) return 0;
        return (value_t)(it->second).size();
    }

	[[nodiscard]] id_type get_instance_id() const {
	    return _instance_id;
	}

    [[nodiscard]] State* get_goal_state() const{
        return _goal_state.get();
    }

	/// Full info printing
    [[nodiscard]] std::string to_string() const{
        std::string ret = "[INSTANCE]: " + _name + "\n";
        ret += "[DOMAIN]: " + (_domain?_domain->get_name():"") + "\n";
        ret += "[OBJECTS]:";
        for(const auto& o : _objects)
            ret += " " + o->to_string(true);
        ret += "\n";

		ret += "[INIT]:";
		if( _init ) ret += " " + _init->to_string(false);
        ret += "\n";

		ret += "[GOAL]:";
		for(const auto& g : _goal)
			ret += " " + g->to_string(false);
		return ret;
	}
	
private:
    /// Main instance attributes
    Domain *_domain;
    std::string _name;
    //Domain* domain; // this will be saved in generalized domain which is shared for all instances
    std::vector<std::unique_ptr<Object>> _objects;
	std::unique_ptr<State> _init;
    std::vector< std::unique_ptr<expressions::conditions::Condition> > _goal;
    std::unique_ptr<State> _goal_state; // Only in closed-world settings

    /// Fast type and object access
    std::map< std::string, std::vector<Object*> > _type_to_objs; // object type name -> vector of object pointers
    std::map< std::string, size_t> _obj_to_idx;  // object name -> index in _objects
    std::map< std::string, size_t> _typed_obj_to_idx;  // object name -> index in _typed_to_objs
 
    /// Instance id
    id_type _instance_id; // is this relevant?
};

#endif
