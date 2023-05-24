#ifndef __STATE_H__
#define __STATE_H__

#include "utils/common.h"
#include "variables/state_variable.h"

class State {
public:
    typedef std::set<std::unique_ptr<variables::StateVariable>, variables::StateVariableComparer> set_fact_t;  // vector of fact unique pointers
    //typedef std::set<std::unique_ptr<variables::StateVariable>> set_fact_t;  // vector of fact unique pointers

    // Default constructor
    State() = default;

    // Constructor mainly used to make copies and propagate effects
    explicit State (State *s){
        for(const auto& it : s->get_facts()){
            _facts.insert(it->copy_no_pointers() );
        }
    }

	std::unique_ptr<State> copy() {
        return std::make_unique<State>(this);
	}

    void add_fact(std::unique_ptr<variables::StateVariable> f){
        /// Adds a fact without checking if the StateVariable exists
        _facts.insert(std::move(f));
    }

    [[nodiscard]] variables::StateVariable* get_fact(variables::StateVariable* f) const{
        auto uf = f->copy_no_pointers(); // make unique fact // ToDo: unnecessary copy of a fact to get their value on a state
        const auto& it = _facts.find(uf);  // find the func(objects) header in s
        if( it == _facts.end() ) return nullptr;
        return (*it).get();
    }

    value_t get_value(variables::StateVariable* f) const{
        /// If the StateVariable exists in s, returns the value in s, otherwise returns 0
        auto it = get_fact(f);
        if( it == nullptr ) return value_t{0}; // if the StateVariable doesn't exist, return 0
        return it->get_value(); // otherwise, return the existing value
    }

   void set_value(variables::StateVariable* f, const value_t& value){
        auto uf = f->copy_no_pointers();  // make unique fact // ToDo: unnecessary copy of a fact to get their value on a state
        const auto& it = _facts.find(uf); // find the func(objects) header in s
        if( it == _facts.end() ) add_fact(std::move(uf) ); // if the fact doesn't exist, create it // ToDo:  do the copy in add_fact
        else (*it)->set_value(value);  // otherwise, update its value
   }


    // FIXME (Issue #47): innefficient if used extensively, O(|facts|)
    [[nodiscard]] std::vector<variables::StateVariable*> get_facts() const{
        std::vector<variables::StateVariable*> facts;
        for(const auto& f : _facts)
            facts.emplace_back(f.get());
        return facts;
    }
    /*[[nodiscard]] set_fact_t const& get_facts(){  // FIXME (Issue #47): not the best choice
        return _facts;
    }*/

    [[nodiscard]] std::string to_string(bool full_info) const {
        std::string ret = (full_info?"[STATE]: ":"");
        for (const auto& fact: _facts)
            ret += (fact!=*_facts.begin()?" ":"") + fact->get_name();
            //ret += (fact!=*_facts.begin()?" ":"") + fact->to_string(true);
        return ret;
    }

private:
    set_fact_t _facts;  // set of facts
};

#endif
