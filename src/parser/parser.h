#ifndef __PARSER_H__
#define __PARSER_H__

#include "../utils/common.h"
#include "../utils/bfgp_utils.h"
#include "../variables/variable.h"
#include "../state.h"

#include "../expressions/conditions/condition.h"
#include "../expressions/conditions/greater.h"
#include "../expressions/conditions/greater_equal.h"
#include "../expressions/conditions/lesser.h"
#include "../expressions/conditions/lesser_equal.h"
#include "../expressions/conditions/equals.h"
#include "../expressions/conditions/add.h"
#include "../expressions/conditions/subtrack.h"
#include "../expressions/conditions/different.h"

#include "../expressions/effects/effect.h"
#include "../expressions/effects/add_assign.h"
#include "../expressions/effects/assign.h"
#include "../expressions/effects/compare.h"
#include "../expressions/effects/subtrack_assign.h"
#include "../expressions/effects/bitvec/and.h"
#include "../expressions/effects/bitvec/not.h"
#include "../expressions/effects/bitvec/or.h"
#include "../expressions/effects/bitvec/shift_left.h"
#include "../expressions/effects/bitvec/shift_right.h"
#include "../expressions/effects/bitvec/xor.h"

#include "../action.h"
#include "../domain.h"
#include "../instance.h"

namespace parser {
    class Parser {
    public:
        Parser() = default;

        ~Parser() = default;

        /*
        static std::unique_ptr<variables::Variable> read_grounded_var(const std::string &name, Instance *ins ){
            std::string var_name = name;
            std::string var_type;
            id_type var_id;
            vec_id_t param_ids;
            size_t pos;

            if( utils::is_digit(name) ) {
                var_type = NAME_VAR_TYPE_CONSTANT;
                std::istringstream iss(name);
                iss >> var_id;  // this is to avoid atoi, atoll, and related functions that are type dependant
                //var_id = std::atoll( name.c_str() );
            }
            else if( (pos = name.find('(')) != std::string::npos ) {
                var_type = NAME_VAR_TYPE_PREDICATE;
                var_name = name.substr( 0, pos );
                var_id = sd->get_type_id(var_name);
                var_name += "(";
                auto param_names = utils::split( name.substr( pos+1, (name.length() - 1 ) - (pos+1) ) );
                for (size_t i = 0; i < param_names.size(); i++) {
                    auto obj_address = ins->get_object_address(param_names[i]);
                    param_ids.emplace_back(-(obj_address + 1)); // const objects have ids < 0;
                    //var_name += param_name;
                    var_name += (i ? "," : "") + std::to_string(obj_address);
                }
                var_name += ")";
            }
            else {
                var_type = NAME_VAR_TYPE_POINTER;
                var_id = sd->get_type_id(name);
            }

            return std::make_unique<variables::Variable>( var_name, var_type, var_id, param_ids  );
        }

        static std::unique_ptr<variables::Variable> grounding_var(const std::string& name,
                                                       const map_str_idx_t& par_name_to_idx,
                                                       const vec_str_t& grounded_params ){
            std::string var_name = name, var_type;
            id_type var_id;

            bool var_constant = utils::is_digit(name);
            vec_id_t param_ids;
            size_t pos;
            if( var_constant ) {
                var_type = NAME_VAR_TYPE_CONSTANT;
                std::istringstream iss(name);
                iss >> var_id;  // this is to avoid atoi, atoll, and related functions that are type dependant
                //var_id = std::atoll( name.c_str() );
            }
            else if( (pos = name.find('(')) != std::string::npos ) {
                var_type = NAME_VAR_TYPE_PREDICATE;
                var_name = name.substr( 0, pos );
                var_id = sd->get_type_id(var_name);
                var_name += "(";
                auto param_names = utils::split( name.substr( pos+1, (name.length() - 1 ) - (pos+1) ) );
                for( unsigned i = 0; i < param_names.size(); i++){
                    //std::cout << name << " => " << var_name << ": " << param_names[i] << "\n";
                    auto it = par_name_to_idx.find(param_names[i]);
                    assert(it != par_name_to_idx.end());
                    auto idx = it->second;
                    assert(idx < (id_type)grounded_params.size());
                    auto param_id = sd->get_type_id(grounded_params[idx]); // get pointer ID
                    param_ids.emplace_back(param_id);
                    var_name += (i?",":"") + sd->get_pointer_name(param_id);
                }
                var_name += ")";
            }
            else {
                var_type = NAME_VAR_TYPE_POINTER;
                var_id = sd->get_type_id(name);
            }

            return std::make_unique<variables::Variable>( var_name, var_type, var_id, param_ids  );
        }*/

        static void process_keyword(std::ifstream &ifs, const std::string& expected_keyword, int error_code){
            std::string word;
            ifs >> word;
            if(word != expected_keyword)
                utils::system_error("Unexpected keyword " + word + " instead of " + expected_keyword,
                                    error_code);
        }

        static bool is_definition(const std::string &name){
            /// A definition has the form 'var_name:var_type'
            auto it_first = name.find_first_of(':');
            auto it_last = name.find_last_of(':');
            // At least 3 chars required, and there must be a single ':' between [1,size()-2]
            if (name.size() < 3 or it_first == std::string::npos or it_first != it_last or it_first == 0 or
                it_first == name.size() - 1)
                return false;
            return true;
        }

        static std::pair<std::string, std::string> get_definition(const std::string &word) {
            /// A definition has the form "name:type" where name and type are strings
            if(not is_definition(word))
                utils::system_error("Wrong definition syntax: " + word, ERROR_PARSING_DOMAIN);
            auto it_first = word.find_first_of(':');
            return std::make_pair(word.substr(0, it_first), word.substr(it_first + 1));
        }

        static bool is_lifted_state_variable(const std::string &name){
            /// A lifted state variable has the form 'var_name(?arg1,...)' with a possible empty list of arguments
            // ToDo: args could be partially grounded with Constant Objects
            auto it_first_lp = name.find_first_of('(');
            auto it_last_lp = name.find_last_of('(');
            auto it_first_rp = name.find_first_of(')');
            auto it_last_rp = name.find_last_of(')');
            // If it doesn't have at least 3 chars, starts with '(' or doesn't end with ')', or there are more of one
            // parenthesis of a kind, then it is not a lifted state variable or its syntax is wrong
            if(name.size() < 3 or name[0] == '(' or name[name.size()-1] != ')' or it_first_lp == std::string::npos or
                it_first_rp == std::string::npos or it_first_lp != it_last_lp or it_first_rp != it_last_rp)
                return false;
            // The 'var_name' cannot be a number
            auto var_name = name.substr(0,it_first_lp);
            if(utils::is_number(var_name)) return false;
            // The arguments cannot be empty or definitions, and must start with '?'
            auto arguments = utils::split(name.substr(it_first_lp+1,it_first_rp-it_first_lp-1));

            return std::all_of(arguments.begin(),arguments.end(), [](const std::string &s){
                return (not s.empty()) and s[0]=='?' and (not is_definition(s));
            });
            //for(const auto& arg : arguments)
            //    if(arg.empty() or arg[0] != '?' or is_definition(arg)) return false;
            //// Othewise, the lifted state variable syntax is correct
            //return true;
        }

        static std::pair<std::string,vec_str_t> get_lifted_state_variable(const std::string &word){
            if(not is_lifted_state_variable(word))
                utils::system_error("Wrong lifted state variable syntax: " + word, ERROR_PARSING_DOMAIN);
            auto it = word.find_first_of('(');
            auto var_name = word.substr(0, it);
            auto args_str = word.substr(it + 1, word.size() - it - 2);
            auto args_vec = utils::split(args_str);
            return std::make_pair(var_name, args_vec);
        }

        static std::unique_ptr<variables::Variable> make_variable(const std::string &name,
                                                       Domain *dom = nullptr,
                                                       Action *act = nullptr ){
            /// Factory method of variables
            // Add more Variable options (Pointer, Flag,...)
            if(utils::is_number(name)) {
                /// If the name is a number, then return it as a ConstantValue
                return std::make_unique<variables::ConstantValue>(utils::str_to_num(name));
            }
            else if(dom!= nullptr and act != nullptr and is_lifted_state_variable(name)){
                /// A lifted state variable belongs to an action and uses domain functions, hence
                /// it requires domain and action pointers to validate parameters/arguments types
                auto lifted_sv = get_lifted_state_variable(name);
                auto func_ptr = dom->get_function(lifted_sv.first);
                if(func_ptr== nullptr)
                    utils::system_error("Function symbol " + lifted_sv.first +
                    " not found when creating state variable " + name, ERROR_PARSING_DOMAIN);
                // func_objs used for syntax type checking with action parameters
                size_t idx = 0;
                auto func_objs = func_ptr->get_parameters();
                auto act_parameters = act->get_parameters();
                std::vector<Object*> lifted_sv_args;
                for(const auto& arg : lifted_sv.second){
                    auto obj_ptr = act->get_parameter(arg);
                    // Failure if the argument does not match those of the action
                    if(obj_ptr == nullptr)
                        utils::system_error("Parameter "+arg+" does not exist in the action " +
                            act->get_signature(false) + " when parsing lifted state variable " + name);
                    // Failure if the argument differs from the corresponding function arguments and all its subtypes
                    if(obj_ptr->get_type() != func_objs[idx]->get_type() and
                        not obj_ptr->get_type()->is_subtype(func_objs[idx]->get_type()))
                        utils::system_error("The type parameter ("+obj_ptr->get_type()->get_name()+
                            ") of the action neither is the function argument ("+func_objs[idx]->get_type()->get_name()+
                            ") nor its subtype.");
                    // Success, the argument matches with the function type and action parameters
                    lifted_sv_args.emplace_back(obj_ptr);
                    idx++;
                }
                // Use default value for lifted state variables, they need to be interpreted in a state
                return std::make_unique<variables::StateVariable>(func_ptr, lifted_sv_args);
            }
            return nullptr;
        }

        static std::unique_ptr<expressions::conditions::Condition> make_condition(
                const std::string &name,
                std::unique_ptr<variables::Variable> lhs,
                std::unique_ptr<variables::Variable> rhs ){
            /// Factory method of conditions
            if( ">=" == name ) return std::make_unique<expressions::conditions::GreaterEqual>( std::move(lhs), std::move(rhs) );
            else if( "<=" == name ) return std::make_unique<expressions::conditions::LesserEqual>( std::move(lhs), std::move(rhs) );
            else if( ">" == name ) return std::make_unique<expressions::conditions::Greater>( std::move(lhs), std::move(rhs) );
            else if( "<" == name ) return std::make_unique<expressions::conditions::Lesser>( std::move(lhs), std::move(rhs) );
            else if( "=" == name ) return std::make_unique<expressions::conditions::Equals>( std::move(lhs), std::move(rhs) );
            else if( "+" == name ) return std::make_unique<expressions::conditions::Add>( std::move(lhs), std::move(rhs) );
            else if( "-" == name ) return std::make_unique<expressions::conditions::Subtract>( std::move(lhs), std::move(rhs) );
            else if( "!=" == name ) return std::make_unique<expressions::conditions::Different>( std::move(lhs), std::move(rhs) );
            return nullptr;
        }

        static std::unique_ptr<expressions::effects::Effect> make_effect(
                const std::string &name,
                std::unique_ptr<variables::Variable> lhs,
                std::unique_ptr<variables::Variable> rhs ){
            /// Factory method of effects
            if( "+=" == name ) return std::make_unique<expressions::effects::AddAssign>(std::move(lhs), std::move(rhs));
            else if( "-=" == name ) return std::make_unique<expressions::effects::SubtractAssign>(std::move(lhs), std::move(rhs));
            else if( "=" == name ) return std::make_unique<expressions::effects::Assign>(std::move(lhs), std::move(rhs));
            else if( "-" == name ) return std::make_unique<expressions::effects::Compare>(std::move(lhs), std::move(rhs));
            else if( "=~" == name ) return std::make_unique<expressions::effects::bitvec::Not>(std::move(lhs), std::move(rhs));
            else if( "&=" == name ) return std::make_unique<expressions::effects::bitvec::And>(std::move(lhs), std::move(rhs));
            else if( "|=" == name ) return std::make_unique<expressions::effects::bitvec::Or>(std::move(lhs), std::move(rhs));
            else if( "^=" == name ) return std::make_unique<expressions::effects::bitvec::Xor>(std::move(lhs), std::move(rhs));
            else if( "<<=" == name ) return std::make_unique<expressions::effects::bitvec::ShiftLeft>(std::move(lhs), std::move(rhs));
            else if( ">>=" == name ) return std::make_unique<expressions::effects::bitvec::ShiftRight>(std::move(lhs), std::move(rhs));
            return nullptr;
        }


        static std::pair<std::string, vec_str_t > get_signature(const std::string &word){
            /// A signature must be of the form "name(?arg1:arg_type1,...)" and possibly with no arguments
            auto it_first_lp = word.find_first_of('(');
            auto it_last_lp = word.find_last_of('(');
            auto it_first_rp = word.find_first_of(')');
            auto it_last_rp = word.find_last_of(')');
            // If the word has less than 3 letters, or starts with '(' or does not end with ')',
            // or does not have exactly one '(' and ')', then it is a wrong function syntax
            if (word.size() < 3 or word[0] == '(' or word[word.size() - 1] != ')' or it_first_lp != it_last_lp or
                it_first_rp != it_last_rp or it_first_rp == std::string::npos or it_first_lp == std::string::npos)
                utils::system_error("Wrong signature syntax: " + word, ERROR_PARSING_DOMAIN);

            // Now it can savely parse the signature name
            auto sig_name = word.substr(0, it_first_lp);
            // Get all the word content between parentheses, e.g., the dots in (...)
            auto word_args = word.substr(it_first_lp + 1, it_first_rp - it_first_lp - 1);
            auto arguments = utils::split(word_args); // splitted by comma ','
            // Sanity check - arguments must be non-empty and start with '?'
            for (const auto &arg: arguments) {
                if (arg.empty() or arg[0] != '?')  // ToDo: it could also be a constant object
                    utils::system_error("Function argument " + arg + " is wrong, it must be non-empty and start with ?",
                                        ERROR_PARSING_DOMAIN);
            }
            return std::make_pair(sig_name, arguments);
        }

        static bool is_expression(const std::string &name){
            /// An expression has the form '(var1 op var2)' without whitespaces
            // At least the expression requires 5 letters, start with '(' and end with ')'
            if(name.size() < 5 or name[0] != '(' or name[name.size()-1] != ')') return false;
            // Remove the left and right parentheses
            auto expression = name.substr(1,name.size()-2);
            // Get the location of the first invalid char for variables (first char of the operator)
            auto it = expression.find_first_not_of(_valid_var_chars);
            // The first invalid char for variables must be the first valid for operators, and
            // the first variable must be non-empty
            if(it == 0 or it == std::string::npos) return false;
            auto var1 = name.substr(0, it);
            auto it2 = expression.find_first_of(_valid_var_chars,it);
            // There must be at least one remaining valid char for var2
            if(it2 == std::string::npos) return false;
            // There shouldn't be more invalid chars after var2, wrong syntax.
            // Other validations are performed when making the variables, conditions or effects.
            return expression.find_first_not_of(_valid_var_chars,it2) == std::string::npos;
        }

        static vec_str_t get_expression(const std::string &word){
            /// An expression has the form '(var1 op var2)' without whitespaces
            if(not is_expression(word))
                utils::system_error("The syntax is wrong for expression " + word, ERROR_PARSING_DOMAIN);
            // For more details, look at the comments in 'is_expression'
            auto expression = word.substr(1,word.size()-2);
            auto op_start_pos = expression.find_first_not_of(_valid_var_chars);
            auto var2_start_pos = expression.find_first_of(_valid_var_chars,op_start_pos);
            auto var1 = expression.substr(0, op_start_pos);
            auto op = expression.substr(op_start_pos, var2_start_pos-op_start_pos);
            auto var2 = expression.substr(var2_start_pos);
            return {var1, op, var2};
        }

        static bool is_state_variable(Instance *ins, const std::string &name){
            /// A state variable must be of the form 'func_name(obj_name1,...)'
            auto it_first_lp = name.find_first_of('(');
            auto it_last_lp = name.find_last_of('(');
            auto it_first_rp = name.find_first_of(')');
            auto it_last_rp = name.find_last_of(')');
            // There must be exactly one '(' and ')' in this relative order, and '(' cannot be in the first
            // position and ')' must be in at the end
            if(it_first_lp == std::string::npos or it_first_rp == std::string::npos or
                it_first_lp != it_last_lp or it_first_rp != it_last_rp or it_first_lp > it_first_rp or
                it_first_lp == 0 or it_first_rp != name.size()-1 )
                    return false;

            // After this point, it must be a state variable, the rest is to check its correctness,
            // with critical error reported

            // The function must exist in the domain
            auto func_str = name.substr(0, it_first_lp);
            auto dom = ins->get_domain();
            if(dom == nullptr)
                utils::system_error("The domain does not exist", ERROR_PARSING_INSTANCE);
            auto func_ptr = dom->get_function(func_str);
            if(func_ptr == nullptr)
                utils::system_error("The function symbol " + func_str + " from instance " + ins->get_name() +
                                            " does not exist in the domain", ERROR_PARSING_INSTANCE);

            // The number of objects must match with those of the function
            auto objs_str = name.substr(it_first_lp + 1, it_first_rp - it_first_lp - 1);
            auto objs_vec_str = utils::split(objs_str);
            auto func_params = func_ptr->get_parameters();
            if(objs_vec_str.size() != func_params.size())
                utils::system_error(
                        "In instance " + ins->get_name() + ", the state variable " + name +
                        " does not match the grounding size (" + std::to_string(objs_vec_str.size()) +
                        ") of the corresponding function parameters size (" + std::to_string(func_params.size()) + ")",
                        ERROR_PARSING_INSTANCE);

            // The objects must be of the same type or a subtype of the corresponding function argument type
            for(size_t idx = 0; idx < objs_vec_str.size(); idx++){
                auto obj_ptr = ins->get_object(objs_vec_str[idx]);
                if(obj_ptr == nullptr)
                    utils::system_error( "In instance " + ins->get_name() + ", the object " +
                                                objs_vec_str[idx] + " does not exist", ERROR_PARSING_INSTANCE);
                if(obj_ptr->get_type() == func_params[idx]->get_type()) continue;
                if(obj_ptr->get_type()->is_subtype(func_params[idx]->get_type())) continue;

                // If types do not match, throw an error
                utils::system_error("In instance " + ins->get_name() +", state variable " + name +
                ", the type of the object " + objs_vec_str[idx] + " does match the function parameter type" +
                func_params[idx]->get_type()->to_string(false), ERROR_PARSING_INSTANCE);
            }

            return true;
        }

        static std::unique_ptr<variables::StateVariable> make_fact(Instance *ins, const std::string &name){
            /// A fact must be of the form '(func_name(obj_name1,...)=value)'
            auto expr = get_expression(name);
            assert(expr.size() == 3u);
            if(expr[1] != "=")
                utils::system_error("The syntax is wrong for fact " + name +", '=' expected",ERROR_PARSING_INSTANCE);
            auto lhs_str = expr[0]; // must be a state variable
            auto rhs_str = expr[2]; // must be a value_t number
            auto dom = ins->get_domain();
            assert(dom!= nullptr);
            if(not is_state_variable(ins, lhs_str))
                utils::system_error("The lhs of fact " + name + " is not a valid state variable", ERROR_PARSING_INSTANCE);
            if(not utils::is_number(rhs_str))
                utils::system_error("The rhs of fact " + name + " is not a number", ERROR_PARSING_INSTANCE);
            auto it = lhs_str.find('(');
            // Get the function pointer
            auto func_str = lhs_str.substr(0, it);
            auto func_ptr = dom->get_function(func_str);
            // Get the vector of object pointers
            auto objs_str = lhs_str.substr(it + 1, lhs_str.size() - it - 2);
            auto objs_vec_str = utils::split(objs_str);
            std::vector<Object*> obj_ptrs;
            for(size_t idx = 0; idx < objs_vec_str.size(); idx++){
                obj_ptrs.emplace_back(ins->get_object(objs_vec_str[idx]));
            }
            return std::make_unique<variables::StateVariable>(func_ptr, obj_ptrs, utils::str_to_num(rhs_str));
        }

        static void parse_object_type(Domain *dom, const std::string &word) {
            /// Types must be of the form "type:supertype" and provided in the right order (supertype must already exist)
            // ToDo: make the declarations independent of the right order
            auto type_pair = get_definition(word);
            auto obj_type_str = type_pair.first;
            // Check the derived type is not 'object'
            if (obj_type_str == "object")
                utils::system_error("The 'object' type cannot be used in derived types", ERROR_PARSING_DOMAIN);
            auto supertype_str = type_pair.second;
            // Check the supertype exists in the domain
            auto supertype = dom->get_object_type(supertype_str);
            if (supertype == nullptr)
                utils::system_error("The supertype " + supertype_str + " does not exist", ERROR_PARSING_DOMAIN);

            // At this point everything is fine and the object type can be inserted in the domain
            auto ot = std::make_unique<ObjectType>(obj_type_str, supertype);
            dom->add_object_type(std::move(ot));
        }

        static void parse_constant_object(Domain *dom, const std::string &word) {
            /// Constant objects must be of the form "object_name:type"
            auto obj_pair = get_definition(word);
            auto constant_obj_str = obj_pair.first;
            if (dom->get_constant(constant_obj_str) != nullptr)
                utils::system_error("The constant object " + constant_obj_str + " already exists",
                                    ERROR_PARSING_DOMAIN);
            auto type_str = obj_pair.second;
            auto type_ptr = dom->get_object_type(type_str);
            if (type_ptr == nullptr)
                utils::system_error("The object type " + type_str + " does not exist", ERROR_PARSING_DOMAIN);

            // At this point everything is fine and the constant object can be inserted in the domain
            dom->add_constant(std::make_unique<Object>(constant_obj_str, dom->get_next_const_id(), type_ptr));
        }

        static void parse_instance_object(Instance *ins, const std::string &word){
            /// Instance objects must be of the form "object_name:type" and added to the instance
            auto dom = ins->get_domain();
            assert(dom != nullptr);
            auto obj_pair = get_definition(word);
            auto obj_name_str = obj_pair.first;
            auto obj_type_str = obj_pair.second;
            // check if the object exists in the domain constants
            if(dom->get_constant(obj_name_str) != nullptr )
                utils::system_error("The instance object " + obj_name_str + " already exists in domain constants",
                                    ERROR_PARSING_INSTANCE);
            // check if already exist in the instance
            if(ins->get_object(obj_name_str) != nullptr)
                utils::system_error("The instance object " + obj_name_str + " already exists",
                                    ERROR_PARSING_INSTANCE);
            // check type is correct
            auto obj_type_ptr = dom->get_object_type(obj_type_str);
            if(obj_type_ptr == nullptr)
                utils::system_error("The object type " + obj_type_str + " does not exist",
                                    ERROR_PARSING_INSTANCE);

            // make and add the object to the instance
            ins->add_object(std::make_unique<Object>(obj_name_str, ins->get_next_obj_id(), obj_type_ptr));
        }

        static void parse_action_argument(Domain *dom, Action *act, const std::string &arg){
            /// An argument is a local object of the action
            if(arg.size() < 2 or arg[0] != '?')
                utils::system_error("The argument " + arg + " is too short or does not start with '?'",
                                    ERROR_PARSING_DOMAIN);
            auto arg_def = get_definition(arg);
            auto arg_name_str = arg_def.first;
            auto arg_ptr = act->get_parameter(arg_name_str);
            // Check if the argument name is repeated
            if(arg_ptr != nullptr)
                utils::system_error("The argument " + arg_name_str + " is repeated in action " +
                                    act->get_signature(false),ERROR_PARSING_DOMAIN);
            auto arg_type_str = arg_def.second;
            auto arg_type_ptr = dom->get_object_type(arg_type_str);
            // Check if the argument type does not exist
            if(arg_type_ptr == nullptr)
                utils::system_error("The argument type " + arg_type_str + " does not exist", ERROR_PARSING_DOMAIN);

            // The parameter can safely be added
            act->add_parameter(std::make_unique<Object>(arg_name_str, act->get_next_parameter_id(),arg_type_ptr));
        }

        static void parse_function(Domain *dom, const std::string &word) {
            /// Functions must be of the form "func_name(?arg1:arg_type1,?arg2:arg_type2,...)" where args are possibly empty
            // Split the signature into name and arguments
            auto sig = get_signature(word);
            auto func_name = sig.first;
            auto arguments = sig.second;
            // Check if the function name already exists in the domain
            auto func_ptr = dom->get_function();
            if (func_ptr != nullptr)
                utils::system_error("Function " + func_name + " already exists", ERROR_PARSING_DOMAIN);
            auto func_uptr = std::make_unique<Function>(func_name, dom->get_next_func_id());

            // Add all arguments to the function with a sanity check of starting with a question mark
            id_type local_id{0};
            for (const auto &arg: arguments) {
                auto arg_pair = get_definition(arg);

                // The argument must be new in the function
                if( func_uptr->get_parameter(arg_pair.first) != nullptr )
                    utils::system_error("Parameter " + arg_pair.first + " already exist in function " + func_name,
                                        ERROR_PARSING_DOMAIN);

                // Get the Object Type and check that exists in the domain
                auto obj_type_ptr = dom->get_object_type(arg_pair.second);
                if(obj_type_ptr == nullptr)
                    utils::system_error("Object type " + arg_pair.second + " does not exist", ERROR_PARSING_DOMAIN);

                // Now the parameter can be savely added to the Function
                func_uptr->add_parameter(std::make_unique<Object>(arg_pair.first,local_id++,obj_type_ptr));
            }

            // Once the function is built, now it can be added to the domain
            dom->add_function(std::move(func_uptr));
        }

        static void parse_action(Domain *dom, std::ifstream &ifs){
            std::string word;
            ifs >> word;
            /// Action signature expected - split the signature into name and arguments
            auto sig = get_signature(word);
            auto act_name = sig.first;
            auto arguments = sig.second;

            /// [TYPE]: expected
            process_keyword(ifs, "[TYPE]:", ERROR_PARSING_DOMAIN);
            ifs >> word;
            auto act_type = ActionType::Math;  // set math type by default
            if(word == "memory") act_type = ActionType::Memory;  // set memory type if explicitly said in the action
            else if(word != "math"){  // if it is neither math nor memory, it is a wrong type
                std::cerr << utils::error_message("'math' or 'memory'", word) << "\n";
                utils::system_error("Unexpected action type", ERROR_PARSING_DOMAIN);
            }

            /// After the signature and type, the Action can be created
            auto action = std::make_unique<Action>(act_name, act_type);
            // add its arguments
            for(const auto& arg : arguments) {
                parse_action_argument(dom, action.get(), arg);
            }
            /// [PRECONDITIONS]: expected
            process_keyword(ifs, "[PRECONDITIONS]:", ERROR_PARSING_DOMAIN);

            while(ifs >> word, ifs and word != "[EFFECTS]:"){
                auto expr_vec_str = get_expression(word);  // (lhs_str, op_str, rhs_str)
                if(_valid_conditions.find(expr_vec_str[1]) == _valid_conditions.end())
                    utils::system_error("Condition " + expr_vec_str[1] + " not found when parsing "+ word,
                                        ERROR_PARSING_DOMAIN);
                auto var1(make_variable(expr_vec_str[0], dom, action.get()));
                auto var2 = (make_variable(expr_vec_str[2], dom, action.get()));
                action->add_condition(make_condition(expr_vec_str[1], std::move(var1), std::move(var2)));
            }

            if(word != "[EFFECTS]:")
                utils::system_error("Unexpected keyword " + word + " expected [EFFECTS]:", ERROR_PARSING_DOMAIN);

            while(ifs >> word, ifs and word != "[ACTION]:"){ // next action keyword is a stopping condition
                auto expr_vec_str = get_expression(word);  // (lhs_str, op_str, rhs_str)
                if(_valid_effects.find(expr_vec_str[1]) == _valid_effects.end())
                    utils::system_error("Effect " + expr_vec_str[1] + " not found when parsing "+ word,
                                        ERROR_PARSING_DOMAIN);
                auto var1(make_variable(expr_vec_str[0], dom, action.get()));
                auto var2 = (make_variable(expr_vec_str[2], dom, action.get()));
                action->add_effect(make_effect(expr_vec_str[1], std::move(var1), std::move(var2)));
            }
            dom->add_action(std::move(action));
        }

        static std::unique_ptr<expressions::conditions::Condition> make_goal_condition(Instance *ins, const std::string &word){
            auto expr_vec_str = get_expression(word);  // (lhs_str, op_str, rhs_str)
            if(_valid_conditions.find(expr_vec_str[1]) == _valid_conditions.end())
                utils::system_error("Goal condition operator " + expr_vec_str[1] +
                                    " not found when parsing "+ word,
                                    ERROR_PARSING_INSTANCE);
            if(not is_state_variable(ins, expr_vec_str[0]))
                utils::system_error("The lhs of goal condition " + word + " is not a valid state variable",
                                    ERROR_PARSING_INSTANCE);
            // Pointer checks done in is_state_variable
            auto dom = ins->get_domain();
            auto it = expr_vec_str[0].find('(');
            auto func_str = expr_vec_str[0].substr(0,it);
            auto func_ptr = dom->get_function(func_str);
            auto objs_str = expr_vec_str[0].substr(it+1,expr_vec_str[0].size()-it-2);
            auto objs_vec_str = utils::split(objs_str);
            std::vector<Object*> obj_ptrs;
            for(const auto& o_str : objs_vec_str ){
                obj_ptrs.emplace_back(ins->get_object(o_str));
            }
            // The left-hand side must be a StateVariable
            std::unique_ptr<variables::Variable> lhs= std::make_unique<variables::StateVariable>(func_ptr, obj_ptrs);
            // The right-hand side must be either a ConstantValue or a StateVariable
            std::unique_ptr<variables::Variable> rhs;
            if(utils::is_number(expr_vec_str[2]))
                rhs = std::make_unique<variables::ConstantValue>(utils::str_to_num(expr_vec_str[2]));
            else if(is_state_variable(ins, expr_vec_str[2])){
                it = expr_vec_str[2].find('(');
                func_str = expr_vec_str[2].substr(0,it);
                func_ptr = dom->get_function(func_str);
                objs_str = expr_vec_str[2].substr(it+1,expr_vec_str[0].size()-it-2);
                objs_vec_str = utils::split(objs_str);
                obj_ptrs.clear();
                for(const auto& o_str : objs_vec_str ){
                    obj_ptrs.emplace_back(ins->get_object(o_str));
                }
                rhs = std::make_unique<variables::StateVariable>(func_ptr, obj_ptrs);
            }
            else{
                utils::system_error("The rhs of goal condition " + word +
                                            " is not a valid constant value or state variable",
                                    ERROR_PARSING_INSTANCE);
            }
            return make_condition(expr_vec_str[1], std::move(lhs), std::move(rhs));
        }

        // In charge of parsing and creating a domain
        static bool parse_domain(Domain *dom, const std::string &file_name) {
            std::ifstream ifs(file_name.c_str());
            if (!ifs) utils::system_error("File '" + file_name + "' does not exist.", ERROR_INPUT);
            std::string word;

            /// Parsing domain init (mandatory, just keyword and name)
            process_keyword(ifs, "[DOMAIN]:", ERROR_PARSING_DOMAIN);
            ifs >> word; // domain name
            dom->set_name(word);

            ifs >> word;
            /// (Optional) Parsing Object Types
            if (word == "[TYPES]:") { // TYPES are optional, at least 'object' is inserted by default
                while (ifs >> word, ifs and word != "[CONSTANTS]:" and word != "[FUNCTIONS]:") {
                    parse_object_type(dom, word);
                }
                if (!ifs) {
                    std::cerr << utils::error_message("either [CONSTANTS]: or [FUNCTIONS]:", "END OF FILE") << "\n";
                    return false;
                }
            }
            /// (Optional) Parsing Constants
            if (word == "[CONSTANTS]:") {
                while (ifs >> word, ifs and word != "[FUNCTIONS]:") {
                    parse_constant_object(dom, word);
                }
                if (!ifs) {
                    std::cerr << utils::error_message("[FUNCTIONS]:", "END OF FILE") << "\n";
                    return false;
                }
            }
            /// Parsing Functions (mandatory, at least one)
            if (word != "[FUNCTIONS]:") utils::system_error("Unexpected keyword found: " + word, ERROR_PARSING_DOMAIN);
            bool at_least_one_function = false;
            while (ifs >> word, ifs and word != "[ACTIONS]:") {
                parse_function(dom, word);
                at_least_one_function = true;
            }
            if (not at_least_one_function)
                utils::system_error("No function defined!", ERROR_PARSING_DOMAIN);

            /// Parsing Actions
            // If there are still words to process but the keyword is not "[ACTIONS]:" throw a system error
            if (ifs and word != "[ACTIONS]:") utils::system_error("Unexpected keyword found: " + word, ERROR_PARSING_DOMAIN);
            else if(ifs) { // Otherwise, if the stream is active keep parsing actions
                ifs >> word;
                while (ifs and word == "[ACTION]:") {
                    parse_action(dom, ifs);  // ifs progresses inside parse_action
                }
            }

            // If the stream hasn't finished at this point there could be
            // some errors in the domain, although not very relevant

            return true;
        }


        static void parse_instance(Instance *ins, const std::string &file_name = "") {
            std::ifstream ifs(file_name.c_str());
            if (!ifs) utils::system_error("File '" + file_name + "' does not exist.", ERROR_INPUT);
            std::string word;

            // 1. Parse instance name
            process_keyword(ifs, "[INSTANCE]:", ERROR_PARSING_INSTANCE);
            ifs >> word; // name of the instance
            ins->set_name(word);

            // 2. Parse domain name (checking the name matches)
            process_keyword(ifs, "[DOMAIN]:", ERROR_PARSING_INSTANCE);
            ifs >> word;
            assert(ins->get_domain() != nullptr);
            if(word != ins->get_domain()->get_name())
                utils::system_error("Unknown domain " + word + " expected " + ins->get_domain()->get_name(),
                                    ERROR_PARSING_INSTANCE);

            // 3. Parse objects
            process_keyword(ifs, "[OBJECTS]:", ERROR_PARSING_INSTANCE);
            while (ifs>>word, ifs && word != "[INIT]:")
                parse_instance_object(ins, word);

            // 4. Parse initial state
            if (word != "[INIT]:")
                utils::system_error("Unexpected keyword " + word + " expected [INIT]:",
                                    ERROR_PARSING_INSTANCE);
            auto init_state = std::make_unique<State>();
            while(ifs>>word, ifs && word != "[GOAL]:")
                init_state->add_fact(make_fact(ins, word));
            ins->set_initial_state(std::move(init_state));

            // 5. Parse goal conditions
            if (word != "[GOAL]:")
                utils::system_error("Unexpected keyword " + word + " expected [GOAL]:",
                                    ERROR_PARSING_INSTANCE);
            while(ifs>>word)
                ins->add_goal_condition(make_goal_condition(ins, word));
        }

    private:
        inline static std::set<std::string> _valid_conditions= {">=","<=",">","<","=","+","-","!="};
        inline static std::set<std::string> _valid_effects = {"+=","-=","=","-","=~","&=","|=","^=","<<=",">>="};
        inline static std::string _valid_var_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_?(,)";
    };
}

#endif
