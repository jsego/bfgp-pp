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
            _open.push(std::move(node));
        }

        [[nodiscard]] std::shared_ptr<Node> select_node() override {
            return _open.top();
        }

        [[nodiscard]] bool is_goal(Node* node) override {
            auto p = node->get_program();
            auto vps = p->run( _gpp.get() );
            _last_failed_instance_idx = -1;

            // FIXME: if this happens, then progressive mode fails
            if (vps.empty()) {
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
                if(not end->is_applicable(ins, vps[local_id].get())) {
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

/*bool is_aimed_program(Program *p){
    std::vector<std::string> expected_program ={"for(ptr_object_0--,5)",
                                                                "cmp(ptr_object_0,ptr_object_1)",
                                                                "if((zf=0)(cf=1),4)",
                                                                "swap(ptr_object_0,ptr_object_1)",
                                                                "inc(ptr_object_1)",
                                                                "endfor(ptr_object_0--,0)",
                                                                "end"};
    for(size_t l = 0; l < expected_program.size(); l++) {
        if(p->get_instruction(l) != nullptr and p->get_instruction(l)->get_name(false) != expected_program[l])
            return false;
    }
    return true;
}*/

        [[nodiscard]] std::vector<std::shared_ptr<Node> > expand_node(Node* node) override {
            int pc_max = -1;
            auto p = node->get_program();
            auto instructions = p->get_instructions();

            // Retrieve the pc_max (first program line without a programmed instruction)
            for (size_t ins_idx = 0; ins_idx < instructions.size(); ins_idx++) {
                if (instructions[ins_idx] == nullptr) {
                    pc_max = (int) ins_idx;
                    break;
                }
            }

            /*
            // Retrieve the pc_max from the execution of the program (last nullptr reached)
            auto vps = p->run(_gpp.get());
            for(const auto& ps : vps) {
                auto line = ps->get_line();
                assert(line < p->get_num_instructions());
                if(p->get_instruction(line) == nullptr)
                    pc_max = std::max(pc_max, (int) ps->get_line());
            }
            std::cout << "[INFO] PC_MAX=" << pc_max << "\n";
            */

            // Failure case either when the next valid line is not found or if an instruction is already programmed
            if (pc_max == -1 or p->get_instruction(pc_max) != nullptr) return {};

            //bool only_end = false;  // ToDo: implement after bitvec theory
            //if(_bitvec_theory and pc_max > 0){
            //    auto ins_str = p->get_instruction(pc_max-1)->to_string(false);
            //    if(ins_str.find("vector(ptr-goal) =") != std::string::npos)
            //        only_end = true;
            //}

            std::vector<std::shared_ptr<Node> > childs;
            //auto loop_pattern = get_loop_pattern(p);  // ToDo: implement this for CPP
            auto gd = _gpp->get_generalized_domain();
            int maxi = std::max(1, int(_evaluation_functions.size()));

            for (const auto &ins: gd->get_instructions()) {
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

                // Test the run
                auto vps = p2->run(_gpp.get());
                if(vps.empty()) continue;

                // Update constraints
                _theory->update(p2.get(), ins);

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

        [[nodiscard]] std::shared_ptr<Node> solve() override {
            /// Initialize root program
            /*for(id_type instance_id=1; instance_id < (id_type)_gpp->get_num_instances(); instance_id++){
                _gpp->deactivate_instance(instance_id);
            }*/

            auto root_program = std::make_unique<Program>(_gpp.get());
            _theory->set_initial_program(_gpp.get(), root_program.get());

            auto vps = root_program->run( _gpp.get() );
            _evaluated_nodes = 0;
            auto root = std::make_shared<Node>(
                    std::move(root_program),
                    vec_value_t(_evaluation_functions.size(), INF),
                    _evaluated_nodes++);
            root->set_f(f(root.get()));
            add_node(root);
            vec_value_t best_evaluations(_evaluation_functions.size(), INF);
//bool first=true;
            while (!is_empty()) {
                _expanded_nodes++;
                auto current = select_node();
                // remove current node from open
                _open.pop();
//std::cout << "Current ID:" << current->get_id() << std::endl;
                auto current_evaluations = current->f();
                auto children = expand_node(current.get());

                if (current_evaluations < best_evaluations) {
                    best_evaluations = current_evaluations;
                    print_node(current.get());
                } else if (_expanded_nodes % PROGRAM_FREQUENCY == 0) {
                    print_node(current.get());
                }

                for (const auto &child: children) {
                    /// Checked in the expansion
                    //vps = child->get_program()->run( _gpp.get() );
                    //if (vps.empty()) continue;

                    /*if( _bitvec_theory ) { // closed list of visited program states
                        std::vector<vec_value_t> vvs;
                        for (const auto &ps: vps) vvs.emplace_back(ps->as_vector());
                        if (_closed_program_states.find(vvs) != _closed_program_states.end()) continue;
                        _closed_program_states.insert(vvs);
                    }*/

                    // Evaluate the child
                    child->set_f(f(child.get()));
                    child->set_id(_evaluated_nodes++);

                    if (is_goal(child.get())) {
                        std::cout << "[INFO] Solution candidate!\n" << child->to_string();
                        // if the program solves all instances finish
                        bool is_progressive = _gpp->is_progressive();
                        _gpp->set_progressive(false);
                        bool all_goal = is_goal(child.get());
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
                            std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node> >, NodeComparator> new_open;
                            while(not _open.empty()){
                                auto node = _open.top();
                                _open.pop();
                                node->set_f(f(node.get()));
                                new_open.push(std::move(node));
                            }
                            //child->set_f(f(child.get())); // FIXME: shouldn't be pushed into the queue...
                            std::swap(new_open, _open);
                            std::cout << " done!\n";
                        }
                    }
                    else { // FIXME: only add the child if it was not a tentative goal
                        // Standard A* but no chance to repeat programs
                        // so nodes are always pushed into priority queue
                        add_node(child);
                    }
//if(first) std::cout << "FIRST DATA:\n" << child->to_string() << "\n";
                }
//first = false;
            }

            return nullptr;
        }

    private:
        // In priority_queue, unique_ptr cannot be accessed through top() because is deleted
        std::priority_queue<std::shared_ptr<Node>, std::vector<std::shared_ptr<Node> >, NodeComparator> _open;

        // TEST
        id_type _last_failed_instance_idx;
        //bool _bitvec_theory;
        //std::set<std::vector<vec_value_t>> _closed_program_states;
    };
}

#endif //__SEARCH_BEST_FIRST_SEARCH_H__
