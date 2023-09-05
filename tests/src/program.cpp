//
// Created by js on 9/10/22.
//

#include "../../src/parser/parser.h"
#include "../../src/theories/assembler.h"
#include "../../src/program.h"
#include <gtest/gtest.h>


TEST(ProgramTest, EmptyPartialFullProgram){
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/program/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(8);
    gd->add_pointer(std::make_unique<variables::Pointer>("b1", gd->get_domain()->get_object_type("ball")));
    gd->add_pointer(std::make_unique<variables::Pointer>("g1", gd->get_domain()->get_object_type("gripper")));
    gd->add_pointer(std::make_unique<variables::Pointer>("r1", gd->get_domain()->get_object_type("room")));
    gd->add_pointer(std::make_unique<variables::Pointer>("r2", gd->get_domain()->get_object_type("room")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,"../../test_files/program/");
    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/program/1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp

    /// 1. Test empty program
    auto program = std::make_unique<Program>(gpp.get());
    auto ps_empty = program->run(gpp.get());
    ASSERT_EQ(1, ps_empty.size());
    EXPECT_STREQ("[PROGRAM STATE]:\n"
                 "[LINE]: 0\n"
                 "[FLAGS]: (zf=0) (cf=0)\n"
                 "[POINTERS]: (b1=0) (g1=0) (r1=0) (r2=0)\n"
                 "[STATE]: (at_robby(roomA)=1) (at(b1,roomA)=1) (at(b2,roomA)=1) (at(b3,roomA)=1) (at(b4,roomA)=1) "
                 "(at(b5,roomA)=1) (at(b6,roomA)=1) (free(left)=1) (free(right)=1)"
    , ps_empty[0]->to_string().c_str());

    /// 2. Test partial program
    std::vector<std::string> vec_instructions={
            "inc(r2:room)",
            "pick(b1:ball,r1:room,g1:gripper)",
            "move(r1:room,r2:room)",
            "drop(b1:ball,r2:room,g1:gripper)",
            "move(r2:room,r1:room)",
            "inc(b1:ball)",
            "goto(1,!((zf=1)(cf=0)))",
            "end"
            };
    auto raw_gd = gpp->get_generalized_domain();
    // Program the first 5 instructions, run and test
    for(size_t program_line = 0; program_line < 5; program_line++)
        program->set_instruction(program_line, raw_gd->get_instruction(vec_instructions[program_line]));
    auto ps_partial  = program->run(gpp.get());
    ASSERT_EQ(1, ps_partial.size());
    EXPECT_EQ(5, ps_partial[0]->get_line());
    EXPECT_STREQ("[PROGRAM STATE]:\n"
                 "[LINE]: 5\n"
                 "[FLAGS]: (zf=0) (cf=1)\n"
                 "[POINTERS]: (b1=0) (g1=0) (r1=0) (r2=1)\n"
                 "[STATE]: (at_robby(roomA)=1) (at_robby(roomB)=0) (at(b1,roomA)=0) (at(b1,roomB)=1) "
                 "(at(b2,roomA)=1) (at(b3,roomA)=1) (at(b4,roomA)=1) (at(b5,roomA)=1) (at(b6,roomA)=1) (free(left)=1) "
                 "(free(right)=1) (carry(b1,left)=0)", ps_partial[0]->to_string().c_str());
    //std::cout << ps_partial[0]->to_string() << std::endl;

    /// 3. Test full program
    for(size_t program_line = 5; program_line < vec_instructions.size(); program_line++)
        program->set_instruction(program_line, raw_gd->get_instruction(vec_instructions[program_line]));
    //std::cout << program->to_string(false) << std::endl;
    auto ps_full =  program->run(gpp.get());
    ASSERT_EQ(1, ps_full.size());
    EXPECT_EQ(7, ps_full[0]->get_line());
    EXPECT_STREQ("[PROGRAM STATE]:\n"
                 "[LINE]: 7\n"
                 "[FLAGS]: (zf=1) (cf=0)\n"
                 "[POINTERS]: (b1=5) (g1=0) (r1=0) (r2=1)\n"
                 "[STATE]: (at_robby(roomA)=1) (at_robby(roomB)=0) (at(b1,roomA)=0) (at(b1,roomB)=1) "
                 "(at(b2,roomA)=0) (at(b2,roomB)=1) (at(b3,roomA)=0) (at(b3,roomB)=1) (at(b4,roomA)=0) (at(b4,roomB)=1) "
                 "(at(b5,roomA)=0) (at(b5,roomB)=1) (at(b6,roomA)=0) (at(b6,roomB)=1) (free(left)=1) (free(right)=1) "
                 "(carry(b1,left)=0) (carry(b2,left)=0) (carry(b3,left)=0) (carry(b4,left)=0) (carry(b5,left)=0) "
                 "(carry(b6,left)=0)", ps_full[0]->to_string().c_str());
    // Test the goal condition holds in the current state
    EXPECT_TRUE(raw_gd->get_instruction("end")->is_applicable(gpp->get_instance(0), ps_full[0]));
}