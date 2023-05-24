//
// Created by js on 2/09/22.
//

#ifndef __RELAXATIONS_RELAXED_PLANNING_GRAPH_H__
#define __RELAXATIONS_RELAXED_PLANNING_GRAPH_H__

#include "../domain.h"
#include "../instance.h"
#include "../grounder.h"

#include "relaxed_action.h"

namespace relaxation{
    class RelaxedPlanningGraph{
    public:
        explicit RelaxedPlanningGraph( Domain* dom, Instance* ins)://, value_t max_val)
            _dom(dom), _ins(ins){
            // Reset containers
            reset();

            // Precompute relaxed actions
            precompute_relaxed_actions();
        }

        /// Owns all relaxed_actions
        ~RelaxedPlanningGraph() = default;

        void precompute_relaxed_actions(){
            /// Precompute all grounded relaxed actions
            auto grounder = std::make_unique<Grounder>();
            auto all_objs = _ins->get_raw_objects();
            for(const auto& a : _dom->get_actions()){
                /// Compute action "a" grounding over the instance objects
                std::vector<ObjectType*> arg_types;
                for(const auto& o : a->get_parameters()) arg_types.emplace_back(o->get_type());
                std::vector<std::vector<Object*>> groundings;
                std::vector<Object*> current_grounding(arg_types.size());
                grounder->ground_over_objects(arg_types, all_objs, groundings, current_grounding);

                for(const auto& gr : groundings){
                    auto grounded_act = a->copy_with_substitution(gr);
                    _relaxed_actions.emplace_back(std::make_unique<RelaxedAction>(grounded_act.get()));
                }
            }
        }

        id_type get_fact_id(variables::StateVariable* sv){
            if(sv == nullptr) return 0;  // default id
            auto it = _fact_name_to_id.find(sv->get_name());
            if(it != _fact_name_to_id.end()) return it->second;
            auto id =  id_type(_fact_name_to_id.size())+1; // start counting from 1 (0 is reserved for nullptr)
            _fact_name_to_id[sv->get_name()] = id;
            _fact_id_to_name.emplace_back(sv->get_name());
            return id;
        }

        std::string get_fact_name(id_type f_id){
            assert(f_id < (id_type)_fact_id_to_name.size());
            return _fact_id_to_name[f_id];
        }

        void add_parent(variables::StateVariable* parent, variables::StateVariable* child, RelaxedAction *ra){
            auto parent_id = get_fact_id(parent);
            auto child_id = get_fact_id(child);
            if(child_id >= (id_type)_parent_facts.size()) _parent_facts.resize(child_id+1);
            _parent_facts[child_id].emplace_back(std::make_pair(parent_id, ra));
        }

        void add_child(variables::StateVariable* child, variables::StateVariable* parent, RelaxedAction *ra){
            auto parent_id = get_fact_id(parent);
            auto child_id = get_fact_id(child);
            if(parent_id >= (id_type)_child_facts.size()) _child_facts.resize(parent_id+1);
            _child_facts[parent_id].emplace_back(std::make_pair(child_id, ra));
        }

        void update_graph_from_relaxed_action(RelaxedAction *ra){
            auto precs = ra->get_prec_facts();
            auto effs = ra->get_effect_facts();
            for(const auto& prec : precs){
                for(const auto& eff : effs){
                    add_parent(prec, eff, ra);
                    add_child(eff, prec, ra);
                }
            }
        }

        void reset(){
            _unsolvable = false;
            _fact_id_to_name.clear();
            _fact_id_to_name.resize(1);
            _fact_name_to_id.clear();
            _child_facts.clear();
            _parent_facts.clear();
            _fact_layer.clear();
            _fact_layer.resize(1);
            _action_layer.clear();
            for(const auto& ra: _relaxed_actions) ra->set_applied(false);
        }

        void build_relaxed_graph(State* root) {
            /// 0. Reset containers
            reset();

            /// 1.a Get facts from the root state
            auto rs = std::make_unique<RelaxedState>( root );

            /// 1.b Add init facts to the graph
            for(const auto& fact : root->get_facts()){
                add_parent(nullptr, fact, nullptr);
                add_child(fact, nullptr, nullptr);
                _fact_layer[0].insert(get_fact_id(fact));
            }

            /// 1.c Filter out all relaxed actions whose effects hold in the initial state
            for(const auto& ra: _relaxed_actions){
                bool is_novel = false;
                for(const auto& eff : ra->get_effect_facts()){
                    if(not rs->has_fact(eff)){ is_novel = true; break;}
                }
                if(not is_novel) ra->set_applied(true);
            }
            size_t layer = 0;
            while(not is_goal(rs.get())){
                /// 2. apply all applicable relaxed actions that add some new fact
                std::vector<RelaxedAction*> applicable_act;
                for (const auto& a : _relaxed_actions) {
                    if(a->get_applied()) continue;
                    if(a->is_applicable(rs.get())) {
                        applicable_act.push_back( a.get() );
                    }
                }
                for( const auto& ra : applicable_act ) {
                    // Update relations parent->child and child<-parent
                    update_graph_from_relaxed_action(ra);
                    // Add relaxed action to action layer
                    if(_action_layer.size() <= layer) _action_layer.resize(layer+1);
                    _action_layer[layer].emplace_back(ra);
                    // Add new facts from the relaxed action effects to fact layer
                    if(_fact_layer.size() <= layer+1) _fact_layer.resize(layer+2);
                    for(const auto& eff : ra->get_effect_facts()){
                        if(not rs->has_fact(eff))
                            _fact_layer[layer+1].insert(get_fact_id(eff));
                    }
                    // Apply relaxed action to the state
                    ra->apply( rs.get() );
                }

                /// 3. stop when there are no more applicable actions (fix point)
                if(applicable_act.empty()) break;
                layer++;
            }

            _unsolvable = ( not is_goal(rs.get()) );
        }

        bool is_goal(RelaxedState *rs ){
            /// Returns whether the goal condition holds in the RelaxedState rs
            for( const auto& goal : _ins->get_goal_condition() ){
                auto sv = dynamic_cast<variables::StateVariable*>(goal->get_lhs());
                assert(sv != nullptr);
                auto cv = dynamic_cast<variables::ConstantValue*>(goal->get_rhs());
                assert(cv != nullptr);
                auto new_sv = sv->copy();
                new_sv->set_value(cv->get_value());
                if(not rs->has_fact(new_sv.get())) return false;
            }
            return true;
        }

        [[nodiscard]] bool is_unsolvable() const{
            return _unsolvable;
        }

        [[nodiscard]] value_t get_num_layers() const{
            return (value_t)_action_layer.size();
        }

        [[nodiscard]] std::string to_string() const{
            /// Print graph data by layers
            std::string output = "[RELAXED-GRAPH]:";
            for(size_t layer = 0; layer < _action_layer.size(); layer++ ){
                output += "\nfacts_" + std::to_string(layer) + "={";
                for(const auto& f_id : _fact_layer[layer]){
                    output += (f_id != *_fact_layer[layer].begin()?",":"") + _fact_id_to_name[f_id];
                }
                output += "}";
                output += "\nactions_" + std::to_string(layer) + "={";
                for(const auto& ra : _action_layer[layer]){
                    output += (ra != *_action_layer[layer].begin()?",":"") + ra->get_signature();
                }
                output += "}";
            }

            // Fact layer should have one layer more than actions layer
            output += "\nfacts_" + std::to_string(_action_layer.size()) + "={";
            for(const auto& f_id : _fact_layer[_action_layer.size()]){
                output += (f_id != *_fact_layer[_action_layer.size()].begin()?",":"") + _fact_id_to_name[f_id];
            }
            output += "}";

            return output;
        }

    private:
        /// Core data domain and instance
        Domain* _dom;
        Instance* _ins;

        /// RelaxedActions computed from the domain
        std::vector<std::unique_ptr<RelaxedAction>> _relaxed_actions;

        /// Fact data
        std::map<std::string,id_type> _fact_name_to_id;
        std::vector<std::string> _fact_id_to_name;

        /// Bidirectional edges in the planning graph
        std::vector<std::vector<std::pair<id_type,RelaxedAction*>>> _parent_facts; // disjunctive parents
        std::vector<std::vector<std::pair<id_type,RelaxedAction*>>> _child_facts; // disjunctive childs
        std::vector<std::set<id_type>> _fact_layer;
        std::vector<std::vector<RelaxedAction*>> _action_layer;

        /// Relevant outcome about unsolvability after running the algorithm
        bool _unsolvable;
    };
}

#endif //__RELAXATIONS_RELAXED_PLANNING_GRAPH_H__
