//
// Created by js on 4/05/22.
//

#ifndef __PROGRAM_TRANSLATOR_H__
#define __PROGRAM_TRANSLATOR_H__

#include "utils/common.h"

#include "expressions/conditions/condition.h"
#include "expressions/conditions/greater.h"
#include "expressions/conditions/greater_equal.h"
#include "expressions/conditions/lesser.h"
#include "expressions/conditions/lesser_equal.h"
#include "expressions/conditions/equals.h"
#include "expressions/conditions/add.h"
#include "expressions/conditions/subtrack.h"
#include "expressions/conditions/different.h"

#include "expressions/effects/effect.h"
#include "expressions/effects/add_assign.h"
#include "expressions/effects/assign.h"
#include "expressions/effects/subtrack_assign.h"

#include "instructions/instruction.h"
#include "instructions/planning_action.h"
#include "instructions/for.h"
#include "instructions/end_for.h"
#include "instructions/if.h"
#include "instructions/end.h"

#include "generalized_domain.h"
#include "generalized_planning_problem.h"
#include "utils/argument_parser.h"

class ProgramTranslator{
public:
    /// Translates a program to CPP code (ToDo: [enhancement] other languages)
    explicit ProgramTranslator( GeneralizedPlanningProblem* gpp,
                                const std::vector<instructions::Instruction*> &generalized_plan,
                                utils::ArgumentParser* arg_parse) :
                                _gpp(gpp), _generalized_plan(generalized_plan), _arg_parser(arg_parse), _offset("    "){
    }

    ~ProgramTranslator() = default;

    [[nodiscard]] std::string to_string() const{
        return get_header() + get_predicates() + get_actions() + get_main();
    }

    void generate_input_data(const std::string& folder = "") const{
        /* Gripper example:
         rooms 2
         balls 501
         grippers 2
         at_robby {0} 1
         at {0,0} 1
         at {1,0} 1
         ...
         at {500,0} 1
         free {0} 1
         free {1} 1
        */
        auto var_types = _gpp->get_generalized_domain()->get_domain()->get_object_types();
        auto pred_types = _gpp->get_generalized_domain()->get_domain()->get_functions();

        for(size_t ins_id = 0; ins_id < _gpp->get_num_instances(); ins_id++){
            auto instance = _gpp->get_instance(ins_id);

            /// Step 1. Create initial state info
            std::ofstream ofs_init(folder+"init_" + std::to_string(ins_id+1)+ ".txt");
            // Add bounds info
            for(auto & var_type : var_types){
                auto var_bound = instance->get_typed_variable_domain(var_type->get_name());
                ofs_init << var_type->get_name() << " " << var_bound << "\n";
            }

            // Get initial state
            auto init_state = instance->get_initial_state();

            // Add pointers info
            for(const auto& ptr : _gpp->get_generalized_domain()->get_pointers()){
                ofs_init << ptr->get_name() << " {} 0\n"; // Pointers should all start at 0 in the init
            }

            // Add grounded predicates info

            for(const auto& fact : init_state->get_facts()){
                ofs_init << fact->get_function()->get_name() << " {";
                bool first_val = true;
                for(const auto &obj : fact->get_objects()){
                    ofs_init << (first_val?"":",") + std::to_string(instance->get_typed_object_idx(obj));
                    first_val=false;
                }
                ofs_init << "} " << std::to_string(fact->get_value()) << "\n";
            }
            ofs_init.close();

            /// Step 2. Create goal state info
            std::ofstream ofs_goal(folder + "goal_" + std::to_string(ins_id+1) + ".txt");
            auto goal_cond = instance->get_goal_condition();
            for(const auto& c: goal_cond){
                auto state_var = dynamic_cast<variables::StateVariable*>(c->get_lhs());
                assert(state_var);
                ofs_goal << state_var->get_function()->get_name() << " {";
                bool first_arg = true;
                for(const auto &obj : state_var->get_objects()){
                    ofs_goal << (first_arg?"":",") + std::to_string(instance->get_typed_object_idx(obj));
                    first_arg=false;
                }
                // FIXME: Possible bug when right var is not a constant
                ofs_goal << "} " << c->get_rhs()->get_name() << "\n";
            }
            ofs_goal.close();
        }
    }

private:
    /// Auxiliary functions
    [[nodiscard]] static std::string to_underscore(std::string s){
        std::replace(s.begin(), s.end(), '-', '_');
        return s;
    }

    [[nodiscard]] static std::string get_predicate_cpp_name(const std::string& pred_name) {
        return "pred_" + to_underscore(pred_name);
    }

    [[nodiscard]] static std::string get_action_cpp_name(Action* a) {
        return to_underscore(a->get_name());
    }

    [[nodiscard]] static std::string get_action_cpp_declared_args(Action* a) {
        std::string name = "(";
        bool first_arg = true;
        for(const auto& param : a->get_parameters() ){
            name += (first_arg ? "int _": ", int _") + to_underscore(param->get_name().substr(1)); // skip '?'
            first_arg = false;
        }
        return name + ")";
    }

    [[nodiscard]] static std::string get_predicate_name_and_args(const std::string& pred_name_and_args, size_t offset = 1) {
        //std::cout << "[DEBUG] " << pred_name_and_args << " " << pred_name_and_args.size() << "\n";
        auto first_arg_pos = pred_name_and_args.find_first_of('(', offset);
        auto last_arg_pos = pred_name_and_args.find_first_of(')', first_arg_pos+1);
        auto pred_name = get_predicate_cpp_name(pred_name_and_args.substr(offset, first_arg_pos-offset));
        auto args = pred_name_and_args.substr(first_arg_pos+1,last_arg_pos-1-first_arg_pos);
        std::replace(args.begin(),args.end(),'?','_');
        return pred_name+"[{"+ to_underscore(args)+"}]";
    }

    [[nodiscard]] std::string get_condition_cpp_name(expressions::conditions::Condition* c) const {
        auto lhs = c->get_lhs();
        auto rhs = c->get_rhs();
        auto lhs_name = get_predicate_name_and_args(lhs->get_name());
        auto cond_name = c->get_operator_name();
        auto rhs_name = std::string("");
        /// RHS can be either a predicate or a constant
        auto rhs_pred = dynamic_cast<variables::StateVariable*>(rhs);
        auto rhs_constant = dynamic_cast<variables::ConstantValue*>(rhs);
        if(rhs_pred) rhs_name = get_predicate_name_and_args(rhs->get_name());
        else if(rhs_constant) rhs_name = rhs->get_name();
        else{
            std::cerr << "[ERROR] The RHS of condition " << c->to_string(false) << " neither a StateVariable nor a ConstantValue" << "\n";
            exit(-1007);
        }

        if(cond_name == "+")
            return "(" + lhs_name + cond_name + rhs_name + ")<" + std::to_string(_arg_parser->get_max_val());
        else if(cond_name == "=") cond_name = "==";
        return lhs_name + cond_name + rhs_name;
    }

    [[nodiscard]] static vec_str_t get_effect_cpp_names(expressions::effects::Effect* eff) {
        /// Keep args as shared_ptr for better dynamic cast
        //auto lhs_name = to_underscore(eff->get_lhs()->get_name());
        //auto rhs_name = to_underscore(eff->get_rhs()->get_name());
        /// LHS must be always a predicate function
        auto lhs_name = get_predicate_name_and_args(eff->get_lhs()->get_name());
        /// RHS could be either a predicate or a constant
        auto rhs_name = std::string("");
        auto rhs_sv = dynamic_cast<variables::StateVariable*>(eff->get_rhs());
        auto rhs_constant = dynamic_cast<variables::ConstantValue*>(eff->get_rhs());
        if(rhs_sv) rhs_name = get_predicate_name_and_args(eff->get_rhs()->get_name());
        else if(rhs_constant) rhs_name = eff->get_rhs()->get_name();
        else {
            std::cerr << "[ERROR] The RHS of effect " << eff->to_string(false) << " is neither a StateVariable nor a ConstantValue" << "\n";
            exit(-1007);
        }

        vec_str_t  eff_name;
        eff_name.emplace_back(lhs_name);
        eff_name.emplace_back(eff->get_operator_name());
        eff_name.emplace_back(rhs_name);

        return eff_name;
    }

    [[nodiscard]] static std::string get_aux_var_from_lhs_name(const std::string &name) {
        std::string aux_var = "aux_";
        for(char c : name){
            if(c == '-' or c == ',' or c == '[' or c == ']' or c == '{' or c == '}' )
                aux_var.push_back('_');
            else aux_var.push_back(c);
        }
        return aux_var;
    }

    [[nodiscard]] static vec_str_t get_action_cpp_arg_names(Action* a) {
        vec_str_t names;
        for(const auto &param : a->get_parameters()){
            names.emplace_back(to_underscore(param->get_name()));
        }
        return names;
    }

    [[nodiscard]] static std::string get_ptr_type_name(const std::string &ptr_type) {
        return "n_" + ptr_type;
    }

    /// Step 1. Get the header
    static std::string get_header() {
        return "#include <bits/stdc++.h>\n\nusing namespace std;\n\n";
    }

    /// Step 2. Get the global predicate variables
    [[nodiscard]] std::string get_predicates() const{
        /*
        /// Gripper example:
        // ---- Predicates ----
        map< vector<int>, int> pred_at_robby;
        map< vector<int>, int> pred_at;
        map< vector<int>, int> pred_free;
        map< vector<int>, int> pred_carry;
        */
        std::string pred_data_structs = "// ---- Predicates ----\n";
        /*
        auto sd = _gpp->get_generalized_domain()->get_domain()->get_state_descriptor();
        auto pred_names = sd->get_predicate_types();
        */
        auto funcs = _gpp->get_generalized_domain()->get_domain()->get_functions();
        for( const auto& func : funcs ){
            pred_data_structs += "map< vector<int>, int> " + get_predicate_cpp_name(func->get_name()) + ";\n";
        }
        pred_data_structs += "\n";
        return pred_data_structs;
    }

    /// Step 3. Get the actions
    [[nodiscard]] std::string get_actions() const{
        /*
         /// Gripper move action example
         int act_move(int r1,int r2){
            if(pred_at_robby[{r1}]==1  && pred_at_robby[{r2}]==0  ){
                pred_at_robby[{r1}] = 0;
                pred_at_robby[{r2}] = 1;
                return 0;
            }
            return 1;
         }
         */
        std::string act_funcs = "// ---- Actions ----\n";
        auto dom = _gpp->get_generalized_domain()->get_domain();
        auto actions = dom->get_actions();
        std::set<std::string> action_names;
        for( const auto& act : actions ){
            /// Step 3.a. Action signature
            auto act_f = get_action_cpp_name(act);
            // Check if the action already exists
            if(action_names.find(act_f) != action_names.end()) continue;
            action_names.insert(act_f);

            /// Step 3.b. Add arguments
            act_f = "int " + act_f + get_action_cpp_declared_args(act) + "{\n";

            /// Step 3.c. Add when the action is applicable (Preconditions)
            bool first_pred = true;
            act_f += _offset + "if(";
            auto cpp_conditions = std::string("");
            for( const auto &prec : act->get_preconditions()){
                cpp_conditions += (first_pred?"":" && ");
                cpp_conditions += get_condition_cpp_name(prec);
                first_pred = false;
            }
            if(cpp_conditions.empty()) act_f += "true";
            else act_f += cpp_conditions;
            act_f += "){\n";

            /// Step 3.d. Add the action effects (Effects)
            std::map<std::string,std::string> all_lhs_to_aux;
            std::vector<vec_str_t > all_effs;
            for( const auto &eff : act->get_effects()){ // declare aux; and operate with it
                auto cpp_effs = get_effect_cpp_names(eff);
                all_effs.emplace_back(cpp_effs);
                auto it = all_lhs_to_aux.find(cpp_effs[0]); // get lhs->aux_lhs
                if(it==all_lhs_to_aux.end()){
                    auto aux_var = get_aux_var_from_lhs_name(cpp_effs[0]);
                    act_f += _offset+_offset+"int " + aux_var + "=" + cpp_effs[0] + ";\n";
                    all_lhs_to_aux[cpp_effs[0]] = aux_var;
                }
            }

            // produce all effs over auxs here
            for(const auto &eff : all_effs){
                assert(eff.size() == 3u);
                auto it = all_lhs_to_aux.find(eff[0]);
                assert(it!=all_lhs_to_aux.end());
                act_f += _offset + _offset + (it->second) + " " + eff[1] + " " + eff[2] +";\n"; // aux operator rhs_var
            }

            // copy auxs back to original vars
            for(const auto &lhs2aux : all_lhs_to_aux){
                act_f += _offset + _offset + (lhs2aux.first) + " = " + (lhs2aux.second) + ";\n";
            }

            /// Step 3.e. Add default returned values of action (in-)applicable
            act_f += _offset + _offset + "return 0;\n";
            act_f += _offset + "}\n";
            act_f += _offset + "return 1;\n}\n";
            act_funcs += act_f + "\n";
        }
        return act_funcs;
    }



    [[nodiscard]] std::string get_initial_state() const{
        /* Gripper input bounds example:
         rooms 2
         balls 501
         grippers 2
         i {} 0
         j {} 0
         at-robby {0} 1
         at {0,0} 1
         at {1,0} 1
         ...
         at {500,0} 1
         free {0} 1
         free {1} 1
        */
        std::string tmp_offset = _offset;
        std::string initial_procedure = tmp_offset + "// ---- Initial state ----\n";

        /// Declare pointers
        auto pointers = _gpp->get_generalized_domain()->get_pointers();
        for(const auto& ptr : pointers){
            initial_procedure += tmp_offset + "int " + to_underscore(ptr->get_name()) + "=0;\n";
        }
        for(const auto& obj_type : _gpp->get_generalized_domain()->get_domain()->get_object_types()){
            initial_procedure += tmp_offset + "int n_" + to_underscore(obj_type->get_name()) + "=0;\n";
        }

        initial_procedure += "\n" + tmp_offset + "string initial_filename = string( argv[ 1 ] );\n";
        initial_procedure += tmp_offset + "ifstream ifs_init(initial_filename);\n";
        initial_procedure += tmp_offset + "if(!ifs_init){ cout << initial_filename << \"does not exist\\n\"; return -1;}\n\n";

        initial_procedure += tmp_offset + "string var_type;\n";
        initial_procedure += tmp_offset + "int value;\n";
        auto num_obj_types = _gpp->get_generalized_domain()->get_domain()->get_object_types().size();
        initial_procedure += tmp_offset + "for(int i = 0; i < " + std::to_string(num_obj_types)+ "; i++){\n";
        tmp_offset += _offset;
        initial_procedure += tmp_offset + "ifs_init >> var_type >> value;\n";
        for(const auto& obj_t : _gpp->get_generalized_domain()->get_domain()->get_object_types()){
            auto ptr_t = get_ptr_type_name(obj_t->get_name());
            initial_procedure += tmp_offset + "if(var_type == \"" + obj_t->get_name() + "\") " + ptr_t + " = value;\n";
        }
        tmp_offset = tmp_offset.substr(_offset.size());
        initial_procedure += tmp_offset + "}\n\n";

        /// Parsing predicates, arguments and their value
        initial_procedure += tmp_offset + "string var_name, args;\n";
        initial_procedure += tmp_offset + "while(!ifs_init.eof() and ifs_init >> var_name >> args >> value){\n";
        tmp_offset += _offset;
        initial_procedure += tmp_offset + "replace( args.begin(), args.end(), ',', ' ');\n";
        initial_procedure += tmp_offset + "args = args.substr(1, args.size()-2);\n";
        initial_procedure += tmp_offset + "istringstream parse_args(args);\n";
        initial_procedure += tmp_offset + "int arg_val;\n";
        initial_procedure += tmp_offset + "vector<int> arg_vals;\n";
        initial_procedure += tmp_offset + "while ( parse_args >> arg_val ) arg_vals.push_back( arg_val );\n";

        bool first_pred = true;

        // add grounded predicates
        for(const auto &pred : _gpp->get_generalized_domain()->get_domain()->get_functions()){
            auto pred_name = pred->get_name();
            initial_procedure += tmp_offset + (first_pred?"if ":"else if ") +"(var_name==\"" + pred_name + "\") " +
                                 get_predicate_cpp_name(pred_name) + "[arg_vals]=value;\n";
            first_pred=false;
        }

        // add instantiated pointers
        for(const auto& ptr : _gpp->get_generalized_domain()->get_pointers()){
            auto ptr_name = ptr->get_name();
            initial_procedure += tmp_offset + (first_pred?"if ":"else if ") +"(var_name==\"" + ptr_name + "\") " +
                    to_underscore(ptr_name) + "=value;\n";
            first_pred=false;
        }

        tmp_offset = tmp_offset.substr(_offset.size());

        initial_procedure += tmp_offset + "}\n";
        initial_procedure += tmp_offset + "ifs_init.close();\n";

        return initial_procedure;
    }

    std::string get_instruction_cpp_name(instructions::Instruction* ins,
                                         std::string &tmp_offset,
                                         vec_str_t &last_variables,
                                         std::stack<int> &end_ifs) const{
        auto pa_ins = dynamic_cast<instructions::PlanningAction*>(ins);
        auto for_ins = dynamic_cast<instructions::For*>(ins);
        auto endfor_ins = dynamic_cast<instructions::EndFor*>(ins);
        auto if_ins = dynamic_cast<instructions::If*>(ins);
        auto end_ins = dynamic_cast<instructions::End*>(ins);
        auto ptr_ins = dynamic_cast<instructions::PointerAction*>(ins);
        auto reg_ins = dynamic_cast<instructions::RegisterAction*>(ins);
        if(pa_ins) {
            return tmp_offset + to_underscore(pa_ins->get_action()->get_signature(false)) +";";
        }
        else if(ptr_ins){
            auto act_signature = ptr_ins->get_name(false);
            auto act_name = act_signature.substr(0, act_signature.find_first_of('('));
            auto pointers = ptr_ins->get_pointers();
            /// Math type actions
            if(act_name == "inc"){
                assert(pointers.size() == 1);
                auto bound_var = get_ptr_type_name(pointers[0]->get_type()->get_name());
                return tmp_offset + "if(" + pointers[0]->get_name() + " + 1 < " + bound_var + ") " + pointers[0]->get_name() + "++;";
            }
            else if(act_name == "dec"){
                assert(pointers.size() == 1);
                return tmp_offset + "if(" + pointers[0]->get_name() + " > 0) " + pointers[0]->get_name() + "--;";
            }
            else if(act_name == "set"){
                assert(pointers.size() == 2u);
                last_variables = {pointers[0]->get_name(),pointers[1]->get_name()};
                return tmp_offset + pointers[0]->get_name() + " = " + pointers[1]->get_name() + ";";
            }
            else if(act_name == "cmp"){
                assert(pointers.size() == 2u);
                last_variables = {pointers[0]->get_name(),pointers[1]->get_name()};
                return "";
            }
            else if(act_name == "clear"){
                assert(pointers.size() == 1u);
                return tmp_offset + pointers[0]->get_name() + " = 0;";
            }
            // ToDo: else ERROR?
        }
        else if(reg_ins){
            auto act_signature = reg_ins->get_name(false);
            auto act_name = act_signature.substr(0, act_signature.find_first_of('('));
            auto lhs_fact = get_predicate_name_and_args(reg_ins->get_fact_name(false), 0u);

            if(act_name == "test"){
                last_variables = {lhs_fact, "0"};
                return "";
            }
            else if(act_name == "cmp"){
                auto reg_cmp = dynamic_cast<instructions::RegisterCmp*>(ins);
                auto rhs_fact = get_predicate_name_and_args(reg_cmp->get_right_fact_name(false), 0u);
                last_variables = {lhs_fact, rhs_fact};
                return "";
            }
            else if(act_name == "assign"){
                auto reg_assign = dynamic_cast<instructions::RegisterAssign*>(ins);
                auto rhs_fact = get_predicate_name_and_args(reg_assign->get_right_fact_name(false), 0u);
                return tmp_offset + lhs_fact + " = " + rhs_fact + ";";
            }
            else if(act_name == "set"){
                auto reg_set = dynamic_cast<instructions::RegisterSet*>(ins);
                auto val = reg_set->get_value();
                return tmp_offset + lhs_fact + " = " + std::to_string(val) + ";";
            }
            // ToDo: else ERROR?
        }
        else if(for_ins){ // ToDo: for-- must leave the ptr=0; and for++ ptr=bound-1 after the for
            auto ptr_name = to_underscore(for_ins->get_pointer()->get_name());
            auto bound_var = get_ptr_type_name(for_ins->get_pointer()->get_type()->get_name());

            std::string name;
            if(for_ins->get_modifier()<0){ // decremental for
                name = "for(" + ptr_name + " = " + bound_var + "-1; " + ptr_name + " >= 0; " + ptr_name + "--){";
            }
            else{ // incremental for
                name = "for(" + ptr_name + " = 0; " + ptr_name + " < " + bound_var + "; " + ptr_name + "++){";
            }
            auto current_offset = tmp_offset;
            tmp_offset += _offset;
            return current_offset + name;
        }
        else if(endfor_ins){
            tmp_offset = tmp_offset.substr(_offset.size());
            return tmp_offset + "}";
        }
        else if(if_ins){
            std::string name = "if(" + last_variables[0];
            auto conds = if_ins->get_conds();
            auto c_zf = std::string("zf==")+std::to_string(conds[0].second);
            if(conds.size() == 2u) {
                auto c_cf = std::string("cf==") + std::to_string(conds[1].second);
                if (c_zf == "zf==0" and c_cf == "cf==0") {
                    name += "<";
                } else if (c_zf == "zf==1" and c_cf == "cf==0") {
                    name += "==";
                } else if (c_zf == "zf==0" and c_cf == "cf==1") {
                    name += ">";
                }
                // else{} // zf==1 and cf==1 is forbidden in this encoding
                name += last_variables[1] + "){";
            }
            else{ // conds.size() == 1u
                if(c_zf == "zf==0") name += "==1){";
                else name += "==0){";
            }
            end_ifs.push(if_ins->get_destination_line());

            auto current_offset = tmp_offset;
            tmp_offset += _offset;
            return current_offset + name;
        }
        else if(end_ins){
            return "";
        }
        // ToDo: else ERROR?
        return "";
    }

    [[nodiscard]] std::string get_generalized_plan() const{
        /* Gripper example:
        // ---- Generalized plan ----
        int r1 = 0; int r2 = 0; int b1 = 0; int g1 = 0; // moved before initial state
        for(b1=0; b1<NBALLS; b1++){
            act_pick(b1,r1,g1);
            if (r2<NROOMS-1) r2++;
            act_move(r1,r2);
            act_drop(b1,r2,g1);
            act_move(r2,r1);
        }
        */
        std::string tmp_offset = _offset;
        vec_str_t last_variables;
        std::stack<int> end_ifs;
        std::string generalized_plan = tmp_offset + "// ---- Generalized plan ----\n";
        int line = 0;
        for(const auto& ins : _generalized_plan){
            // Add ENDIF code
            while(!end_ifs.empty() and end_ifs.top() == line){
                tmp_offset = tmp_offset.substr(_offset.size());
                generalized_plan += tmp_offset + "}\n";
                end_ifs.pop();
            }
            auto cpp_instruction = get_instruction_cpp_name(ins, tmp_offset, last_variables, end_ifs);
            if(!cpp_instruction.empty())
                generalized_plan +=  cpp_instruction + "\n";
            line++;
        }
        return generalized_plan;
    }

    [[nodiscard]] std::string get_goal_state() const{
        std::string tmp_offset = _offset;
        std::string goal_procedure = tmp_offset + "// ---- Goal condition ----\n";
        goal_procedure += tmp_offset + "string goal_filename = string( argv[ 2 ] );\n";
        goal_procedure += tmp_offset + "ifstream ifs_goal(goal_filename);\n";
        goal_procedure += tmp_offset + "if(!ifs_goal){ cout << goal_filename << \"does not exist\\n\"; return -2;}\n\n";

        /// Parsing pointers, predicates and arguments, and their corresponding values
        goal_procedure += tmp_offset + "while(!ifs_goal.eof() and ifs_goal >> var_name >> args >> value){\n";
        tmp_offset += _offset;
        goal_procedure += tmp_offset + "replace( args.begin(), args.end(), ',', ' ');\n";
        goal_procedure += tmp_offset + "args = args.substr(1, args.size()-2);\n";
        goal_procedure += tmp_offset + "istringstream parse_args(args);\n";
        goal_procedure += tmp_offset + "int arg_val;\n";
        goal_procedure += tmp_offset + "vector<int> arg_vals;\n";
        goal_procedure += tmp_offset + "while ( parse_args >> arg_val ) arg_vals.push_back( arg_val );\n";

        auto funcs = _gpp->get_generalized_domain()->get_domain()->get_functions();
        bool first_pred = true;
        // Add grounded predicate goal conditions
        for(const auto &func : funcs){
            auto pred_name = func->get_name();
            auto pred_cpp_name = get_predicate_cpp_name(pred_name);
            goal_procedure += tmp_offset + (first_pred ? "if " : "else if ") + "(var_name==\"" + pred_name + "\"){\n";
            tmp_offset += _offset;
            goal_procedure += tmp_offset + "if("+pred_cpp_name + "[arg_vals]!=value){\n";
            tmp_offset += _offset;
            goal_procedure += tmp_offset + "replace( args.begin(), args.end(), ' ', ',');\n";
            goal_procedure += tmp_offset + "cout << \"[ERROR] Fail: "+pred_cpp_name + R"([{"<<args<<"}] is "<<)";
            goal_procedure += pred_cpp_name+"[{arg_vals}] << \" (wrong) instead of \" << value << \" (correct)\\n\";\n";
            goal_procedure += tmp_offset + "return -4;\n";
            tmp_offset = tmp_offset.substr(_offset.size());
            goal_procedure += tmp_offset + "}\n";
            tmp_offset = tmp_offset.substr(_offset.size());
            goal_procedure += tmp_offset+"}\n";
            first_pred=false;
        }
        tmp_offset = tmp_offset.substr(_offset.size());

        goal_procedure += tmp_offset + "}\n";
        goal_procedure += tmp_offset + "ifs_goal.close();\n";
        goal_procedure += tmp_offset + "cout << \"[INFO] Success: goal achieved!\\n\";\n";


        return goal_procedure;
    }

    [[nodiscard]] std::string get_main() const{
        return "int main(int argc, const char* argv[]){\n" +
               _offset + "if(argc!=3){\n"+
               _offset+_offset+"cout << \"[ERROR] The number of arguments must be 3\\n\";\n" +
               _offset+_offset+"cout << \"Running example: ./validator_compiled.bin init.txt goal.txt\\n\";\n"+
               _offset+_offset+"return -3;\n"+
               _offset +"}\n\n" +
               get_initial_state() + "\n" +
               get_generalized_plan() + "\n" +
               get_goal_state() +
               "}\n";
    }

    GeneralizedPlanningProblem* _gpp;
    std::vector<instructions::Instruction*> _generalized_plan;
    utils::ArgumentParser* _arg_parser;
    std::string _offset;
};

#endif //__PROGRAM_TRANSLATOR_H__
