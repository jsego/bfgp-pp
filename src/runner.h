//
// Created by js on 23/05/22.
//
#ifndef __RUNNER_H__
#define __RUNNER_H__

#include "utils/bfgp_utils.h"
#include "utils/argument_parser.h"
#include "generalized_domain.h"
#include "generalized_planning_problem.h"
#include "stats_info.h"
#include "factory_methods.h"
#include "program_translator.h"

namespace runner{
    void synthesis( std::unique_ptr<utils::ArgumentParser> arg_parser,
                    std::unique_ptr<GeneralizedPlanningProblem> gpp,
                    std::unique_ptr<StatsInfo> stats_info ){
        // Build the search engine as a Best-First Search bounded by program lines with
        // the corresponding generalized domain and problem
        auto th_name = arg_parser->get_theory_name();
        if( th_name.size() > 8u and th_name.substr(0,8) == "actions_" ){
            gpp->activate_actions_theory();
        }
        if(arg_parser->is_progressive()){
            gpp->set_progressive(true);
            for(size_t instance_id = 1; instance_id < gpp->get_num_instances(); ++instance_id)
                gpp->deactivate_instance(instance_id);
        }
        auto mode_name = arg_parser->get_mode();
        std::vector<std::unique_ptr<Program>> programs;
        if(mode_name == "repair"){ // TODO: add flexible & fixed repair modes, to get all or one root program
            programs = factories::make_programs(arg_parser.get(), gpp.get(), true);
            if((int)programs[programs.size()-1]->get_num_instructions() != arg_parser->get_program_lines())
                arg_parser->helper("The input program and the input number of program lines differ");
        }

        auto engine = factories::make_engine(arg_parser.get(), std::move(gpp));
        stats_info->add_timer("engine");
        stats_info->timers_info("Engine created.", "gpp", "engine");
        stats_info->add_info_msg("Searching...");

        // Call the engine solver to search for a generalized plan (or program)
        auto resulting_node = engine->solve(std::move(programs));
        stats_info->add_timer("search");

        auto output_file = arg_parser->get_output_file();
        auto dest_folder_file =
                utils::create_experiments_file_subdirectory(
                        output_file,
                        arg_parser->get_problem_folder(),
                        arg_parser->get_program_lines(),
                        arg_parser->get_evaluation_function_names());
        auto dest_file_name = utils::join(dest_folder_file);

        if(resulting_node != nullptr ){
            auto resulting_program = resulting_node->get_program();
            utils::print_to_file(dest_file_name+".prog", resulting_program->to_string(false));
            stats_info->add_info_msg("SOLUTION FOUND!!!\n" + resulting_program->to_string(false));
        }
        else{
            stats_info->add_info_msg("SOLUTION NOT FOUND :(");
        }
        stats_info->add_info_msg("Number of instances: " +
                                 std::to_string(engine->get_generalized_planning_problem()->get_num_instances()));
        stats_info->add_info_msg("Expanded: " + std::to_string(engine->get_expanded()));
        stats_info->add_info_msg("Evaluated: " + std::to_string(engine->get_evaluated()));
        if(resulting_node != nullptr) {
            stats_info->add_info_msg(
                    "Total plan costs: " + std::to_string(resulting_node->get_program()->get_total_plan_costs()));
            stats_info->add_info_msg("Total number of instructions: " +
                                     std::to_string(resulting_node->get_program()->get_num_of_steps()));
        }
        stats_info->timers_info("Search time:", "engine", "search");
        stats_info->timers_info("Total time:", "start", "search");
        if(resulting_node != nullptr ) stats_info->add_info_msg("Program file: " + dest_file_name + ".prog");
        stats_info->add_info_msg("Experiments file: " + dest_file_name + ".out");

        utils::print_to_file(dest_file_name+".out", stats_info->get_all_info());
    }



    void run_program(Program *prog,
                     GeneralizedPlanningProblem *gpp,
                     StatsInfo *stats_info,
                     std::string dest_file_name = "",
                     bool save_pddl_plans = false){
        auto vps = prog->run( gpp, save_pddl_plans );

        if(save_pddl_plans){
            if((not dest_file_name.empty()) and (dest_file_name[dest_file_name.size()-1] != '/'))
                dest_file_name += ".";
            for(size_t instance_id = 1; instance_id <= gpp->get_num_instances(); instance_id++){
                std::ofstream ofs(dest_file_name + "plan." + std::to_string(instance_id));
                for(const auto& str_act : prog->get_plan(instance_id))
                    ofs << str_act << "\n";
                ofs.close();
            }
        }
        stats_info->add_info_msg("Number of instances: " + std::to_string(gpp->get_num_instances()));
        bool all_goals = false;
        if(!vps.empty()) {
            assert(vps.size() == gpp->get_num_instances());
            all_goals = true;
            int error = 0;
            for (size_t idx = 0; idx < gpp->get_num_instances(); ++idx) {
                all_goals &= prog->is_goal(vps[idx], gpp->get_instance(idx), error);
            }
        }
        if(all_goals) stats_info->add_info_msg("GOAL ACHIEVED!");
        else stats_info->add_info_msg("INVALID GENERAL PLAN :(");
    }

    void generate_cpp_code(GeneralizedPlanningProblem *gpp,
                           Program* p,
                           const std::string &dest_folder,
                           const std::string &dest_file_name,
                           StatsInfo *stats_info,
                           utils::ArgumentParser *arg_parser) {
        /// Generate CPP code from a .prog file, a domain and a set of instances
        stats_info->add_timer("cpp_translator_starts");
        auto prog_translator = std::make_unique<ProgramTranslator>(gpp, p->get_instructions(), arg_parser);
        utils::print_to_file(dest_folder+dest_file_name+".cpp", prog_translator->to_string());

        /// Generate init and goal data
        prog_translator->generate_input_data(dest_folder );

        stats_info->add_timer("cpp_translator_ends");
        stats_info->timers_info("CPP translator time: ", "cpp_translator_starts", "cpp_translator_ends");
    }

    void compile_cpp_code(const std::string &dest_file_name,
                          StatsInfo *stats_info) {
        /// Compile the CPP code
        stats_info->add_timer("compile_starts");
        std::string command = "g++ -Wall -O3 -std=c++17 " + dest_file_name + ".cpp -o " + dest_file_name + ".bin";
        stats_info->add_info_msg("Executing: " + command);

        auto compiler_ret = std::system(command.c_str());
        if (compiler_ret != 0) utils::system_error("Compilation error " + std::to_string(compiler_ret));

        stats_info->add_timer("compile_ends");
        stats_info->timers_info("Compilation succeeded: ", "compile_starts", "compile_ends");
    }

    void execute_cpp_code(
            GeneralizedPlanningProblem *gpp,
            const std::string &dest_folder,
            const std::string &dest_file_name,
            StatsInfo *stats_info){
        /// Execute the program
        std::vector<bool> goal_achieved;
        std::vector<double> ins_exec_times;
        for(size_t i =1; i <= gpp->get_num_instances(); i++){
            stats_info->add_timer("exec_starts");

            auto command = "./"+dest_file_name+".bin ";
            command += dest_folder+"init_"+std::to_string(i)+".txt ";
            command += dest_folder+"goal_"+std::to_string(i)+".txt";
            stats_info->add_info_msg("Executing: " + command);

            auto exec_ret = std::system(command.c_str());

            stats_info->add_timer("exec_ends");
            if(exec_ret != 0){
                stats_info->timers_info("Instance #"+std::to_string(i)+" failed: ", "exec_starts", "exec_ends");
                goal_achieved.emplace_back(false);
            }
            else {
                stats_info->timers_info("Instance #"+std::to_string(i)+" succeeded: ", "exec_starts", "exec_ends");
                goal_achieved.emplace_back(true);
            }
            ins_exec_times.emplace_back(stats_info->get_seconds("exec_starts", "exec_ends"));
        }
        if(std::all_of(goal_achieved.begin(),goal_achieved.end(), [](bool b) { return b; }))
            stats_info->add_info_msg("ALL GOALS ACHIEVED! :-)");
        else stats_info->add_info_msg("INVALID GENERAL PLAN :-(");

        // Computing average
        double accumulated_times_avg = std::accumulate(ins_exec_times.begin(), ins_exec_times.end(),0.0)/double(ins_exec_times.size());
        stats_info->add_info_msg("Avg. time "+utils::print_time(accumulated_times_avg));

        // Computing standard deviation
        double accumulated_times_std_dev = 0.0;
        for( const auto &v : ins_exec_times )
            accumulated_times_std_dev += (v-accumulated_times_avg)*(v-accumulated_times_avg);
        accumulated_times_std_dev /= ins_exec_times.size();
        accumulated_times_std_dev = std::sqrt(accumulated_times_std_dev);
        stats_info->add_info_msg("Standard deviation time "+utils::print_time(accumulated_times_std_dev));
    }

    void validation( std::unique_ptr<utils::ArgumentParser> arg_parser,
                     std::unique_ptr<GeneralizedPlanningProblem> gpp,
                     std::unique_ptr<StatsInfo> stats_info){
        auto dest_folder_file =
                utils::create_experiments_file_subdirectory(arg_parser->get_output_file(),
                                                            arg_parser->get_problem_folder(),
                                                            arg_parser->get_program_lines(),
                                                            arg_parser->get_evaluation_function_names());
        auto dest_file_name = utils::join(dest_folder_file);

        auto programs = factories::make_programs(arg_parser.get(), gpp.get(), true);
        assert(not programs.empty());
        std::unique_ptr<Program> prog = std::move(programs[0]);

        stats_info->add_timer("program");
        stats_info->timers_info("Program loaded:", "gpp", "program");
        stats_info->add_info_msg("Read program:\n" + prog->to_string(false));

        auto th_name = arg_parser->get_theory_name();
        if( th_name.size() > 8u and th_name.substr(0,8) == "actions_" ){
            gpp->activate_actions_theory();
        }

        if(arg_parser->get_mode() == "validation-prog") {
            auto th_name = arg_parser->get_theory_name();
            run_program(prog.get(), gpp.get(), stats_info.get(), dest_file_name, arg_parser->is_save_pddl_plans());
        }
        else if(arg_parser->get_mode() == "validation-cpp"){
            generate_cpp_code(gpp.get(), prog.get(), dest_folder_file.first, dest_folder_file.second, stats_info.get(), arg_parser.get());
            compile_cpp_code(dest_file_name, stats_info.get());
            execute_cpp_code(gpp.get(), dest_folder_file.first, dest_file_name, stats_info.get());
        }

        stats_info->add_timer("end");
        stats_info->timers_info("Total time:", "start", "end");

        utils::print_to_file(dest_file_name+".out", stats_info->get_all_info());
    }

}

#endif //__RUNNER_H__
