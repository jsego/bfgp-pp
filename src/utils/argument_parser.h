//
// Created by js on 20/05/22.
//

#ifndef __ARGUMENT_PARSER_H__
#define __ARGUMENT_PARSER_H__

#include "./bfgp_utils.h"

namespace utils {
    class ArgumentParser {
    public:
        explicit ArgumentParser(const vec_str_t &input_arguments) :
                _program_lines(0), _infinite_detection(false) {
            std::map<std::string, vec_str_t > arg_map;
            for (size_t i = 0; i < input_arguments.size(); i++) {
                auto arg_type = normalize_arg_type(input_arguments[i++]);

                // Check if the argument type is an unrecognized token
                if (arg_type.empty())
                    helper("Unrecognized argument type: " + input_arguments[i - 1]);

                // Check if the argument value is not filled
                if (i >= input_arguments.size())
                    helper("Expected value after argument type " + arg_type);

                // Check if the argument type has been repeated
                if (arg_map.find(arg_type) != arg_map.end())
                    helper("Inconsistent input. Repeated argument type: " + arg_type);

                // Otherwise, add corresponding values
                vec_str_t values;
                while (i < input_arguments.size()) {
                    assert(!input_arguments[i].empty()); // This must never happen
                    if (input_arguments[i][0] == '-') {
                        i--;
                        break;
                    } // Break if it is another argument type
                    values.emplace_back(input_arguments[i++]);
                }
                if (values.empty())
                    helper("Missing values for argument type " + arg_type);
                arg_map[arg_type] = values;
            }

            if (arg_map.find(_help_ntype) != arg_map.end())
                helper(); // call the helper and end execution if it is in the list of arguments

            auto it_mode = arg_map.find(_mode_ntype);
            if (it_mode == arg_map.end())
                helper("Mode is required.");
            if (it_mode->second.size() != 1u)
                helper("Exactly one value expected for mode but " + std::to_string(it_mode->second.size()) + " found.");
            if (_valid_modes.find(it_mode->second[0]) == _valid_modes.end())
                helper("The mode \"" + it_mode->second[0] + "\" is invalid.");

            if (it_mode->second[0] == "synthesis") {
                parse_synthesis_arguments(arg_map); // ToDo: this must be an argument option
                // Set global vars
                _max_val = 100;
            }
            else if (it_mode->second[0] == "validation-prog" or it_mode->second[0] == "validation-cpp") {
                parse_validation_arguments(arg_map);
                // Set global vars
                _max_val = 1000000000;
            }
            else helper("Unreachable code, since mode is found to be valid.");

            _carry_flag = (get_theory_name() != "bitvec");  // It is only false if the theory is "bitvec"


        }

        ~ArgumentParser() = default;

        // Generalize to synthesizer and validators
        static void helper(const std::string &error_message = "", int error_code = ERROR_INPUT) {
            std::string help_str =
                    "Structured Programming helper:\n\n"
                    "usage template: ./main.bin [argument options]\n\n"
                    "argument options:\n"
                    "  " + _help_stype + ", " + _help_type + "   shows this message help and exit\n"
                                                             "  " + _mode_stype + ", " + _mode_type +
                    " {synthesis, validation-prog, validation-cpp}   exactly one required parameter:\n"
                    "      synthesis: computes a planning program\n"
                    "      validation-prog: interprets an input program and validates it on a set of instances\n"
                    "      validation-cpp: parses a program and translates it to c++ code, and validates it on a set of instances\n"
                    "  " + _program_lines_stype + ", " + _program_lines_type +
                    " PROGRAM_LINES   required in \"synthesis\" mode; "
                    "type: strictly positive integer\n"
                    "  " + _problem_folder_stype + ", " + _problem_folder_type +
                    " PROBLEM_DIR/   required in all modes;"
                    " PROBLEM_DIR/ is a directory to a domain.txt and "
                    "numbered instances 1.txt to [n].txt\n"
                    "  " + _theory_stype + ", " + _theory_type + " {assembler, cpp, bitvec, actions_strips, actions_adl, actions_cell, actions_ram}   available in all modes;"
                                                                 " it loads a theory of instructions that builds the program grammar;"
                                                                 " default: cpp\n"
                                                                 "  " + _eval_func_stype + ", " + _eval_func_type +
                    " [{lc, ilc, ed, mnl, mll, llc, ac, astar, wastar}]   only available in \"synthesis\" mode; "
                    "list of functions to evaluate nodes in the search; "
                    "default: [ed, ilc]\n"
                    "      lc (loop counter): minimize the number of loops in the program\n"
                    "      ilc (inverse loop counter): maximize the number of loops in the program\n"
                    "      ed (euclidean distance): euclidean distance from last state after executing the program to goal condition\n"
                    "      cwed (closed-world euclidean distance): euclidean distance assuming the goal is a state\n"
                    "      hd (hamming distance): hamming distance from last state after executing the program to goal condition\n"
                    "      chd (closest hamming distance): min hamming distance from each state in the resulting trace of executing the program to goal condition\n"
                    "      jd (jaccard distance): jaccard distance from last state after executing the program to goal condition\n"
                    "      nei (number of empty instructions): counts the number of empty instructions in a program\n"
                    "      mri (min repeated instructions): returns the max number of instruction occurrences in a program\n"
                    "      mnl (max nested loops): largest loop nesting in the program\n"
                    "      mll (max loop lines): maximize the number of covered lines in the program by loops\n"
                    "      llc (loop line counter): maximize the sum of all loop sizes in the program\n"
                    "      lmc (landmark counter): count the number of unachieved landmarks during program execution\n"
                    "      mi (max ifs): maximize the number of IF instructions\n"
                    "      ac (accumulated cost): sum of all applied instructions\n"
                    "      astar (ed+ac): euclidean plus accumulated cost in an A* fashion\n"
                    "      wastar (5*ed+ac): weighted euclidean plus accumulated cost in an WA* fashion, default w=5\n"
                    "  " + _program_stype + ", " + _program_type +
                    " PROGRAM_FILE.prog   required in \"validation-*\" modes\n"
                    "  " + _infinite_detection_stype + ", " + _infinite_detection_type +
                    " INFINITE_DETECTION   available in \"validation-prog\" mode;"
                    " detects duplicate states in the program validation;"
                    " type: boolean (True, False; true, false; 1, 0);"
                    " default: false\n"
                    "  " + _progressive_stype + ", " + _progressive_type + " PROGRESSIVE  available in \"synthesis\" mode;"
                    " activates input instances progressively, where tentative solutions fails; "
                    " type: boolean (True, False; true, false; 1, 0);"
                    " default: false\n"
                    "  " + _verbosity_stype + ", " + _verbosity_type + " for verbose output; type: boolean"
                    " (True, False; true, false; 1, 0); default: false\n\n"
                    "usage examples:\n"
                    "1. Synthesis: ./main.bin -m synthesis -l 5 -f domains/synthesis/triangular-sum/\n"
                    "2. Program validation: ./main.bin -m validation-prog -f domains/synthesis/triangular-sum/ -p experiments/synthesis/triangular-sum/triangular-sum_5_ed_ilc.prog\n"
                    "3. C++ program validation: ./main.bin -m validation-cpp -f domains/synthesis/triangular-sum/ -p experiments/synthesis/triangular-sum/triangular-sum_5_ed_ilc.prog\n";
            // It is just printing the helping message
            if (error_message.empty()) {
                std::cout << help_str << "\n";
                exit(error_code);
            }
            // Some input error occurred
            utils::system_error(error_message + "\n\n" + help_str, error_code);
        }

        void parse_synthesis_arguments(const std::map<std::string, vec_str_t > &arg_map) {
            for (const auto &m: arg_map) {
                auto arg_type = m.first;
                auto arg_vals = m.second;
                if (arg_type == _mode_ntype)
                    parse_mode(arg_vals[0]); // previously checked that only contains 1 value
                else if (arg_type == _program_lines_ntype) {
                    if (arg_vals.size() != 1u)
                        helper("Exactly one value for program lines expected but " +
                                std::to_string(arg_vals.size()) +" found.");
                    parse_program_lines(arg_vals[0]);
                } else if (arg_type == _problem_folder_ntype) {
                    if (arg_vals.size() != 1u)
                        helper("Exactly one problem folder expected but " +
                                std::to_string(arg_vals.size()) + " found.");
                    parse_problem_folder(arg_vals[0]);
                } else if (arg_type == _eval_func_ntype)
                    parse_evaluation_functions(arg_vals);
                else if (arg_type == _theory_ntype)
                    parse_theory(arg_vals);
                else if (arg_type == _num_extra_pointers_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one integer expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_num_extra_pointers(arg_vals[0]);
                }
                else if(arg_type == _progressive_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one boolean expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_progressive(arg_vals[0]);
                }
                else if(arg_type == _output_file_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one output file expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_output_file(arg_vals[0]);
                }
                else if(arg_type == _verbosity_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one boolean expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_verbosity(arg_vals[0]);
                }
                // Check if the argument type is an unrecognized token
                else helper("Unrecognized input token: " + arg_type);
            }

            // Check if required arguments are filled
            if (arg_map.find(_program_lines_ntype) == arg_map.end())
                helper("Program lines are required.");
            if (arg_map.find(_problem_folder_ntype) == arg_map.end())
                helper("Problem folder is required.");

            // Set default values for the rest if not filled by command line
            if (arg_map.find(_theory_ntype) == arg_map.end())
                _theory_name = "cpp";
            if (arg_map.find(_eval_func_ntype) == arg_map.end()) {
                if (_theory_name == "bitvec") _evaluation_function_names = {"mri", "hd"};
                else _evaluation_function_names = {"ed", "ilc"};
            }
            if(arg_map.find(_num_extra_pointers_ntype) == arg_map.end())
                _num_extra_pointers = 0;
            if(arg_map.find(_progressive_ntype) == arg_map.end())
                _progressive = false;
            if(arg_map.find(_verbosity_ntype) == arg_map.end())
                _verbose = false;
        }

        void parse_validation_arguments(const std::map<std::string, vec_str_t > &arg_map) {
            for (const auto &m: arg_map) {
                auto arg_type = m.first;
                auto arg_vals = m.second;
                if (arg_type == _mode_ntype) {
                    parse_mode(arg_vals[0]);
                } else if (arg_type == _program_ntype) {
                    if (arg_vals.size() != 1u)
                        helper("Only one program expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_program(arg_vals[0]);
                } else if (arg_type == _problem_folder_ntype) {
                    if (arg_vals.size() != 1u)
                        helper("Only one problem folder expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_problem_folder(arg_vals[0]);
                } else if (arg_type == _theory_ntype) {
                    parse_theory(arg_vals);
                } else if (arg_type == _infinite_detection_ntype) {
                    if (arg_vals.size() != 1u)
                        helper("Only one value expected for infinite detection but " + std::to_string(arg_vals.size()) +
                               " found.");
                    parse_infinite_detection(arg_vals[0]);
                }
                else if (arg_type == _num_extra_pointers_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one integer expected but " +
                               std::to_string(arg_vals.size()) + " found.");
                    parse_num_extra_pointers(arg_vals[0]);
                }
                else if(arg_type == _verbosity_ntype){
                    if(arg_vals.size() != 1u)
                        helper("Exactly one boolean expected but " + std::to_string(arg_vals.size()) + " found.");
                    parse_verbosity(arg_vals[0]);
                }
                // Check if the argument type is an unrecognized token
                else helper("Unrecognized input token: " + arg_type);
            }

            // Check if required arguments are filled
            if (arg_map.find(_program_ntype) == arg_map.end())
                helper("Program is required.");
            if (arg_map.find(_problem_folder_ntype) == arg_map.end())
                helper("Problem folder is required.");

            // Set default values for the rest if not filled by command line
            if (arg_map.find(_theory_ntype) == arg_map.end())
                _theory_name = "cpp";
            if (arg_map.find(_infinite_detection_ntype) == arg_map.end())
                _infinite_detection = false;
            if(arg_map.find(_num_extra_pointers_ntype) == arg_map.end())
                _num_extra_pointers = 0;
            if(arg_map.find(_verbosity_ntype) == arg_map.end())
                _verbose = false;

            // Parse from _program_file_name the number of _program_lines
            _program_lines = utils::count_non_empty_file_lines(_program_file_name);

            // Parse from _program_file_name the list of evaluation functions
            std::vector<std::pair<size_t, std::string> > pos_eval_funcs;
            for (const auto &ef: _valid_evaluation_functions) {
                auto it = _program_file_name.find("_" + ef);
                if (it != std::string::npos)
                    pos_eval_funcs.emplace_back(std::make_pair(it, ef));
            }
            sort(pos_eval_funcs.begin(), pos_eval_funcs.end());
            for (const auto &pef: pos_eval_funcs)
                _evaluation_function_names.emplace_back(pef.second);
        }

        void parse_mode(const std::string &mode) {
            _mode = mode;
        }

        void parse_program(const std::string &program_file_name) {
            _program_file_name = program_file_name;
            if (_program_file_name.size() <= 5u)
                helper("Program file name " + _program_file_name + " is too short.", ERROR_PROGRAM_DOES_NOT_EXIST);
            auto pos = _program_file_name.find_last_of('.');
            if (pos == std::string::npos)
                helper("Program file name extension not found but it must be .prog");
            if (_program_file_name.substr(pos) != ".prog")
                helper("Program file name extension must be .prog but " + _program_file_name.substr(pos) + " found.");
            if (!std::filesystem::exists(_program_file_name))
                helper("Program file " + _program_file_name + " does not exist.", ERROR_PROGRAM_DOES_NOT_EXIST);
        }

        void parse_problem_folder(const std::string &problem_folder) {
            _problem_folder = problem_folder;
            // Checking input type is a valid directory
            if (!std::filesystem::exists(_problem_folder))
                helper("Wrong input. The problem folder \"" + _problem_folder + "\" is not a valid path.");
        }

        void parse_theory(const vec_str_t &theories) {
            // Current version (obsolete in near future)
            _theory_name = theories[0];
            if (_valid_theories.find(_theory_name) == _valid_theories.end())
                helper("Wrong input. The theory \"" + _theory_name + "\" is not valid.");

            // ToDo: In future iterations we may have orthogonal theories that may be combined
            //  but in the current version we just use a predefined built theory
            /*
            for(const auto &theory_name : theories){
                if(_valid_theories.find(theory_name) == _valid_theories.end())
                    helper("Theory \"" + theory_name + "\" does not exist.");
                // Add a valid theory name to the list
                _theories.emplace_back(theory_name);
            }
            */
        }

        void parse_program_lines(const std::string &str_program_lines) {
            // Checking input type is a valid number
            if(not utils::is_number(str_program_lines))
                helper("Wrong input format. The input program lines " + str_program_lines + " is not a number.");
            _program_lines = utils::str_to_num(str_program_lines);
        }

        void parse_num_extra_pointers(const std::string &str_num_extra_pointers){
            // Checking input type is a valid number
            if(not utils::is_number(str_num_extra_pointers))
                helper("Wrong input format. The input number of extra pointers " + str_num_extra_pointers +
                        " is not a number.");
            _num_extra_pointers = utils::str_to_num(str_num_extra_pointers);
        }

        void parse_evaluation_functions(const vec_str_t &eval_funcs) {
            for (const auto &eval_func_name: eval_funcs) {
                if (_valid_evaluation_functions.find(eval_func_name) == _valid_evaluation_functions.end())
                    helper("Evaluation function \"" + eval_func_name + "\" does not exist.");
                // Add a valid func name to the list
                _evaluation_function_names.emplace_back(eval_func_name);
            }
        }

        void parse_infinite_detection(const std::string &str_infinite_detection) {
            auto it = _valid_boolean.find(str_infinite_detection);
            if (it == _valid_boolean.end())
                helper("Expected boolean value for infinite detection but " + str_infinite_detection + " found.");
            _infinite_detection = it->second;
        }

        void parse_progressive(const std::string &str_progressive){
            auto it = _valid_boolean.find(str_progressive);
            if (it == _valid_boolean.end())
                helper("Expected boolean value for PGP but " + str_progressive + " found.");
            _progressive = it->second;
        }

        void parse_output_file(const std::string &str_output_file){
            _output_file = str_output_file;
            // if (!std::filesystem::exists(_output_file))  // do not check whether it exists
            //    helper("Wrong input. The output file \"" + _output_file + "\" is not a valid path.");
        }

        void parse_verbosity(const std::string &str_verbosity){
            auto it = _valid_boolean.find(str_verbosity);
            if (it == _valid_boolean.end())
                helper("Expected boolean value for verbose argument but " + str_verbosity + " found.");
            _verbose = it->second;
        }

        [[nodiscard]] std::string get_mode() const {
            return _mode;
        }

        [[nodiscard]] std::string get_program_file_name() const {
            return _program_file_name;
        }

        [[nodiscard]] int get_program_lines() const {
            return _program_lines;
        }

        [[nodiscard]] std::string get_problem_folder() const {
            return _problem_folder;
        }

        [[nodiscard]] vec_str_t get_evaluation_function_names() const {
            return _evaluation_function_names;
        }

        [[nodiscard]] bool is_evaluation_function_selected(const std::string& name) const{
            return std::any_of(_evaluation_function_names.begin(),
                               _evaluation_function_names.end(),
                               [&name](const std::string& ef) {return ef==name;});
        }

        [[nodiscard]] std::string get_theory_name() const {
            return _theory_name;
        }

        [[nodiscard]] bool get_infinite_detection() const {
            return _infinite_detection;
        }

        [[nodiscard]] bool get_carry_flag() const{
            return _carry_flag;
        }

        [[nodiscard]] value_t get_max_val() const{
            return _max_val;
        }

        [[nodiscard]] int get_num_extra_pointers() const{
            return _num_extra_pointers;
        }

        [[nodiscard]] bool is_progressive() const{
            return _progressive;
        }

        [[nodiscard]] std::string get_output_file() const{
            return _output_file;
        }

        [[nodiscard]] bool is_verbose() const{
            return _verbose;
        }

    private:
        [[nodiscard]] static std::string normalize_arg_type(const std::string &arg_type) {
            if (arg_type == _help_type or arg_type == _help_stype) return _help_ntype;
            if (arg_type == _mode_type or arg_type == _mode_stype) return _mode_ntype;
            if (arg_type == _program_type or arg_type == _program_stype) return _program_ntype;
            if (arg_type == _program_lines_type or arg_type == _program_lines_stype) return _program_lines_ntype;
            if (arg_type == _problem_folder_type or arg_type == _problem_folder_stype) return _problem_folder_ntype;
            if (arg_type == _eval_func_type or arg_type == _eval_func_stype) return _eval_func_ntype;
            if (arg_type == _theory_type or arg_type == _theory_stype) return _theory_ntype;
            if (arg_type == _infinite_detection_type or arg_type == _infinite_detection_stype)
                return _infinite_detection_ntype;
            if (arg_type == _num_extra_pointers_type or arg_type == _num_extra_pointers_stype)
                return _num_extra_pointers_ntype;
            if (arg_type == _progressive_type or arg_type == _progressive_stype) return _progressive_ntype;
            if (arg_type == _output_file_type or arg_type == _output_file_stype) return _output_file_ntype;
            if (arg_type == _verbosity_type or arg_type == _verbosity_stype) return _verbosity_ntype;
            return _unrecognized_token;
        }

        /// Accessible data-structures
        std::string _mode; // required in all modes
        std::string _problem_folder; // required in all modes
        vec_str_t _evaluation_function_names; // optional for synthesis only (default: [ed, ilc])
        std::string _theory_name; // optional for synthesis only (default: cpp)
        size_t _program_lines; // required in synthesis but used in both (in validation mode is inferred from the program)
        std::string _program_file_name; // required in any validation mode
        bool _infinite_detection; // optional for validation-prog mode (default: false)
        bool _carry_flag;
        value_t _max_val;
        int _num_extra_pointers;  // number of extra pointers per argument type
        bool _progressive; // optional for synthesis only (default: false)
        std::string _output_file;  // optional for synthesis only (default: "")
        bool _verbose; // optional verbose output

        /// Constant argument types (requires C++17)
        inline static const std::string _unrecognized_token = ""; // default value for unrecognized tokens
        inline static const std::string _help_type = "--help";
        inline static const std::string _help_stype = "-h"; // short type
        inline static const std::string _help_ntype = "help"; // normalized type
        inline static const std::string _mode_type = "--mode";
        inline static const std::string _mode_stype = "-m"; // short type
        inline static const std::string _mode_ntype = "mode"; // normalized type
        inline static const std::string _program_lines_type = "--program-lines";
        inline static const std::string _program_lines_stype = "-l"; // short type
        inline static const std::string _program_lines_ntype = "program_lines"; // normalized type
        inline static const std::string _problem_folder_type = "--problem-folder";
        inline static const std::string _problem_folder_stype = "-f"; // short type
        inline static const std::string _problem_folder_ntype = "problem_folder"; // normalized type
        inline static const std::string _eval_func_type = "--evaluation-functions";
        inline static const std::string _eval_func_stype = "-e"; // short type
        inline static const std::string _eval_func_ntype = "evaluation_functions"; // normalized type
        inline static const std::string _theory_type = "--theory";
        inline static const std::string _theory_stype = "-t"; // short type
        inline static const std::string _theory_ntype = "theory"; // normalized type
        inline static const std::string _program_type = "--program";
        inline static const std::string _program_stype = "-p"; // short type
        inline static const std::string _program_ntype = "program"; // normalized type
        inline static const std::string _progressive_type = "--progressive";
        inline static const std::string _progressive_stype = "-pgp"; // short type
        inline static const std::string _progressive_ntype = "progressive"; // normalized type
        inline static const std::string _infinite_detection_type = "--infinite-detection";
        inline static const std::string _infinite_detection_stype = "-inf"; // short type
        inline static const std::string _infinite_detection_ntype = "infinite_detection"; // normalized type
        inline static const std::string _num_extra_pointers_type = "--num-extra-pointers";
        inline static const std::string _num_extra_pointers_stype = "-s"; // short type
        inline static const std::string _num_extra_pointers_ntype = "num_extra_pointers"; // normalized type
        inline static const std::string _output_file_type = "--output-file";
        inline static const std::string _output_file_stype = "-o"; // short type
        inline static const std::string _output_file_ntype = "output_file"; // normalized type
        inline static const std::string _verbosity_type = "--verbosity";
        inline static const std::string _verbosity_stype = "-v"; // short type
        inline static const std::string _verbosity_ntype = "verbosity"; // normalized type

        /// Constant argument values (requires C++17)
        inline static const std::set<std::string> _valid_modes = {"synthesis", "validation-prog", "validation-cpp"};
        inline static const std::set<std::string> _valid_evaluation_functions = {"lc", "ed", "hd", "chd", "jd", "nei",
                                                                                 "mri", "mnl", "mll", "llc", "ilc",
                                                                                 "lmc", "hmax", "hadd", "mi", "cwed",
                                                                                 "ac", "dll", "astar", "wastar"};
        inline static const std::set<std::string> _valid_theories = {"assembler", "cpp", "bitvec", "actions_strips",
                                                                     "actions_adl", "actions_cell", "actions_ram"};
        inline static const std::map<std::string, bool> _valid_boolean = {{"True", true},
                                                                          {"true", true},
                                                                          {"1", true},
                                                                          {"False", false},
                                                                          {"false", false},
                                                                          {"0", false},};
    };
}
#endif //__ARGUMENT_PARSER_H__
