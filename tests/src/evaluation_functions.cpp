//
// Created by js on 10/10/22.
//

#include "../../src/parser/parser.h"
#include "../../src/theories/assembler.h"
#include "../../src/program.h"
#include "../../src/evaluation_functions/euclidean_distance.h"
#include "../../src/evaluation_functions/inverse_loop_counter.h"
#include "../../src/evaluation_functions/loop_counter.h"
#include "../../src/evaluation_functions/loop_lines_counter.h"
#include "../../src/evaluation_functions/max_loop_lines.h"
#include "../../src/evaluation_functions/max_nested_loops.h"
#include "../../src/evaluation_functions/min_repeated_instructions.h"
#include "../../src/evaluation_functions/num_empty_instructions.h"
#include <gtest/gtest.h>


/***
 Tested evaluation functions:
        * Closest Hamming Distance [strict bitvec]  // ToDo: after bitvec theory
 (done) * Euclidean Distance [assembler,cpp]
        * Hamming Distance [weak bitvec]  // ToDo: after bitvec theory
 (done) * Inverse Loop Counter [assembler,cpp]
        * Jaccard Distance [weak bitvec]  // ToDo: after bitvec theory
        * Landmark Counting [assembler,cpp]  // ToDo: after landmarks implementation
 (done) * Loop Counter [assembler,cpp]
 (done) * Loop Lines Counter [assembler,cpp]
 (done) * Max Loop Lines [assembler,cpp]
 (done) * Max Nested Loops [assembler,cpp]
 (done) * Min Repeated Instructions [all]
 (done) * Num of Empty Instruction [all]
 ***/


TEST(EvaluationFunctionsTest, AssemblerAndCPPEvaluationFunctions){
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


    /// Create evaluation functions
    auto ef_euclidean_dist = std::make_unique<evaluation_functions::EuclideanDistance>();
    auto ef_inv_loop_counter = std::make_unique<evaluation_functions::InverseLoopCounter>();
    auto ef_loop_counter = std::make_unique<evaluation_functions::LoopCounter>();
    auto ef_loop_lines_counter = std::make_unique<evaluation_functions::LoopLinesCounter>();
    auto ef_max_loop_lines = std::make_unique<evaluation_functions::MaxLoopLines>();
    auto ef_max_nested_loops = std::make_unique<evaluation_functions::MaxNestedLoop>();
    auto ef_min_repeated_instructions = std::make_unique<evaluation_functions::MinRepeatedInstructions>();
    auto ef_num_empty_instructions = std::make_unique<evaluation_functions::NumEmptyInstructions>();

    /// BEGIN - source code taken from program.cpp
    auto program = std::make_unique<Program>(gpp.get());
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
    /// END - source code taken from program.cpp

    // Tests - empty program (all balls at origin)
    EXPECT_EQ(6, ef_euclidean_dist->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_inv_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_loop_lines_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_max_loop_lines->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_max_nested_loops->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_min_repeated_instructions->compute(program.get(), gpp.get()));
    EXPECT_EQ(8, ef_num_empty_instructions->compute(program.get(), gpp.get()));

    // Tests - partial program (1 ball at goal, 5 at origin)
    for(size_t program_line = 0; program_line < 5; program_line++)
        program->set_instruction(program_line, raw_gd->get_instruction(vec_instructions[program_line]));
    EXPECT_EQ(5, ef_euclidean_dist->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_inv_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_loop_lines_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_max_loop_lines->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_max_nested_loops->compute(program.get(), gpp.get()));
    EXPECT_EQ(1, ef_min_repeated_instructions->compute(program.get(), gpp.get()));
    EXPECT_EQ(3, ef_num_empty_instructions->compute(program.get(), gpp.get()));

    // Tests - full program (all balls finish at goal)
    for(size_t program_line = 5; program_line < vec_instructions.size(); program_line++)
        program->set_instruction(program_line, raw_gd->get_instruction(vec_instructions[program_line]));
    EXPECT_EQ(0, ef_euclidean_dist->compute(program.get(), gpp.get()));
    EXPECT_EQ(-1, ef_inv_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(1, ef_loop_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(-6, ef_loop_lines_counter->compute(program.get(), gpp.get()));
    EXPECT_EQ(-6, ef_max_loop_lines->compute(program.get(), gpp.get()));
    EXPECT_EQ(1, ef_max_nested_loops->compute(program.get(), gpp.get()));
    EXPECT_EQ(1, ef_min_repeated_instructions->compute(program.get(), gpp.get()));
    EXPECT_EQ(0, ef_num_empty_instructions->compute(program.get(), gpp.get()));

}

// TEST(EvaluationFunctionsTest, BitvecEvaluationFunctions){
// }