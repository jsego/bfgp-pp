//
// Created by js on 11/10/22.
//

#include "../../../src/parser/parser.h"
#include "../../../src/theories/assembler.h"
#include "../../../src/evaluation_functions/euclidean_distance.h"
#include "../../../src/evaluation_functions/closed_world_euclidean_distance.h"
#include "../../../src/evaluation_functions/loop_counter.h"
#include "../../../src/search/best_first_search.h"
#include "../../../src/theories/action_schemas.h"
#include "../../../src/theories/action_cellular.h"
#include <gtest/gtest.h>


TEST(BestFirstSearchTests, BFS){
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/search/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(5);
    gd->add_pointer(std::make_unique<variables::Pointer>("a", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("b", gd->get_domain()->get_object_type("object")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,"../../test_files/search/");
    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/search/1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp

    auto engine = std::make_unique<search::BFS>(std::move(gpp));
    engine->add_evaluation_function(std::make_unique<evaluation_functions::EuclideanDistance>());
    engine->add_evaluation_function(std::make_unique<evaluation_functions::LoopCounter>());
    engine->set_theory(std::move(th_assembler));
    auto res = engine->solve();
    ASSERT_TRUE(res != nullptr);
    std::cout << res->to_string() << std::endl;
}

TEST(BestFirstSearchTests, BFSGridMove){
    std::string domain_folder = "../../test_files/theories/action_schemas/hanoi/";
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), domain_folder + "domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(1);
    /* // GRIPPER pointers
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_0", gd->get_domain()->get_object_type("place")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_1", gd->get_domain()->get_object_type("place")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_key_0", gd->get_domain()->get_object_type("key")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_key_1", gd->get_domain()->get_object_type("key")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_shape_0", gd->get_domain()->get_object_type("shape")));
    */
    /* // VISITALL pointers
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_0", gd->get_domain()->get_object_type("place")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_1", gd->get_domain()->get_object_type("place")));
    */
    // HANOI pointers
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_0", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_1", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_2", gd->get_domain()->get_object_type("object")));


    auto th_act_sch = std::make_unique<theory::ActionSchemas>();
    th_act_sch->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,domain_folder);
    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), domain_folder+"1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp

    auto prog = std::make_unique<Program>(gpp.get());
    auto ps = prog->make_program_state(gpp->get_generalized_domain(), gpp->get_instance(0)->get_initial_state());
    prog->reset_program_state(ps.get(), gpp->get_instance(0));
    std::cout << ps->to_string() << std::endl;

    auto instructions = std::vector<std::string>(
            {
                    "test(clear(ptr_object_0:object))",
                    "if((zf=0),45)",
                    "test(clear(ptr_object_1:object))",
                    "if((zf=1),45)",
                    "test(clear(ptr_object_2:object))",
                    "if((zf=0),45)",
                    "test(on(ptr_object_0:object,ptr_object_1:object))",
                    "if((zf=0),45)",
                    "test(on(ptr_object_0:object,ptr_object_2:object))",
                    "if((zf=1),45)",
                    "test(on(ptr_object_1:object,ptr_object_0:object))",
                    "if((zf=1),45)",
                    "test(on(ptr_object_1:object,ptr_object_2:object))",
                    "if((zf=1),45)",
                    "test(on(ptr_object_2:object,ptr_object_0:object))",
                    "if((zf=1),45)",
                    "test(smaller(ptr_object_0:object,ptr_object_1:object))",
                    "if((zf=1),45)",
                    "test(smaller(ptr_object_1:object,ptr_object_0:object))",
                    "if((zf=0),45)",
                    "test(smaller(ptr_object_2:object,ptr_object_0:object))",
                    "if((zf=0),45)",
                    "set(clear(ptr_object_1:object),1)",
                    "set(clear(ptr_object_2:object),0)",
                    "set(on(ptr_object_0:object,ptr_object_1:object),0)",
                    "set(on(ptr_object_0:object,ptr_object_2:object),1)",
                    "end"
            });

    auto cwed = std::make_unique<evaluation_functions::ClosedWorldEuclideanDistance>();

    auto raw_gd = gpp->get_generalized_domain();
    size_t program_line = 0;
    for(const auto& ins_name : instructions){
std::cout << "Checking '" << ins_name << "'..." << std::endl;
       auto ins = raw_gd->get_instruction(ins_name);
       assert(ins != nullptr);
       assert( th_act_sch->check_syntax_constraints(prog.get(), program_line, ins) );
       assert( th_act_sch->check_semantic_constraints(gpp.get(), prog.get(), program_line, ins) );
       prog->set_instruction(program_line++, ins);
       std::cout << "Value returned: " << cwed->compute(prog.get(), gpp.get()) << std::endl;
    }
    std::cout << "Final program:\n" << prog->to_string(false) << std::endl;
    gpp->activate_actions_theory();
    auto vps = prog->run(gpp.get());
    for(const auto& ps : vps){
        std::cout << ps->to_string() << std::endl;
    }


}