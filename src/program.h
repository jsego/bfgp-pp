#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "utils/common.h"
#include "program_state.h"
#include "instructions/instruction.h"
#include "instructions/end.h"
#include "instructions/end_for.h"
#include "instructions/planning_action.h"
#include "instructions/ram/goto.h"
#include "instructions/ram/register_test.h"
#include "instructions/ram/register_assign.h"

#include "generalized_planning_problem.h"
#include "action.h"
//#include "program_translator.h"
//#include "landmarks/landmark_graph.h"

class Program{
public:
    explicit Program(GeneralizedPlanningProblem *gpp){
	//explicit Program( int program_lines = 1){//,std::shared_ptr<instructions::Instruction> end_instruction = nullptr){
        auto program_lines = gpp->get_generalized_domain()->get_program_lines();
        assert( program_lines >= 1 );
		_instructions.resize( program_lines, nullptr );
        //set_instruction(program_lines - 1, end_instruction);  // Just a simple improvement
        reset_performance_variables();
	}

	explicit Program( Program *p ){
        /// Copy instructions data
        auto vi = p->get_instructions();
		_instructions.resize( vi.size() );
		for( size_t i = 0; i < _instructions.size(); i++ )
			_instructions[ i ] = vi[ i ];
        /// Copy empirical performance data
        reset_performance_variables();
        /// Copy landmarks data
        //_landmark_count = p->get_landmark_count();
        //_unachieved_landmarks = p->get_unachieved_landmark_ids();
	}
	
	~Program()= default;
	
	std::unique_ptr<Program> copy(){
        return std::make_unique<Program>(this);
	}

    void reset_performance_variables(){
        _num_of_steps = 0;
        _total_plan_costs = 0;
        _num_of_math_planning_actions = 0;
        _num_of_mem_planning_actions = 0;
        _failed_instance_idx = -1;
    }

    [[nodiscard]] std::vector<instructions::Instruction*> get_instructions() const{
		return _instructions;
	}
	
	void set_instruction(size_t program_line, instructions::Instruction* ins){
        /// Assign instruction ins to the corresponding program_line
	    assert( program_line <_instructions.size() );
		_instructions[program_line] = ins;
	}
	
	[[nodiscard]] instructions::Instruction* get_instruction(size_t program_line ) const{
	    assert(program_line < _instructions.size());
		return _instructions[ program_line ];
	}
	
	[[nodiscard]] size_t get_num_instructions() const{
		return _instructions.size();
	}
	
	[[nodiscard]] bool is_halting_condition(ProgramState* ps, int &error ) const{
		auto line = ps->get_line();
		// EMPTY line is a halting condition (no transition defined)
        if( _instructions[line] == nullptr ) return true;
        // Either True or False evaluation of End instructions is a halting condition
        return nullptr != dynamic_cast<instructions::End*>(_instructions[line]);
    }
	
	bool is_goal(ProgramState* ps, Instance* ins, int &error ) const{
		auto line = ps->get_line();
        auto end = dynamic_cast<instructions::End*>( _instructions[line] );
        if( end == nullptr ) return false;
        bool is_goal = end->is_applicable(ins, ps);
        if(not is_goal) error = ERROR_INCORRECT_PROGRAM; // ERROR 1: Incorrect program
        return is_goal; // It is an end instruction and reaches all goal states
    }

    /*[[nodiscard]] static bool is_conditional(const std::string& ins_name) {
        return (ins_name.substr(0,3) == "cmp" or ins_name.substr(0,4) == "test");
    }*/

    // ToDo: evaluation function dependant - maybe some program specialization would work
    /*bool check_deadend(ProgramState *ps,
                       landmarks::LandmarkGraph *lm,
                       int &error ) const{
        auto rs = std::make_unique<relaxation::RelaxedState>( sd );
        auto reg = ps->get_state()->get_typed_registers();
        for(id_type pred_idx = 0; pred_idx < (id_type)reg.size(); pred_idx++ ) {
            for( const auto& m : reg[ pred_idx ] )
                rs->add_fact(pred_idx, m.first, m.second );
        }
        bool is_deadend = lm->is_deadend( rs.get() );
        if( is_deadend ) error = ERROR_DEADEND; // ERROR 14: the relaxed state is a deadend
        return is_deadend;
    }*/

    // ToDo: CPP theory dependant - update from a settings class
    [[nodiscard]] bool is_terminating(ProgramState* ps, std::set<std::string > &visited) const{
        /// Returns whether the current program is terminating based on repeated states in backward loops
        auto line = ps->get_line();
        // cpp theory
        auto ef = dynamic_cast<instructions::EndFor*>( _instructions[ line ] );
        // assembler theory
        auto g = dynamic_cast<instructions::Goto*>(_instructions[line]);
        if( ef or (g and g->get_destination_line()<line)){
            auto ps_str = ps->to_string();
            // Infinite loop detected
            if(visited.find(ps_str) != visited.end() )
                return false; // Infinite loop detected
            visited.insert(ps_str);
        }
        return true;
    }

    static void update_pointer(Instance *ins, variables::Pointer* ptr, size_t idx){
        auto objs = ins->get_typed_objects(ptr->get_type()->get_name());
        assert(idx < objs.size());
        ptr->set_value(idx);
        ptr->set_object(objs[idx]);
    }

    static void update_flags(ProgramState *ps, value_t res){
        for(const auto& f : ps->get_flags()){
            f->set_value(res);
        }
    }

    static std::unique_ptr<ProgramState> make_program_state(GeneralizedDomain *gd, State *s){
        auto ps = std::make_unique<ProgramState>(s->copy());
        for( auto f : gd->get_flags())
            ps->add_flag(f);
        for(auto ptr : gd->get_pointers()) {
            ps->add_pointer(ptr);
        }
        return ps;
    }

    static std::vector<bool> reset_program_state(ProgramState *ps, Instance *ins){
        /// Apply the default behavior (all pointers to 0, and state to init)
        /// and returns the pointers assigned to specific objects when "action_X" is defined in INIT
        ps->set_state(ins->get_initial_state()->copy()); // set the planning state to s
        for(const auto& ptr : ps->get_pointers()) {
            update_pointer(ins, ptr, 0u);
        }

        // ToDo: program specialization for ActionSchemas (override the reset_program_state)
        /// If the theory is ActionSchemas, reset pointers to the corresponding action_* objects,
        /// in this case there must be only one action.
        auto ptrs = ps->get_pointers();
        std::vector<bool> ptr_assigned(ptrs.size(), false);
        for(const auto& fact : ins->get_initial_state()->get_facts()){
            auto act_name = fact->get_function()->get_name();
            if(act_name.size() > 7u and act_name.substr(0,7)=="action_"){
                auto objs = fact->get_objects();
                for(const auto& o : objs){
                    // Set for the current Object* o, its type obj_t and index obj_idx
                    auto obj_t = o->get_type();
                    auto all_objs_t = ins->get_typed_objects(obj_t->get_name());
                    size_t obj_idx = 0u;
                    // ToDo: implement a better lookup function for obj_idx
                    for(obj_idx=0u; obj_idx < all_objs_t.size(); ++obj_idx){
                        if(all_objs_t[obj_idx] == o) break;
                    }
                    assert(obj_idx < all_objs_t.size());

                    // Assign the object to a free pointer of its type
                    for(size_t ptr_idx{0}; ptr_idx < ptrs.size(); ++ptr_idx){
                        if(ptr_assigned[ptr_idx]) continue;
                        if(obj_t == ptrs[ptr_idx]->get_type()){
                            ptr_assigned[ptr_idx] = true;
                            update_pointer(ins, ptrs[ptr_idx], obj_idx);
                            break;
                        }
                    }
                }
                return ptr_assigned;
            }
        }
        return ptr_assigned;
    }

    std::vector< std::unique_ptr<ProgramState> > run(GeneralizedPlanningProblem *gpp,
                                                     bool save_pddl_plans = false){
        reset_performance_variables();
        if(save_pddl_plans){
            _pddl_plans.clear();
            _pddl_plans.resize(gpp->get_num_instances()+1);
        }

        auto actions_theory = gpp->is_actions_theory();
        auto infinite_detection = gpp->get_infinite_detection();
        //auto use_landmarks = gpp->get_use_landmarks();// ToDo: evaluation function dependant - maybe some program specialization would work
		//auto num_instances = gpp->get_num_instances();
        auto active_instance_idxs = gpp->get_active_instance_idxs();
		auto funcs = gpp->get_generalized_domain()->get_domain()->get_functions();

		// One program state per instance
        std::vector< std::unique_ptr<ProgramState> > pss;
        auto gd = gpp->get_generalized_domain();
        for(const auto& idx : active_instance_idxs){
            pss.emplace_back(make_program_state(gd, gpp->get_instance(idx)->get_initial_state()));
        }

         int errors = 0;
        /*if(use_landmarks){ // ToDo: evaluation function dependant - maybe some program specialization would work
            // Initialized class variables
            _landmark_count = 0;
            _unachieved_landmarks.resize(num_instances, 0);
        }*/

        id_type active_instance_local_idx = 0;
        for(const auto& idx : active_instance_idxs){
            //if( gpp->is_progressive() and (not gpp->is_instance_active(id))) continue; // not required
            //std::cout << "******** INSTANCE #" << (id+1) << " ********\n";
			// Initialize local initial state
			auto ins = gpp->get_instance(idx);
            auto ps = pss[active_instance_local_idx++].get(); // default ProgramState values
            reset_program_state(ps, ins);
            auto line = ps->get_line();

            /// Copy the pre_state in actions_theory
            [[maybe_unused]] auto pre_ps = (actions_theory ? ps->copy() : nullptr);

            // ToDo: evaluation function dependant - maybe some program specialization would work
            /*// Process the landmarks of the initial state
            [[maybe_unused]] set_id_t set_accepted_landmarks_ids;
            [[maybe_unused]] set_id_t set_landmarks_ids;
            [[maybe_unused]] landmarks::LandmarkGraph *lg = nullptr;
            [[maybe_unused]] relaxation::RelaxedPlanningGraph *rpg = nullptr;
            [[maybe_unused]] vec_id_t goal_landmarks_ids;

            if( use_landmarks ) { // ToDo: evaluation function dependant - maybe some program specialization would work
                // Get the landmark graph and the relaxed planning graph of the same planning instance
                lg = gpp->get_landmark_graph(id);
                rpg = lg->get_relaxed_planning_graph();
                // Get the full set of active landmarks
                auto landmark_ids = lg->get_active_landmarks_ids();
                set_landmarks_ids = set_id_t(landmark_ids.begin(), landmark_ids.end());
                // Initial landmarks are accepted by definition
                auto initial_landmark_ids = lg->get_initial_landmarks_ids();
                set_accepted_landmarks_ids = set_id_t(initial_landmark_ids.begin(), initial_landmark_ids.end());
                // Get goal landmarks
                goal_landmarks_ids = lg->get_goal_landmarks_ids();
            }*/

			// For detecting infinite loops (ToDo: it can be enhanced with a hash or bigint identifier)
            //std::set< std::unique_ptr<ProgramState>, ProgramStateComparer > visited;
            std::set< std::string > visited; // saving program states as strings
			int error = 0;

			while( not is_halting_condition(ps, error) ){
                // Checking infinite loop (only for backward loops)
                if( infinite_detection and not is_terminating(ps, visited) ){
                    error = ERROR_INFINITE_PROGRAM; // ERROR 3: Infinite program
                    break;
                }

                // Retrieving program line and action type
                line = ps->get_line();
                auto ins_type = _instructions[line]->get_type();
                if( ins_type == ActionType::Math ) _num_of_math_planning_actions++;
                else if(ins_type == ActionType::Memory ) {
                    _num_of_mem_planning_actions++;
                    // Memory planning actions are saved in PDDL plans
                    auto act = dynamic_cast<instructions::PlanningAction*>(_instructions[line]);
                    if(act and act->is_applicable(ins, ps)) {
                        _total_plan_costs++;
                        if (save_pddl_plans) {
                            _pddl_plans[ins->get_instance_id()].emplace_back(act->get_action()->to_pddl_grounded());
                        }
                    }
                }

				// Applying current instruction
                //std::cout << _instructions[line]->to_string(false) << "\n";
                //std::cout << "Is applicable? " << _instructions[line]->is_applicable(ins, ps) << "\n";
                value_t res{0u};
                auto ins_reg_test = dynamic_cast<instructions::RegisterTest*>(_instructions[line]);
                auto ins_reg_assign = dynamic_cast<instructions::RegisterAssign*>(_instructions[line]);
                if(actions_theory and ins_reg_test){
                    pre_ps->set_line(ps->get_line());
                    res = ins_reg_test->apply(ins, pre_ps.get());
                    ps->set_line(pre_ps->get_line());

                }
                else if(actions_theory and ins_reg_assign){
                    res = ins_reg_assign->apply_from_pre(ins, ps, pre_ps.get());
                }
                else{
                    res = _instructions[ line ]->apply(ins, ps);
                }

				_num_of_steps++;

                // Mathematical planning actions update zero and carry flags
                if(ins_type == ActionType::Math ) update_flags(ps, res);

                //std::cout << ps->to_string() << "\n\n";

                // ToDo: evaluation function dependant - maybe some program specialization would work
                /*if(use_landmarks){
                    for(const bool& ppl : {false, true}) {
                        process_reached_landmarks(sd.get(), rpg, ps->get_state(), lg, set_landmarks_ids,
                                                  set_accepted_landmarks_ids, ppl);
                    }
                }*/
            }

            // ToDo: evaluation function dependant - maybe some program specialization would work
            /*if(use_landmarks){
                update_landmark_counting(sd.get(), rpg, ps->get_state(), lg, id, set_landmarks_ids,
                                         set_accepted_landmarks_ids, goal_landmarks_ids);
            }*/

            if( error == 0 ) {
                auto goal = is_goal(ps, ins, error);
                if(goal and actions_theory){
                    // Close world assumption: goal is a state, so check that all what is true in the state holds
                    // ToDo: inefficient, do it only once for the goal
                    /*std::set<std::string> goal_fact_names;
                    for(const auto& c : ins->get_goal_condition()) {
                        goal_fact_names.emplace(c->to_string(false));
                    }
                    for(const auto& fact : ps->get_state()->get_facts()){
                        auto f_name = fact->to_string(true);
                        if(f_name.size()>8u and f_name.substr(0,8) == "(action_") continue;
                        if(fact->get_value()>0 and goal_fact_names.find(f_name) == goal_fact_names.end()) {
                            error = ERROR_INCORRECT_PROGRAM;
                            break;
                        }
                    }*/
                    auto goal_state = ins->get_goal_state();
                    for(const auto& fact : ps->get_state()->get_facts()){
                        auto f_name = fact->get_name();
                        if(f_name.size() > 8u and f_name.substr(0,8) == "(action_") continue;
//std::cout << "Checking... " << fact->get_name() <<" f:" << fact->get_value() << " g:" << goal_state->get_value(fact) << std::endl;
                        if(fact->get_value() != goal_state->get_value(fact)){
                            error = ERROR_INCORRECT_PROGRAM;
                            break;
                        }
                    }
                }
                else if(actions_theory){ // Return error if fix state variables (sv_init == sv_goal) are modified
                    auto init_state = ins->get_initial_state();
                    auto goal_state = ins->get_goal_state();
                    for(const auto& fact : ps->get_state()->get_facts()){ // list of modified and unmodified state vars
                        auto f_name = fact->get_name();
                        if(f_name.size() > 8u and f_name.substr(0,8) == "(action_") continue;
//std::cout << "Checking... " << fact->get_name() <<" f:" << fact->get_value() << " g:" << goal_state->get_value(fact) << std::endl;
                        if( fact->get_value() != goal_state->get_value(fact) and
                            fact->get_value() != init_state->get_value(fact)){
                            error = ERROR_INCORRECT_PROGRAM;
                            break;
                        }
                    }

                }
            }
            if( error < 0 ){
                errors++;
                _failed_instance_idx = idx;
                break;
            }
		}

        if( errors ) return {};
		return pss;
	}

    /*
    void process_reached_landmarks(relaxation::RelaxedPlanningGraph *rpg,
                                   State *s,
                                   landmarks::LandmarkGraph *lg,
                                   set_id_t &landmark_ids,
                                   set_id_t &accepted,
                                   bool process_pointer_landmarks = false){
        vec_id_t reached;
        for( auto lm_id : lg->get_active_landmarks_ids() ){
            auto landmark = lg->get_landmark(lm_id);
            auto is_ptr_landmark = landmark->is_pointer_landmark();
            // If "process ptrs" and "isn't one", or "don't process ptrs" and "is one", continue
            if(process_pointer_landmarks != is_ptr_landmark ) continue;
            // If the landmark was already accepted continue;
            if( accepted.find( lm_id ) != accepted.end() ) continue;
            bool landmark_holds;
            if( is_ptr_landmark ) landmark_holds = landmark->holds(sd, s);
            else landmark_holds = landmark->holds(rpg, s);
            // New landmark reached
            if( landmark_holds ){
                bool is_reached = true;
                // check if gn landmarks hold
                auto gn_landmarks_ids = lg->get_inverse_greedy_necessary_landmark_ordering(lm_id);
                for( auto gn_l_id : gn_landmarks_ids ){
                    // check if a gn condition has not been accepted yet
                    if( accepted.find( gn_l_id ) == accepted.end() ){
                        is_reached = false; break;
                    }
                }
                auto nat_landmarks_ids = lg->get_inverse_natural_landmark_ordering(lm_id);
                for( auto nat_l_id : nat_landmarks_ids ){
                    // check if a nat condition has not been accepted yet
                    if( accepted.find( nat_l_id ) == accepted.end() ){
                        is_reached = false; break;
                    }
                }
                // if all gn and nat landmarks have been accepted, include the new landmark as reached
                if( is_reached )
                    reached.emplace_back( lm_id );
            }
        }
        // Union of reached and accepted
        std::copy( reached.begin(), reached.end(), inserter( accepted, accepted.end() ) );
    }


    void update_landmark_counting(relaxation::RelaxedPlanningGraph *rpg,
                                  State *s,
                                  landmarks::LandmarkGraph *lg,
                                  id_type landmark_graph_id,
                                  set_id_t &landmark_ids,
                                  set_id_t &accepted,
                                  vec_id_t &goal_landmarks_ids){
        /// Add all non-accepted landmarks
        set_id_t not_accepted;
        for( auto lm_id : lg->get_active_landmarks_ids() ){
            if( accepted.find( lm_id ) == accepted.end() )
                not_accepted.insert( lm_id );
        }

        /// Add required preconditions
        std::set< int > required_again;
        for( auto lm_id : accepted ){
            auto landmark = lg->get_landmark(lm_id);
            bool landmark_holds;
            if(landmark->is_pointer_landmark()) landmark_holds = landmark->holds(sd,s);
            else landmark_holds = landmark->holds(rpg, s);
            if( not landmark_holds ){
                /// Required again if it is greedy necessary for a non-accepted landmark
                bool is_req_again = false;
                auto gn_landmarks = lg->get_greedy_necessary_landmark_ordering( lm_id );
                for( auto gn_id : gn_landmarks ){
                    if( not_accepted.find( gn_id ) != not_accepted.end() ){
                        is_req_again = true; break;
                    }
                }
                if( is_req_again ){
                    required_again.insert( lm_id );
                }
            }
        }

        /// Add required again goals
        for( auto lm_id : goal_landmarks_ids ){
            /// If the goal has not been accepted yet continue
            if( accepted.find( lm_id ) == accepted.end() ) continue;
            auto l = lg->get_landmark( lm_id );
            if( not l->holds( rpg, s ) )
                required_again.insert( lm_id );
        }

        _landmark_count += (int)not_accepted.size() + (int)required_again.size();
        // NEW FOR NORMALIZATION
        _unachieved_landmarks[landmark_graph_id] = (int)not_accepted.size() + (int)required_again.size();
    }

    value_t get_landmark_count() const{
        /// Counted in the program instead of the evaluation function to execute expensive programs only once
        return _landmark_count;
    }

    vec_id_t get_unachieved_landmark_ids() const{
        /// Counted in the program instead of the evaluation function to execute expensive programs only once
        return _unachieved_landmarks;
    }
    */

	[[nodiscard]] long long get_num_of_steps() const{
        /// Count the total number of steps taken (applied instructions) in the program execution
	    return _num_of_steps;
	}

    [[nodiscard]] long long get_num_of_math_planning_actions() const{
        /// Count the number of "math" actions applied during the program execution
        return _num_of_math_planning_actions;
    }

    [[nodiscard]] long long get_num_of_mem_planning_actions() const{
        /// Count the number of "memory" actions applied during the program execution
        return _num_of_mem_planning_actions;
    }

    [[nodiscard]] long long get_total_plan_costs() const{
        /// Count the number of applicable "memory" actions during the program execution
        return _total_plan_costs;
    }

    [[nodiscard]] long long get_failed_instance_idx() const{
        /// Returns the idx of the instance that made the program run to fail
        return _failed_instance_idx;
    }

    [[nodiscard]] vec_str_t get_plan(size_t instance_id) const{
        assert(instance_id < _pddl_plans.size());
        return _pddl_plans[instance_id];
    }

    [[nodiscard]] std::string to_string(bool full_info) const{
        std::string ret;
        for(size_t line = 0; line < _instructions.size(); line++ ){
            ret += std::to_string(line ) + ". ";
            if(_instructions[ line ] != nullptr )
                ret += _instructions[line]->to_string(full_info) + "\n";
            else ret += "empty\n";
        }
        return ret;
    }
	
private:
    /// Program instructions
    std::vector<instructions::Instruction*> _instructions;

    /// Empirical complexity data
	long long _num_of_steps;
    long long _num_of_math_planning_actions;
    long long _num_of_mem_planning_actions;
    long long _total_plan_costs;
    long long _failed_instance_idx;

    /// PDDL plans
    std::vector<vec_str_t> _pddl_plans;

    /// Landmarks data
    //std::vector< std::shared_ptr<landmarks::LandmarkGraph> > _landmark_graphs;  // accessible from gpp
    //value_t _landmark_count;
    //vec_id_t _unachieved_landmarks;
};

#endif
