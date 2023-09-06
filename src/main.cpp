#include "runner.h"

int main(  int argc, const char* argv[] ){
    auto stats_info = factories::make_stats_info();
    auto input_arguments = utils::input_arguments_to_strings(argc, argv);
    auto arg_parser = std::make_unique<utils::ArgumentParser>(input_arguments);

    // Create the Domain object
    auto dom = factories::make_domain(arg_parser.get());
    //std::cout << dom->to_string(true) << std::endl;
    stats_info->add_timer("domain");
    stats_info->timers_info("Parsed domain.", "start", "domain");

    // Create the Generalized Domain object
    auto gd(std::move(factories::make_generalized_domain(arg_parser.get(), std::move(dom))));
    stats_info->add_timer("gd");
    stats_info->timers_info("Generalized Domain created.", "domain", "gd");

	// Create the Generalized Planning Problem object
    auto gpp = factories::make_generalized_planning_problem(arg_parser.get(), std::move(gd));

    //std::cout << gpp->to_string(true) << std::endl;
    // ToDo: move this into the corresponding theory
    /*if(arg_parser->get_theory_name() == "bitvec"){
        for(id_type ins_id = 0; ins_id < gpp->get_num_instances(); ins_id++){
            auto ins = gpp->get_instance(ins_id);
            // Set the 4 default pointers to one index
            auto default_ptr_names = {"ptr-input", "ptr-goal", "ptr-zero", "ptr-one"};
            int line{0};
            for(const auto &ptr_name : default_ptr_names){
                ins->get_initial_state()->set_pointer(ptr_name, line++);
            }
            // Assuming input and goal objects exist in the instance, add zero and one
            auto default_objects = {"_c0", "_c1"};
            int val{0};
            for(const auto &obj_name : default_objects){
                ins->add_object(sd, obj_name, "object");
                ins->get_initial_state()->add_register("vector",{ins->get_object_address(obj_name)},val++);
            }
            // Set each ptr-res-[line] = line+4
            for (int l = 0; l + 2 < arg_parser->get_program_lines(); l++) {
                ins->get_initial_state()->set_pointer("ptr-res-"+std::to_string(l), 4 + l);
            }
        }
    }
    */
    stats_info->add_timer("gpp");
    stats_info->timers_info("Generalized Planning Problem created.", "gd", "gpp");

    // Run either the synthesis or the validation, otherwise the mode is wrong
    auto mode = arg_parser->get_mode();
    if( mode == "synthesis" or mode == "repair")
        runner::synthesis(std::move(arg_parser), std::move(gpp), std::move(stats_info));
    else if( mode == "validation-prog" or mode == "validation-cpp")
        runner::validation(std::move(arg_parser), std::move(gpp), std::move(stats_info));
    else utils::system_error("Wrong mode: " + mode); // Unreachable code (previously checked)
}
