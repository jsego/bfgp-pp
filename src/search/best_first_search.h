//
// Created by js on 24/05/22.
//

#ifndef __SEARCH_BEST_FIRST_SEARCH_H__
#define __SEARCH_BEST_FIRST_SEARCH_H__

#include "engine.h"

namespace search {
    class BFS : public Engine {
    public:
        explicit BFS(std::unique_ptr<GeneralizedPlanningProblem> gpp) : Engine(std::move(gpp)){
            //_bitvec_theory = false;
        }

        ~BFS() override = default;

        /*void set_bitvec_theory(bool is_bitvec){
            _bitvec_theory = is_bitvec;
        }*/

        [[nodiscard]] bool is_empty() const override {
            return _open.empty();
        }

        void add_node(std::shared_ptr<Node> node) override {
            /// Before adding the node, clear up the program states to save memory
            node->get_program()->clear_program_states();
            _open.push(std::move(node));
        }

        [[nodiscard]] std::shared_ptr<Node> select_node() override {
            return _open.top();
        }

        [[nodiscard]] bool is_goal(Node* node, bool run_program=false) override {
            auto p = node->get_program();
            auto vps = (run_program?p->run(_gpp.get()):p->get_program_states());
            _last_failed_instance_idx = -1;

            // FIXME: if this happens, then progressive mode fails
            if (vps.empty()) {
                //std::cout <<run_program << "\n"<< p->to_string(false) << std::endl;
                _last_failed_instance_idx = p->get_failed_instance_idx();
                return false; // Check whether some error occurred during execution
            }

            auto active_instance_idxs = _gpp->get_active_instance_idxs();
            id_type local_id = 0;
            for(const auto& idx : active_instance_idxs){
            //for (id_type id = 0; id < (id_type)vps.size(); id++) {
            //    if(_gpp->is_progressive() and (not _gpp->is_instance_active(id))) continue;
                auto ins = _gpp->get_instance(idx);
                auto line = vps[local_id]->get_line();
                auto end = dynamic_cast<instructions::End*>(p->get_instruction(line));
                // It is not a goal, if the instruction is not an END
                if(end == nullptr) {
                    _last_failed_instance_idx = idx;
                    return false;
                }
                // If the instruction is an END, it cannot be a goal if it is not applicable
                //if(not end->is_applicable(ins, vps[local_id].get())) {  /// vps is a vector of unique pointers
                if(not end->is_applicable(ins, vps[local_id])) {  /// vps is a vector of raw pointers
                    _last_failed_instance_idx = idx;
                    return false;
                }
                // Special test for theory 'actions'
                if(_gpp->is_actions_theory()){
                    // Close world assumption: goal is a state, so check that all what is true in the state holds
                    auto goal_state = ins->get_goal_state();
                    for(const auto& fact : vps[local_id]->get_state()->get_facts()){
                        auto f_name = fact->get_name();
                        if(f_name.size() > 8u and f_name.substr(0,8) == "(action_") continue;
                        if(fact->get_value() != goal_state->get_value(fact)) {
                            _last_failed_instance_idx = idx;
                            return false;
                        }
                    }
                }

                ++local_id;
            }
            return true;
        }

        [[nodiscard]] bool check_base_constraints(Program *p, size_t pc_max, instructions::Instruction* ins){
            /// Validates if exists a line with non-empty instructions where 'p' and 'base_program' programs differ
            /// Input:
            ///  - 'p', the Program to validate
            ///  - 'pc_max', which is the current line to program in 'p'
            ///  - 'ins', the instruction to program at 'pc_max'
            /// Returns:
            ///  - true, if one non-empty instruction differs
            ///  - false, otherwise
            if(nullptr == base_program->get_instruction(pc_max)) return true;
            if(ins->get_id() != base_program->get_instruction(pc_max)->get_id()) return true;
            for(size_t line = 0; line < p->get_num_instructions(); line++){
                auto base_ins = base_program->get_instruction(line);
                auto p_ins = p->get_instruction(line);
                if(nullptr == base_ins or nullptr == p_ins) continue;
                if(base_ins->get_id() != p_ins->get_id()) return true;
            }
            return false;
        }

        [[nodiscard]] std::vector<std::shared_ptr<Node> > expand_node(Node* node) override {
            //int pc_max = -1;
            auto p = node->get_program();
            auto instructions = p->get_instructions();
            int pc_max = p->get_pc_max();  /// Retrieve pc_max from previous program execution

            // Failure case either when the next valid line is not found or if an instruction is already programmed
            if (pc_max == -1 or p->get_instruction(pc_max) != nullptr) return {};

            //bool only_end = false;  // ToDo: implement after bitvec theory
            //if(_bitvec_theory and pc_max > 0){
            //    auto ins_str = p->get_instruction(pc_max-1)->to_string(false);
            //    if(ins_str.find("vector(ptr-goal) =") != std::string::npos)
            //        only_end = true;
            //}

            std::vector<std::shared_ptr<Node> > childs;
            auto gd = _gpp->get_generalized_domain();
            int maxi = std::max(1, int(_evaluation_functions.size()));

            for (const auto &ins: gd->get_instructions()) {
//std::cout << "[INFO] checking new expansion with instruction:\n" << ins->to_string(true) << "\n";
                /******
                //if(_bitvec_theory){  // ToDo: implement after bitvec theory
                //    auto ins_end = std::dynamic_pointer_cast<instructions::End>(i);
                //    if(only_end and not ins_end) continue;
                //}
                 // Check if the instruction is an ITE
                //auto ins_ite = dynamic_cast<instructions::bitvec::ITE*>(ins);  // ToDo: implement after bitvec theory
                //if(ins_ite){ // ToDo: implement after bitvec theory
                //    // 1. Check first if only ite can be programmed
                //    if (not only_branching) continue;
                //}
                 *****/

                if(nullptr != base_program and (not check_base_constraints(p, pc_max, ins))) continue;

                if( not _theory->check_syntax_constraints(p, pc_max, ins) or
                    not _theory->check_semantic_constraints(_gpp.get(), p, pc_max, ins)) continue;

                // Make a new child
                auto p2 = p->copy();
                p2->set_instruction(pc_max, ins);

                // Special expansion for CPP theory.
                // If the current instruction is a FOR, we also program an ENDFOR at destination line
                auto ins_for = dynamic_cast<instructions::For*>(ins);
                if (ins_for) {
                    auto for_ptr = ins_for->get_pointer();
                    auto dest_line = ins_for->get_destination_line();
                    auto endfor_name = "endfor(" + for_ptr->get_name() + (ins_for->get_modifier()>0?"++":"--") +
                            "," + std::to_string(pc_max) + ")";
                    auto endfor_instruction = gd->get_instruction(endfor_name);
                    p2->set_instruction(dest_line, endfor_instruction);
                }

                // Update constraints
                //_theory->update(p2.get(), ins);

                childs.emplace_back(std::make_shared<Node>(std::move(p2), vec_value_t(maxi, 0)));
            }

            return childs;
        }

        [[nodiscard]] vec_value_t f(Node* node) override {
            auto p = node->get_program();
            vec_value_t val_h;
            val_h.reserve(_evaluation_functions.size());
            for (const auto &ef: _evaluation_functions)
                val_h.emplace_back(ef->compute(p, _gpp.get()));
            return val_h;
        }

        void print_node(Node *n){
            std::cout << "[ENGINE]\n";
            std::cout << "Node id=" << n->get_id() << "\n";
            std::cout << "Expanded=" << _expanded_nodes << "\n";
            std::cout << "Evaluated=" << _evaluated_nodes << "\n";
            std::cout << "Open queue size=" << _open.size() << "\n";
            std::cout << n->to_string() << "\n";
        }

        [[nodiscard]] std::shared_ptr<Node> solve(std::vector<std::unique_ptr<Program>> roots = {}) override {
            if(roots.empty()){
                /// Initialize the empty root program
                roots.emplace_back(std::make_unique<Program>(_gpp.get()));
                this->base_program = nullptr;
            }
            else{
                /// Otherwise, constraints are added from the input program (last in roots) to avoid search duplicates
                this->base_program = roots[roots.size()-1]->copy();
                /// Also check whether the base program is a goal
                _evaluated_nodes = 0;
                _theory->set_initial_program(_gpp.get(), this->base_program.get());
                auto base_node = std::make_shared<Node>(this->base_program->copy(),
                                                        vec_value_t(_evaluation_functions.size(), INF),
                                                        _evaluated_nodes++);
                // if the program solves all instances finish
                bool is_progressive = _gpp->is_progressive();
                _gpp->set_progressive(false);
                bool all_goal = is_goal(base_node.get(), true);
                _gpp->set_progressive(is_progressive);
                if (all_goal) {
                    base_node->set_f(f(base_node.get()));
                    add_node(base_node);
                    return base_node;
                }
            }

            _evaluated_nodes = 0;
            for(int idx = roots.size()-1; idx >= 0; idx--){
//std::cout << "[INFO] new root node " << std::endl << roots[idx]->to_string(true) << std::endl;
                _theory->set_initial_program(_gpp.get(), roots[idx].get());
                roots[idx]->run(_gpp.get()); /// This must be the first an unique run of each root
                auto root_node =std::make_shared<Node>(std::move(roots[idx]),
                                                       vec_value_t(_evaluation_functions.size(), INF),
                                                       _evaluated_nodes++);
                root_node->set_f(f(root_node.get()));
                add_node(root_node);
            }

            vec_value_t best_evaluations(_evaluation_functions.size(), INF);

            while (!is_empty()) {
                _expanded_nodes++;
                auto current = select_node();
//std::cout << "[INFO] Selecting node:\n" << current->to_string() << "\n";
                // remove current node from open
                _open.pop();
                auto current_evaluations = current->f();
                auto children = expand_node(current.get());
//std::cout << "[INFO] Total new expansions = " << children.size() << "\n";
                if (current_evaluations < best_evaluations) {
                    best_evaluations = current_evaluations;
                    print_node(current.get());
                } else if (_verbose and _expanded_nodes % PROGRAM_FREQUENCY == 0) {
                    print_node(current.get());
                }

                for (const auto &child: children) {
//std::cout << "[INFO] New child to evaluate:\n" << child->to_string() << "\n";
                    /// Checked in the expansion
                    //vps = child->get_program()->run( _gpp.get() );
                    //if (vps.empty()) continue;
                    /*if( _bitvec_theory ) { // closed list of visited program states
                        std::vector<vec_value_t> vvs;
                        for (const auto &ps: vps) vvs.emplace_back(ps->as_vector());
                        if (_closed_program_states.find(vvs) != _closed_program_states.end()) continue;
                        _closed_program_states.insert(vvs);
                    }*/

                    // Evaluate the child (this must be the first and unique run of the program)
                    // Issue #4: keep the program run right before node evaluation, since PGP could change
                    // the number of active instances, hence yield to an inconsistent evaluation
                    auto vps = child->get_program()->run(_gpp.get());
                    if(vps.empty()) continue;
                    child->set_f(f(child.get()));
                    child->set_id(_evaluated_nodes++);

                    if (is_goal(child.get(), false)) {
                        std::cout << "[INFO] Solution candidate!\n" << child->to_string();
                        // if the program solves all instances finish
                        bool is_progressive = _gpp->is_progressive();
                        _gpp->set_progressive(false);
                        bool all_goal = is_goal(child.get(), true);
                        _gpp->set_progressive(is_progressive);
                        if (all_goal) {
                            child->set_f(f(child.get()));
                            add_node(child);
                            return child;
                        }
                        else{
                            // Get the failure id
                            assert(_last_failed_instance_idx != -1);
                            assert(not _gpp->is_instance_active(_last_failed_instance_idx));
                            std::cout << "[INFO] Failure on instance " << (_last_failed_instance_idx + 1) << " reevaluating... ";
                            // activate it
                            _gpp->activate_instance(_last_failed_instance_idx);
                            // reevaluate queue
                            std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node> >, NodeComparator> old_open;
                            std::swap(old_open, _open);
                            // Also add the current child, just in case is a correct partial solution
                            old_open.push(child);
                            while(not old_open.empty()){
                                auto node = old_open.top();
                                node->get_program()->run(_gpp.get()); // run again the program
                                old_open.pop();
                                node->set_f(f(node.get()));
                                node->set_id(_evaluated_nodes++); // Node reevaluated!
                                add_node(node);
                            }
                            std::cout << " done!\n";
                        }
                    }
                    else {
                        // Standard A* but no chance to repeat programs so nodes are always pushed into priority queue
                        add_node(child);
                    }
                }
            }

            return nullptr;
        }

    private:
        // In priority_queue, unique_ptr cannot be accessed through top() because is deleted
        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node> >, NodeComparator> _open;

        // Search constraints
        std::unique_ptr<Program> base_program;

        // TEST
        id_type _last_failed_instance_idx;
        //bool _bitvec_theory;
        //std::set<std::vector<vec_value_t>> _closed_program_states;
    };
}

#endif //__SEARCH_BEST_FIRST_SEARCH_H__
