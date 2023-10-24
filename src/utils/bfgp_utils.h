//
// Created by js on 22/05/22.
//

#ifndef __BFGP_UTILS_H__
#define __BFGP_UTILS_H__

#include "common.h"

namespace utils{
    ///******* INPUT ARGUMENTS METHODS *********
    vec_str_t input_arguments_to_strings(int argc, const char* argv[]){
        vec_str_t str_args;
        for(int i=1; i<argc; i++)
            str_args.emplace_back(std::string(argv[i]));
        return str_args;
    }

    ///******* ERROR METHODS *********
    void system_error(const std::string &message, int code_error = ERROR_INPUT){
        std::cout << "[ERROR] " << message << "\n";
        exit(code_error);
    }

    ///******* CHRONO METHODS *********
    std::chrono::time_point<std::chrono::system_clock> get_time(){
        return std::chrono::system_clock::now();
    }

    /// Precision up to 3 digits
    double seconds_ellapsed(const std::chrono::time_point<std::chrono::system_clock> &start_time,
                            const std::chrono::time_point<std::chrono::system_clock> &end_time){
        return double(std::chrono::duration_cast<std::chrono::milliseconds>(end_time-start_time).count())/1000.0;
    }

    /// Precision up to 3 digits
    std::string print_time(double t){
        std::stringstream sstr;
        sstr << std::fixed << std::setprecision(3) << t;
        return "["+ sstr.str()+"s]";
    }

    ///******* STRINGS, FILES & FOLDERS METHODS *********
    /// Split a string by delim and return all non-empty chuncks
    vec_str_t split(const std::string &s, const std::string &delim  = "," ){
        if(s.empty()) return {};
        vec_str_t vs;
        size_t pos, last_pos=0;
        while( (pos=s.find_first_of(delim, last_pos)) != std::string::npos){
            if(pos>last_pos) vs.emplace_back(s.substr(last_pos, pos-last_pos));
            else vs.emplace_back(std::string()); // emplace empty string, potentially relevant to the caller
            last_pos = pos+delim.size();
        }
        if(last_pos != std::string::npos) vs.emplace_back(s.substr(last_pos));
        return vs;
    }

    /// Join a pair of strings by another string
    std::string join(const std::pair<std::string,std::string> &pss, const std::string &mid=""){
        return pss.first + mid + pss.second;
    }

    /// Join a vector of strings by another string
    std::string join(const vec_str_t &v, const std::string &mid=""){
        std::string s;
        for(size_t i=0; i<v.size(); i++)
            s += (i?mid:"") + v[i];
        return s;
    }

    /// Print string to a file
    void print_to_file(const std::string &file_name, const std::string &s){
        std::ofstream ofs(file_name);
        if(!ofs) system_error("When creating " + file_name);
        ofs << s << "\n";
        ofs.close();
    }


    /// Get the list of subfolders to be created for the experiment
    std::pair<std::string,std::string> create_experiments_file_subdirectory(
            std::string out_file,
            const std::string& orig_problem_folder,
            int program_lines,
            const vec_str_t &evaluation_functions){

        std::string out_folder = "experiments/";

        // If the output file is specified
        if(not out_file.empty()){
            auto problem_folders = split(out_file, "/");  // last is the output file
            out_folder = "";
            int is_last_file = (out_file[out_file.size()-1]=='/'?0:1);
            for(size_t idx=0; idx+is_last_file<problem_folders.size(); ++idx)
                out_folder += problem_folders[idx]+"/";
            out_file = problem_folders[problem_folders.size()-1];
        }
        else{ // Otherwise, set up a default output folder and file
            auto problem_subfolders = split(orig_problem_folder, "/"); // last subfolder expected to be an empty string
            if(!problem_subfolders.empty()){
                // Add all intermediate folders
                for(size_t idx=1; idx+2<problem_subfolders.size(); idx++)
                    out_folder += problem_subfolders[idx] + "/";
            }
            // Add settings info to the out_file name, e.g. program lines and evaluation functions
            assert(problem_subfolders.size()>1u);  // At least expected "domains/[...]/subfolder/" for a problem
            out_file = problem_subfolders[problem_subfolders.size()-2];
            out_file += "_" + std::to_string(program_lines);
            for(const auto &efn : evaluation_functions)
                out_file += "_" + efn;
        }

        if((not out_folder.empty()) and (not std::filesystem::exists(out_folder))){
            std::filesystem::create_directories(out_folder);
        }

        return std::make_pair(out_folder, out_file);
    }

    // ToDo: do it generic line reader
    /// Read all non-empty lines of a file
    vec_str_t read_program_instructions(const std::string &program_file_name){
        std::ifstream ifs_program( program_file_name );
        assert( ifs_program ); // This is already verified by the argument parser
        vec_str_t program_instructions;
        std::string instruction;
        while( getline( ifs_program, instruction ) ){
            if( instruction.empty() ) continue;
            instruction = instruction.substr( instruction.find_first_of( ". " ) + 2 );
            program_instructions.push_back( instruction );
        }
        ifs_program.close();
        return program_instructions;
    }

    /// Count the number of non-empty lines in a file
    int count_non_empty_file_lines(const std::string &file_name){
        if(!std::filesystem::exists(file_name)) return 0;
        std::ifstream ifs_input_file(file_name);
        std::string line;
        int total_lines = 0;
        while(getline(ifs_input_file, line)){
            if(!line.empty()) total_lines++;
        }
        return total_lines;
    }

    std::string error_message(const std::string &expected_word = "", const std::string &readed_word = "") {
        return "Expected ''" + expected_word + "'' but ''" + readed_word + "'' read.";
    }

    bool is_number(const std::string &s ) {
        /// Check whether string s is a integer
        size_t pos = (!s.empty() and s[0] == '-'?1:0); // check if the number is negative
        return (s.find_first_not_of("0123456789",pos) == std::string::npos );
    }

    value_t str_to_num(const std::string &s){
        /// Map a string to a number (for sanity check, call is_number(s) before)
        std::istringstream iss(s);
        value_t res;
        iss >> res;
        return res;
    }

    vec_str_t read_file(const std::string &filename){
        /// Read a file and return all its lines as a vector of strings
        std::ifstream ifs(filename.c_str());
        assert(ifs);
        std::string word;
        vec_str_t ret;
        while(getline(ifs, word)){
            ret.emplace_back(word);
        }
        return ret;
    }

}

#endif //__BFGP_UTILS_H__
