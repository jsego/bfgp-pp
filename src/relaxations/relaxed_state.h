//
//
// Created by js on 2/09/22.

#ifndef __RELAXATIONS_RELAXED_STATE_H__
#define __RELAXATIONS_RELAXED_STATE_H__

#include "../utils/common.h"
#include "../variables/state_variable.h"
#include "../state.h"

namespace relaxation{
    class RelaxedState{
        typedef std::map<std::string, set_value_t> map_rfact_t;  // map of relaxed fact names to set of values
    public:
        explicit RelaxedState() = default;

        explicit RelaxedState(State *s){
            for(const auto f : s->get_facts()){
                add_fact(f);
            }
        }

        ~RelaxedState() = default;

        void add_fact(variables::StateVariable *sv){
            _relaxed_facts[sv->to_string(false)].insert(sv->get_value());
            //_relaxed_facts[sv->get_name()].insert(sv->get_value());
        }

        [[nodiscard]] bool has_fact(const std::string &name, value_t value) const{
            auto it = _relaxed_facts.find(name);
            // If found check whether the set contains the value
            if(it != _relaxed_facts.end())
                return (it->second).find(value) != (it->second).end();
            // Otherwise, it can only be false/0-valued (closed world assumption)
            return value == 0;

        }

        [[nodiscard]] bool has_fact(variables::StateVariable *sv) const{
            return has_fact(sv->to_string(false), sv->get_value());
        }

        [[nodiscard]] map_rfact_t get_facts() const {
            return _relaxed_facts;
        }

        [[nodiscard]] int get_num_facts() const{
            int total = 0;
            for(const auto & rfact : _relaxed_facts){
                total += int( rfact.second.size() );
            }
            return total;
        }

        [[nodiscard]] std::string to_string() const{
            std::string output = "[RELAXED-STATE]:\n";
            for(const auto& rfact : _relaxed_facts){
                output += "(" + rfact.first + "={";
                for(const auto &v : rfact.second){
                    output += (v!=*rfact.second.begin()?",":"") + std::to_string(v);
                }
                output += "})\n";
            }
            return output;
        }

    private:
        map_rfact_t _relaxed_facts;  // set of relaxed facts
    };
}

#endif //__RELAXATIONS_RELAXED_STATE_H__
