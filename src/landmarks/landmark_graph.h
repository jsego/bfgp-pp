//
// Created by js on 6/09/22.
//

#ifndef __LANDMARKS_LANDMARK_GRAPH_H__
#define __LANDMARKS_LANDMARK_GRAPH_H__

#include "../instance.h"
#include "../domain.h"
#include "../relaxations/relaxed_action.h"
#include "../relaxations/relaxed_planning_graph.h"
#include "landmark.h"

namespace landmarks{

class LandmarkGraph{
public:
    /// Class types definitions
    typedef std::map<id_type,set_id_t> ordering_t;

    LandmarkGraph(Domain* dom, Instance* ins) : _dom(dom), _ins(ins){
        /// Create the relaxed graph
        _rpg = std::make_unique<relaxation::RelaxedPlanningGraph>(dom, ins);

        /// Precompute initial state
        auto rs = std::make_unique<relaxation::RelaxedState>( ins->get_initial_state() );
        _rpg->build_relaxed_graph(ins->get_initial_state());
        assert( not _rpg->is_unsolvable() );

        /// Precompute goal conditions
        for( const auto& c : ins->get_goal_condition() ){
            auto sv = dynamic_cast<variables::StateVariable*>(c->get_lhs());
            assert(sv != nullptr);
            auto cv = dynamic_cast<variables::ConstantValue*>(c->get_rhs());
            assert(cv != nullptr);
            sv->set_value(cv->get_value());
            auto fact_id = _rpg->get_fact_id(sv);
            _goal.emplace_back(fact_id);
            _is_goal[fact_id] = true;
        }

        /// Discover landmarks and orders if the task is not unsolvable
        _available_id = (id_type)0;
        identify_landmarks();

        // make copies of each ordering

        /// After identifying landmarks, get the list of initial landmark ids
        for( const auto& l : _landmarks ){
            if(not l->is_active()) continue;
            if( l->get_num_of_facts() > 1 ) continue;
            auto fact_id = *((l->get_fact_ids()).begin());
            auto lm_id = l->get_landmark_id();
            if( _is_init[fact_id] )
                _init_landmark_ids.emplace_back(lm_id);
        }

        /// For efficiency reasons add the inverse of greedy/natural necessary landmarks orderings
        for( const auto & l : _landmarks ){
            if(not l->is_active()) continue;
            auto it = _greedy_necessary_ordering.find( l->get_landmark_id() );
            if( it != _greedy_necessary_ordering.end() ) {
                for (auto m : it->second){
                    _inverse_gn_ordering[ m ].insert( it->first );
                }
            }
            if( NATURAL_ORDERING ) {
                it = _natural_ordering.find(l->get_landmark_id());
                if (it != _natural_ordering.end()) {
                    for (auto m: it->second) {
                        _inverse_nat_ordering[m].insert(it->first);
                    }
                }
            }
        }

        /// Add extra pointer landmarks
        if( POINTER_LANDMARKS ) {
            postprocessing_pointer_landmarks();
        }

        /// Resume all active landmarks ids
        for(const auto& l : _landmarks){
            if(l->is_active()) _active_landmark_ids.emplace_back(l->get_landmark_id());
        }
    }

    ~LandmarkGraph() = default;

    [[nodiscard]] bool is_goal(relaxation::RelaxedState *rs ) const{
        for( auto fact_id : _goal ){
            auto fact = _rpg->get_fact(fact_id );
            if( not rs->has_fact( fact.first.first, fact.first.second, fact.second ) )
                return false;
        }
        return true;
    }

    [[nodiscard]] bool is_deadend(relaxation::RelaxedState *rs) const{
        int num_facts;
        do{
            num_facts = rs->get_num_facts();
            for( const auto& ra : _rpg->get_relaxed_actions() ){
                if( ra->is_applicable(rs) )
                    ra->apply(rs);
            }
        }while( num_facts < rs->get_num_facts() );

        return (not is_goal(rs));
    }

    [[nodiscard]] bool is_goal_fact(id_type fact_id ) const{
        return _is_goal[ fact_id ];
    }

    [[nodiscard]] std::pair<std::pair<id_type ,vec_id_t >, value_t > get_fact(id_type fact_id ) const{
        return _rpg->get_fact(fact_id);
    }

    std::pair<id_type, bool> compute_landmark(set_id_t &fact_ids ){
        auto f2l_it = _fact_ids_to_landmark_id.find(fact_ids);
        if (f2l_it != _fact_ids_to_landmark_id.end())
            return std::make_pair(f2l_it->second, false); // return the existing landmark id
        /// Add possible new landmark
        auto current_id = _available_id++;
        _landmarks.emplace_back(std::make_unique<Landmark>(current_id));
        _landmarks[current_id]->set_facts(fact_ids);
        return std::make_pair(current_id, true);
    }

    static void remove_ordering(id_type landmark_id, ordering_t &ordering ){
        auto it_nat = ordering.find( landmark_id );
        if( it_nat != ordering.end() )
            ordering.erase(it_nat);
        for( auto it : ordering ){
            auto it_nat2 = (it.second).find( landmark_id );
            if( it_nat2 != (it.second).end() )
                (it.second).erase( it_nat2 );
        }
    }

    // Combine conjunctive facts to disjunctive ones
    void combine_facts(const std::vector< set_id_t > &conjunctive_facts, size_t pos,
                       vec_id_t &current_comb, std::set< set_id_t > &res ){
        if( pos >= conjunctive_facts.size() ){
            set_id_t s_comb(current_comb.begin(), current_comb.end() );
            res.insert( s_comb );
            return;
        }
        assert( current_comb.size() == conjunctive_facts.size() );
        for( auto f_id : conjunctive_facts[pos] ){
            current_comb[pos] = f_id;
            combine_facts(conjunctive_facts, pos+1, current_comb, res);
        }
    }

    void add_landmark_and_ordering(const std::pair<id_type, bool> &pre_id_and_new,
                                   const std::string &ordering_type,
                                   id_type post_id ){
        /// Add "pre" landmark, and ordering pre =>_X post_id where X is the ordering type
        auto pre_id = pre_id_and_new.first;
        auto pre_is_new = pre_id_and_new.second;
        auto pre_fact_ids = _landmarks[pre_id]->get_fact_ids();

        // 1. Facts are preferred over disjunctions (pre landmark is a fact)
        if( pre_fact_ids.size() == 1u ){
            auto fact_id = *(pre_fact_ids.begin());
            // Deactivate landmarks that contain pre in the disjunction
            for(const auto& l : _landmarks){
                if(not l->is_active()) continue;
                if(l->get_num_of_facts() == 1) continue;
                if(not l->has_fact(fact_id)) continue;
                auto l_id = l->get_landmark_id();
                if(l_id == pre_id and pre_is_new) continue;
                // Remove obsolete orderings
                if( NATURAL_ORDERING ) {
                    remove_ordering(l_id, _natural_ordering);
                }
                remove_ordering( l_id, _greedy_necessary_ordering );
                auto f2l_it = _fact_ids_to_landmark_id.find(l->get_fact_ids());
                assert(f2l_it != _fact_ids_to_landmark_id.end());
                _fact_ids_to_landmark_id.erase(f2l_it);
                l->deactivate(); // similar to removing the landmark, but keeping it in memory
            }
        }

        // 2. Abort on overlap with existing landmark
        bool new_landmark = true;
        for( const auto & l : _landmarks ){
            if(not l->is_active()) continue;
            if(l->get_landmark_id() == pre_id and pre_is_new) continue;
            auto fact_ids = l->get_fact_ids();
            // 2.a If l is the same landmark as "pre" continue
            if( fact_ids == pre_fact_ids ) {
                new_landmark = false;
                continue;
            }
            // 2.b abort if intersection with the current l is found
            for( auto ipre = pre_fact_ids.begin(), il = fact_ids.begin();
                 ipre != pre_fact_ids.end() and il != fact_ids.end(); ){
                if( *ipre == *il ) {// abort (intersection found)
                    _landmarks[pre_id]->deactivate();
                    return;
                }
                if( *ipre < *il ) ipre++;
                else il++;
            }
        }

        // 3. Add the new landmark to the graph
        if(new_landmark){
            _fact_ids_to_landmark_id[ _landmarks[pre_id]->get_fact_ids() ] = pre_id;
            _queue_landmarks_ids.push(pre_id);
        }

        // 4. Add the new ordering to the graph
        if( ordering_type == "nat" ){ // Natural ordering
            _natural_ordering[pre_id].insert(post_id);
        }
        else if( ordering_type == "gn" ){ // Greedy necessary ordering
            _greedy_necessary_ordering[pre_id].insert(post_id);
        }
    }

    void identify_landmarks(){
        // 0. [lines 12-13] landmark graph starts with all goals, no orderings
        for( auto goal_fact_id : _goal ){
            auto current_id = _available_id++;
            _landmarks.emplace_back(std::make_unique<Landmark>(current_id));
            _landmarks[current_id]->add_fact(goal_fact_id);
            _queue_landmarks_ids.push( current_id );
            _goal_landmark_ids.emplace_back( current_id );
            _fact_ids_to_landmark_id[ _landmarks[current_id]->get_fact_ids() ] = current_id;
            // ToDo: update to log info
            std::cout << "[INFO] New goal landmark: " << _landmarks[current_id]->to_string(sd, _rpg.get()) << "\n";
        }

        // further_orderings (not included yet)
        while( !_queue_landmarks_ids.empty() ){
            auto lm_id = _queue_landmarks_ids.front();
            _queue_landmarks_ids.pop();
            auto fact_ids = _landmarks[lm_id]->get_fact_ids();
            // ToDo: update to log info
            std::cout << "[INFO] Current landmark: " << _landmarks[lm_id]->to_string(sd, _rpg.get()) << "\n";

            // 1. [line 17] If any fact f_id is in the initial state, then the (disjunctive) landmark is true in init
            bool is_init = false;
            for( auto f_id : fact_ids ){
                if(_init_set_fact_ids.find(f_id ) != _init_set_fact_ids.end() ){
                    is_init = true; break;
                }
            }
            if( is_init ) continue;
            // ToDo: update to log info
            std::cout << "[INFO] current landmarks are not in the initial state " << "\n";

            // 2. [line 18] Build the restricted relax planning graph (RRPG)
            // Split relaxed actions between the ones that add the current landmark (possible achievers)
            // and the ones that do not (available actions)
            auto relaxed_actions = _rpg->get_relaxed_actions();
            vec_id_t available_relaxed_action_ids;
            vec_id_t possible_achievers_ids;
            id_type ra_id{0};
            for( const auto& ra : relaxed_actions ){
                for( auto f_id : fact_ids ) {
                    auto fact = _rpg->get_fact(f_id);
                    if (ra->adds_fact(fact.first.first, fact.first.second, fact.second ) ) {
                        possible_achievers_ids.emplace_back(ra_id);
                    }
                    else available_relaxed_action_ids.emplace_back(ra_id);
                }
                ra_id++;
            }
            // ToDo: update to log info
            std::cout << "[INFO] relaxed actions computed\n";
            // Initialize relaxed state to initial state
            auto rs = std::make_unique<relaxation::RelaxedState>(sd);
            for( auto f_id : _init_set_fact_ids ) {
                auto fact = _rpg->get_fact(f_id);
                rs->add_fact(fact.first.first, fact.first.second, fact.second);
            }
            // Apply all available actions while applicable and find the first possible achievers
            vec_id_t first_possible_achievers_ids;
            auto num_of_facts = rs->get_num_facts();
            bool first_achievers_found = false;
            do{
                num_of_facts = rs->get_num_facts();
                if( not first_achievers_found ) {
                    // Check if the possible achievers can be applied in the current relaxed state
                    for (auto pa_id: possible_achievers_ids) {
                        if (relaxed_actions[pa_id]->is_applicable(rs.get())) {
                            first_possible_achievers_ids.emplace_back(pa_id);
                        }
                    }
                    first_achievers_found = (!first_possible_achievers_ids.empty());
                }
                // (Commented) Break when first achievers are found
                // if( first_possible_achievers_ids.size() > 0u ) break;
                // Otherwise continue applying available actions until fix point is reached
                vec_id_t applicable_relaxed_actions_ids;
                for( auto ara_id : available_relaxed_action_ids ){
                    if( relaxed_actions[ara_id]->is_applicable(rs.get()) ){
                        applicable_relaxed_actions_ids.emplace_back(ara_id);
                    }
                }
                for( auto ara_id : applicable_relaxed_actions_ids )
                    relaxed_actions[ara_id]->apply(rs.get());
            }while( num_of_facts < rs->get_num_facts() ); // fixpoint

            // 3. [lines 19-21] Shared preconditions (from first achievers) for current landmark
            // for each one add a greedy necessary ordering pre => current
            assert( !first_possible_achievers_ids.empty() );

            _first_possible_achievers[lm_id] = first_possible_achievers_ids;

            set_id_t shared_preconditions_ids;
            std::vector< set_id_t > prec_fact_ids(first_possible_achievers_ids.size() );
            auto pre_shared = relaxed_actions[first_possible_achievers_ids[0]]->get_precondition_facts();
            for( int pred_idx = 0; pred_idx < (int)pre_shared.size(); pred_idx++ ){
                for( const auto& m : pre_shared[ pred_idx ] ){
                    auto fact_id = _rpg->get_fact_id(pred_idx, m.first, m.second );
                    shared_preconditions_ids.insert(fact_id );
                    prec_fact_ids[ 0 ].insert( fact_id );
                }
            }

            for(int pos = 0; pos < (int)first_possible_achievers_ids.size(); pos++ ){
                pre_shared = relaxed_actions[first_possible_achievers_ids[pos]]->get_precondition_facts();
                set_id_t current_preconditions_ids;
                for( int pred_idx = 0; pred_idx < (int)pre_shared.size(); pred_idx++ ){
                    for( const auto& m : pre_shared[ pred_idx ] ){
                        auto fact_id = _rpg->get_fact_id(pred_idx, m.first, m.second );
                        prec_fact_ids[pos].insert( fact_id );
                        if(shared_preconditions_ids.find(fact_id ) != shared_preconditions_ids.end() )
                            current_preconditions_ids.insert(fact_id );
                    }
                }
                // Update the set of shared preconditions
                swap(shared_preconditions_ids, current_preconditions_ids );
            }

            // Add landmark and ordering
            for( auto sp_id : shared_preconditions_ids ){
                // Retrieve the landmark if already exists, otherwise create a new one
                set_id_t aux_fact_id = {sp_id};
                auto shared_prec_landmark_id = compute_landmark(aux_fact_id);
                // ToDo: update to log info
                std::cout << "[INFO] Shared precondition landmark: " << _landmarks[shared_prec_landmark_id.first]->to_string(sd, _rpg.get() ) << "\n";
                add_landmark_and_ordering(shared_prec_landmark_id, "gn", lm_id );
                // ToDo: update to log info
                std::cout << "[INFO] landmark and greedy necessary ordering added\n";
            }

            // 4. [lines 22-25] Disjunctive fact to cover all shared preconditions
            // (optional) combine only one fact of each achiever of the same predicate symbol
            // (optional) in the LAMA paper, disjunctions up to size 4
            // Filter the uncovered facts
            std::vector<set_id_t > pre_disj_ids;
            for( const auto& pfact_ids : prec_fact_ids ){
                set_id_t uncovered_facts;
                for( auto f_id : pfact_ids ){
                    if(shared_preconditions_ids.find(f_id ) == shared_preconditions_ids.end() ){
                        uncovered_facts.insert( f_id );
                    }
                }
                if( !uncovered_facts.empty() )
                    pre_disj_ids.emplace_back(uncovered_facts );
            }

            if( !pre_disj_ids.empty() ) {
                vec_id_t current_comb(pre_disj_ids.size());
                std::set<set_id_t > disjunctive_facts;
                combine_facts(pre_disj_ids, 0, current_comb, disjunctive_facts);

                for (auto disjunction : disjunctive_facts) {
                    bool entailed_by_initial_state = false;
                    for (auto f_id : disjunction) {
                        if (_is_init[f_id]) {
                            entailed_by_initial_state = true;
                            break;
                        }
                    }
                    if (entailed_by_initial_state) continue;

                    // If the disjunction is not entailed by the initial state
                    // add it as a disjunctive landmark
                    auto disjunctive_landmark_id = compute_landmark(disjunction);
                    add_landmark_and_ordering(disjunctive_landmark_id, "gn", lm_id);
                }
            }

            // 5. [lines 26-29] (optional) extract landmarks from DTG

            // 6. [line 30] (optional) add potential natural orderings from current landmark to unachieved ones
            // add a natural ordering from current landmark => l\in L s.t. l is not entailed by rs
            vec_id_t potential_nat_orderings;
            for( const auto& l : _landmarks ){
                if(not l->is_active()) continue;
                auto l_id = l->get_landmark_id();
                if( l_id == lm_id ) continue;
                auto it = _greedy_necessary_ordering[lm_id].find( l_id );
                if( it != _greedy_necessary_ordering[lm_id].end() ) continue;
                if( not l->holds(_rpg.get(), rs.get()) ){
                    potential_nat_orderings.emplace_back( l_id );
                }
            }
            // Make one iteration in the relaxed state for all relaxed actions
            vec_id_t ra_ids_applicable;
            // - first get the applicable relaxed actions
            for( auto fpa_ra_id : first_possible_achievers_ids ){
                if( relaxed_actions[fpa_ra_id]->is_applicable(rs.get() ) )
                    ra_ids_applicable.emplace_back(fpa_ra_id );
            }
            // - second apply the previous set
            for( auto fpa_ra_id_applicable : ra_ids_applicable ) {
                relaxed_actions[fpa_ra_id_applicable]->apply(rs.get());
            }

            // Check all potential nat ordering, if they do not hold then add them as a nat ordering
            for( auto l_id : potential_nat_orderings ){
                if( not _landmarks[l_id]->holds(_rpg.get(), rs.get() ) ) {
                    add_landmark_and_ordering(std::make_pair(lm_id, false), "nat", l_id);
                }
            }
        }

    }

    [[nodiscard]] vec_id_t get_initial_landmarks_ids() const{
        return _init_landmark_ids;
    }

    [[nodiscard]] vec_id_t get_goal_landmarks_ids() const{
        return _goal_landmark_ids;
    }

    [[nodiscard]] vec_id_t get_active_landmarks_ids() const{
        /// Return all active landmark ids
        return _active_landmark_ids;
    }

    [[nodiscard]] int get_num_landmarks() const{
        return (int)_landmarks.size();
    }

    [[nodiscard]] Landmark* get_landmark(id_type landmark_id ) const{
        assert( landmark_id < (id_type)_landmarks.size() );
        return _landmarks[ landmark_id ].get();
    }

    [[nodiscard]] relaxation::RelaxedPlanningGraph* get_relaxed_planning_graph() const{
        return _rpg.get();
    }

    [[nodiscard]] set_id_t get_greedy_necessary_landmark_ordering(id_type landmark_id ) const{
        auto it = _greedy_necessary_ordering.find( landmark_id );
        if( it == _greedy_necessary_ordering.end() )
            return {};
        return it->second;
    }

    [[nodiscard]] set_id_t get_inverse_greedy_necessary_landmark_ordering(id_type landmark_id ) const{
        auto it = _inverse_gn_ordering.find( landmark_id );
        if( it == _inverse_gn_ordering.end() )
            return {};
        return it->second;
    }

    [[nodiscard]] set_id_t get_inverse_natural_landmark_ordering(id_type landmark_id ) const{
        auto it = _inverse_nat_ordering.find( landmark_id );
        if( it == _inverse_nat_ordering.end() )
            return {};
        return it->second;
    }

    void postprocessing_pointer_landmarks(){
        //auto sd = _dom->getStateDescriptor();
        vec_id_t aux_landmark_ids;
        std::set< std::pair<id_type,id_type> > aux_gn_orderings;
        auto relaxed_actions = _rpg->get_relaxed_actions();

        //for( const auto& lm : _landmarks ){
        for(id_type lm_id = 0; lm_id < (id_type)_landmarks.size(); lm_id++){
            assert(lm_id == _landmarks[lm_id]->get_landmark_id());
            if(not _landmarks[lm_id]->is_active()) continue;
//cout << "[INFO] Checking landmark:" << lm->to_string(_dom->get_state_descriptor(),_rpg);
            auto fact_ids = _landmarks[lm_id]->get_fact_ids();
            if( fact_ids.size() == 1u and _is_init[*fact_ids.begin()] )  continue;

            auto fpa = _first_possible_achievers[ lm_id ];
            int current_size = 1;
            bool all_zeros = false;
            auto current_id = _available_id++;
            _landmarks.emplace_back(std::make_unique<Landmark>(current_id));

            for(id_type fpa_idx = 0; fpa_idx < (id_type)fpa.size(); fpa_idx++  ){
//cout << fpa[ fpa_idx ]->to_string(_dom->getStateDescriptor()) << endl;
                auto param_types = relaxed_actions[fpa[fpa_idx]]->get_param_types();
                auto obj_ids = relaxed_actions[fpa[fpa_idx]]->get_grounded_params();
                if( obj_ids.empty() ) continue;
                int num_zeros = 0;
                _landmarks[current_id]->set_possible_achievers_size(current_size++);
                for(size_t p_idx = 0; p_idx < param_types.size(); p_idx++ ) {
                    _landmarks[current_id]->add_var_assignment(fpa_idx, param_types[p_idx], obj_ids[p_idx] );
                    if(obj_ids[ p_idx ] == 0 ) num_zeros++;
                }
                if( num_zeros == (int)obj_ids.size() ) all_zeros = true;
            }
            if( current_size == 1 ){ // possible achievers have no parameters
                _landmarks[current_id]->deactivate();
                continue;
            }
            // Save new landmark and orderings
            aux_landmark_ids.emplace_back( current_id );
            aux_gn_orderings.insert(std::make_pair(current_id, lm_id ) );
            for( auto ign : _inverse_gn_ordering[ lm_id ] ){
                aux_gn_orderings.insert(std::make_pair(ign, current_id));
            }
            if( all_zeros ) _init_landmark_ids.emplace_back( current_id );
        }

        // Add the new greedy necessary orderings
        for( auto gn_ord : aux_gn_orderings ){
            _greedy_necessary_ordering[ gn_ord.first ].insert( gn_ord.second );
            _inverse_gn_ordering[ gn_ord.second ].insert( gn_ord.first );
        }
    }

    [[nodiscard]] static std::string orderings_to_string(const std::string &ordering_name,
                                                         id_type landmark_id,
                                                         const ordering_t &orderings) {
        std::string output = ordering_name + ": ";
        auto it_gn = orderings.find( landmark_id );
        //assert( it_gn != _greedy_necessary_ordering.end() );
        output += std::to_string( landmark_id ) + " => {";
        if( it_gn != orderings.end() ) {
            for (auto it = it_gn->second.begin(); it != it_gn->second.end(); it++) {
                output += (it != it_gn->second.begin() ? "," : "") + std::to_string(*it);
            }
        }
        output += "}\n";
        return output;
    }

    [[nodiscard]] std::string to_string() const{
        std::string output = "[LANDMARKS][INSTANCE #" + std::to_string( _ins->get_instance_id() ) + "]:\n";
        auto sd = _dom->get_state_descriptor();
        //output += _rpg->to_string(sd) +"\n"; // Print the relaxed graph too
        for( const auto& lm : _landmarks ){
            if(not lm->is_active()) continue;
            auto landmark_id = lm->get_landmark_id();
            //auto fact_ids = lm->get_fact_ids();
            // Print landmark
            output += lm->to_string(sd, _rpg.get());

            // Print greedy necessary orderings
            output += orderings_to_string("GREEDY-NECESSARY", landmark_id, _greedy_necessary_ordering);
            if( NATURAL_ORDERING ) {
                // Print natural orderings
                output += orderings_to_string("NATURAL", landmark_id, _natural_ordering);
            }
        }
        return output;
    }

private:
    /// Original domain and instance
    Domain* _dom;
    Instance* _ins;
    /// Relaxed graph of the original domain and instance
    std::unique_ptr<relaxation::RelaxedPlanningGraph> _rpg;
    /// Initial fact ids
    vec_id_t _init;
    vec_bool_t _is_init;
    vec_id_t _init_landmark_ids;
    set_id_t _init_set_fact_ids;
    /// Goal fact ids
    vec_id_t _goal;
    vec_bool_t _is_goal;
    vec_id_t _goal_landmark_ids;
    /// Discovered landmarks
    std::vector< std::unique_ptr<Landmark> > _landmarks; // all identified landmarks
    vec_id_t _active_landmark_ids; // all active landmarks ids
    std::map<set_id_t,id_type> _fact_ids_to_landmark_id; // set of fact ids map to landmark id
    std::queue<id_type> _queue_landmarks_ids; // queue of landmarks
    /// Discovered orderings
    ordering_t _natural_ordering; // pre_landmark nat-> post_landmarks
    ordering_t _inverse_nat_ordering; // post_landmark <-nat pre_landmarks
    ordering_t _greedy_necessary_ordering; // pre_landmark gn-> post_landmarks
    ordering_t _inverse_gn_ordering; // post_landmark <-gn pre_landmarks
    std::map<id_type,vec_id_t> _first_possible_achievers; // fact_id <- relaxed actions ids

    id_type _available_id;
};
}
#endif //__LANDMARKS_LANDMARK_GRAPH_H__