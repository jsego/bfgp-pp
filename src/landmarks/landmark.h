//
// Created by js on 6/09/22.
//

#ifndef __LANDMARKS_LANDMARK_H__
#define __LANDMARKS_LANDMARK_H__

#include "../utils/common.h"
#include "../relaxations/relaxed_state.h"
#include "../relaxations/relaxed_planning_graph.h"

namespace landmarks {
    class Landmark {
    public:
        explicit Landmark(id_type id) : _landmark_id(id), _is_active(true) {}

        Landmark(Landmark *l) {
            _landmark_id = -1;
            _fact_ids = l->get_fact_ids();
            _is_active = true;
        }

        ~Landmark() = default;

        std::unique_ptr<Landmark> copy() {
            return std::unique_ptr<Landmark>(this);
        }

        void add_fact(id_type fact_id) {
            _fact_ids.insert(fact_id);
        }

        void set_facts(set_id_t &fact_ids) {
            _fact_ids = fact_ids;
        }

        [[nodiscard]] bool has_fact(id_type fact_id) const {
            return (_fact_ids.find(fact_id) != _fact_ids.end());
        }

        [[nodiscard]] int get_num_of_facts() const {
            return (int) _fact_ids.size();
        }

        [[nodiscard]] id_type get_landmark_id() const { return _landmark_id; }

        [[nodiscard]] set_id_t get_fact_ids() const {
            return _fact_ids;
        }

        // Disjunctive facts checking
        [[nodiscard]] bool holds(relaxation::RelaxedPlanningGraph *rpg, relaxation::RelaxedState *rs) const {
            for (auto f_id: _fact_ids) {
                auto fact_name = rpg->get_fact_name(f_id);
                if(rs->has_fact(fact_name, value)) return true;
            }
            return false;
        }

        [[nodiscard]] bool holds(relaxation::RelaxedPlanningGraph *rpg, State *s) const {
            for(const auto& f_id : _fact_ids){
                auto fact_name = rpg->get_fact_name(f_id);
                if(s->has_fact(fact_name, value)) return true;
            }
            return false;
        }

        [[nodiscard]] bool is_active() const{
            return _is_active;
        }

        void deactivate(){
            _is_active = false;
        }

        [[nodiscard]] std::string to_string(relaxation::RelaxedPlanningGraph *rpg) const {
            auto output = "[LANDMARK]: L#"+ std::to_string(_landmark_id)+ "->{";
            for (auto it = _fact_ids.begin(); it != _fact_ids.end(); it++) {
                output += (it != _fact_ids.begin() ? "|" : "") + rpg->get_fact_name(*it);
            }
            output += "}\n";
            return output;
        }

    private:
        // Disjunctive facts
        set_id_t _fact_ids;
        // Landmark id
        id_type _landmark_id;
        // Active landmark (to guarantee constant access, landmarks are kept in memory but may be deactivated)
        bool _is_active;
    };
}
#endif //__LANDMARKS_LANDMARK_H__