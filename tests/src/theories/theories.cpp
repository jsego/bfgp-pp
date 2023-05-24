//
// Created by js on 6/10/22.
//

#include <gtest/gtest.h>
#include "../../../src/parser/parser.h"
#include "../../../src/theories/assembler.h"
#include "../../../src/theories/c_plus_plus.h"
#include "../../../src/theories/action_schemas.h"
#include "../../../src/theories/action_cellular.h"

TEST(TheoriesTests, AssemblerTest){
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/gpp/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(5);
    gd->add_pointer(std::make_unique<variables::Pointer>("z1", gd->get_domain()->get_object_type("block")));
    gd->add_pointer(std::make_unique<variables::Pointer>("z2", gd->get_domain()->get_object_type("block")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());

    //std::cout << gd->to_string(false) << std::endl;
    auto assembler_gd_file_data = utils::read_file("../../test_files/theories/gd_assembler.txt");
    auto expected_gd = utils::join(assembler_gd_file_data,"\n")+"\n";
    EXPECT_STREQ(expected_gd.c_str(), gd->to_string(false).c_str());
}

TEST(TheoriesTests, CPPTest){
    /// Parsing TriangularSum, building its CPP theory, and checking syntax constraints for a solution
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/theories/domain_cpp.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(5);
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_0", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_1", gd->get_domain()->get_object_type("object")));
    auto th_cpp = std::make_unique<theory::CPlusPlus>();
    th_cpp->build_theory(gd.get());

    //std::cout << gd->to_string(false) << std::endl;
    auto cpp_gd_file_data = utils::read_file("../../test_files/theories/gd_cpp.txt");
    auto expected_gd = utils::join(cpp_gd_file_data,"\n")+"\n";
    EXPECT_STREQ(expected_gd.c_str(), gd->to_string(false).c_str());
}

TEST(TheoriesTests, ActionSchemasTest){
    /// Parsing Visitall (no actions) and building its ActionSchemas theory
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/theories/action_schemas/visitall/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(10);
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_0", gd->get_domain()->get_object_type("place")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_place_1", gd->get_domain()->get_object_type("place")));
    auto th_act_schemas = std::make_unique<theory::ActionSchemas>();
    th_act_schemas->build_theory(gd.get());

    //std::cout << gd->to_string(false) << std::endl;
    auto act_sch_gd_file_data = utils::read_file("../../test_files/theories/action_schemas/visitall/gd_act_sch.txt");
    auto expected_gd = utils::join(act_sch_gd_file_data,"\n")+"\n";
    EXPECT_STREQ(expected_gd.c_str(), gd->to_string(false).c_str());

}

TEST(TheoriesTests, ActionCellularAutomataTest){
    /// Parsing Cellular (no actions) and building its ActionCellular theory
    // ToDo: continue from here
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/theories/action_cellular/rule30/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(63);
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_0", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_1", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_object_2", gd->get_domain()->get_object_type("object")));
    auto th_act_schemas = std::make_unique<theory::ActionCellular>();
    th_act_schemas->build_theory(gd.get());

    //std::cout << gd->to_string(false) << std::endl;
    /*auto act_sch_gd_file_data = utils::read_file("../../test_files/theories/action_schemas/visitall/gd_act_sch.txt");
    auto expected_gd = utils::join(act_sch_gd_file_data,"\n")+"\n";
    EXPECT_STREQ(expected_gd.c_str(), gd->to_string(false).c_str());*/

}