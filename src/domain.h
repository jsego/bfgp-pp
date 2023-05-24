#ifndef __DOMAIN_H__
#define __DOMAIN_H__

#include "utils/common.h"
//#include "state_descriptor.h"
#include "object_types.h"
#include "function.h"
#include "action.h"
#include "object.h"

class Domain{
public:
	explicit Domain(const std::string &name = "") : _name(name){
        add_object_type(std::make_unique<ObjectType>("object",nullptr)); // create base "object" type
    }

    ///
    /// Owns _object_types, _constants, _functions and _actions
    ///
	~Domain() = default;

    ///
    /// Setter functions
    ///
	void set_name(const std::string &name = ""){
		_name = name;
	}

    void add_object_type(std::unique_ptr<ObjectType> ot){
        _object_type_name_to_idx[ot->get_name()] = _object_types.size();
        _object_types.emplace_back(std::move(ot));
    }

    void add_constant(std::unique_ptr<Object> o){
        _constant_name_to_idx[o->get_name()] = _constants.size();
        _constants.emplace_back(std::move(o));
    }

    void add_function(std::unique_ptr<Function> f){
        //_function_name_to_idx[f->get_signature()] = _functions.size();
        _function_name_to_idx[f->get_name()] = _functions.size();
        _functions.emplace_back(std::move(f));
    }

	void add_action(std::unique_ptr<Action> a ){
        _action_name_to_idx[a->get_signature(true)] = _actions.size();
		_actions.emplace_back(std::move(a));
	}

    ///
    /// Getters related functions (either by Index or Name)
    ///
    [[nodiscard]] std::string get_name() const{
        return _name;
    }

    // FIXME (Issue #47): inefficient if used exhaustively, e.g., O(|ObjectTypes|)
    [[nodiscard]] std::vector<ObjectType*> get_object_types() const{
        std::vector<ObjectType*> object_types;
        for(const auto& ot : _object_types)
            object_types.emplace_back(ot.get());
        return object_types;
    }

    // FIXME (Issue #47): inefficient if used exhaustively, e.g., O(|Functions|)
    [[nodiscard]] std::vector<Function*> get_functions() const{
        std::vector<Function*> functions;
        for(const auto& f : _functions)
            functions.emplace_back(f.get());
        return functions;
    }

    // FIXME (Issue #47): inefficient if used exhaustively, e.g., O(|Actions|)
    [[nodiscard]] std::vector<Action*> get_actions() const{
        std::vector<Action*> actions;
        for(const auto& act : _actions)
            actions.emplace_back(act.get());
		return actions;
	}

    [[nodiscard]] ObjectType* get_object_type(size_t idx) const{
        assert(idx < _object_types.size());
        return _object_types[idx].get();
    }

    [[nodiscard]] ObjectType* get_object_type(const std::string& obj_type_name = "") const{
        auto it = _object_type_name_to_idx.find(obj_type_name);
        if(it == _object_type_name_to_idx.end() ) return nullptr;
        return get_object_type(it->second);
    }

    [[nodiscard]] Object* get_constant(size_t idx) const{
        assert(idx < _constants.size());
        return _constants[idx].get();
    }

    [[nodiscard]] Object* get_constant(const std::string& const_name = "") const{
        auto it = _constant_name_to_idx.find(const_name);
        if(it == _constant_name_to_idx.end()) return nullptr;
        return get_constant(it->second);
    }

    // FIXME (Issue #47): inefficient method
    [[nodiscard]] std::vector<Object*> get_constants() const{
        std::vector<Object*> constants;
        for(auto const& c : _constants){
            constants.emplace_back(c.get());
        }
        return constants;
    }

    [[nodiscard]] Function* get_function(size_t idx) const{
        assert(idx < _functions.size());
        return _functions[idx].get();
    }

    [[nodiscard]] Function* get_function(const std::string& func_name = "") const{
        auto it = _function_name_to_idx.find(func_name);
        if(it == _function_name_to_idx.end()) return nullptr;
        return get_function(it->second);
    }
	
	[[nodiscard]] Action* get_action(size_t idx) const{
        assert(idx < _actions.size());
		return _actions[idx].get();
	}

	[[nodiscard]] Action* get_action(const std::string &act_signature = "") const{
	    auto it = _action_name_to_idx.find(act_signature );
	    if( it == _action_name_to_idx.end() ) return nullptr;
	    return get_action(it->second);
	}

    [[nodiscard]] id_type get_next_const_id() const{
        return id_type(_constants.size());
    }

    [[nodiscard]] id_type get_next_func_id() const{
        return id_type(_functions.size());
    }

    [[nodiscard]] std::string to_string(bool print_actions) const{
        std::string ret = "[DOMAIN]: " + _name + "\n";

		/// Print Type Hierarchy
		if(not _object_types.empty()) ret += "[TYPES]:\n";
		for(const auto& t : _object_types)
            if(t->get_name() != "object") // skip the base object definition
                ret += t->get_definition() + "\n";

        /// Print Constant objects
        if(not _constants.empty()) ret += "[CONSTANTS]:\n";
        for(const auto& c : _constants)
            ret += c->to_string(true) + "\n";

        /// Print Function definitions
        assert(not _functions.empty());
        ret += "[FUNCTIONS]:\n";
        for(const auto& f : _functions)
            ret += f->to_string(false) + "\n";

        /// Print Action definitions (possibly empty and all knowledge in the theory)
        if(print_actions) {
            if (not _actions.empty()) ret += "[ACTIONS]:\n";
            for (const auto &act: _actions)
                ret += act->to_string(true) + "\n";
        }

		return ret;
	}

private:
    std::string _name;

    /// Type hierarchy, Function definitions, and Action schemas
    std::vector<std::unique_ptr<ObjectType>> _object_types;
    std::vector<std::unique_ptr<Object>> _constants;
    std::vector<std::unique_ptr<Function>> _functions;
    std::vector<std::unique_ptr<Action>> _actions;

    /// Map symbol names into indexes
    map_str_idx_t _object_type_name_to_idx;
    map_str_idx_t _constant_name_to_idx;
    map_str_idx_t _function_name_to_idx;
    map_str_idx_t _action_name_to_idx;
};

#endif
