//
// Created by js on 17/10/22.
//

#include "../../src/utils/bfgp_utils.h"
#include "../../src/utils/argument_parser.h"
#include "../../src/factory_methods.h"
#include <gtest/gtest.h>

// ToDo: create new executable for factories

TEST(FactoriesTests, MainFactoryFlowTest){
    // ArgParser mock
    auto input_args = std::vector<std::string>({"-m","synthesis",  "-t", "assembler", "-l", "5", "-f", "../../test_files/search/"});
    auto arg_parser = std::make_unique<utils::ArgumentParser>(input_args);
    // 1. make_domain
    auto dom = factories::make_domain(arg_parser.get());
    // 2. make_generalized_domain
    auto gd(std::move(factories::make_generalized_domain(arg_parser.get(), std::move(dom))));
    // 3. make_generalized_planning_problem
    auto gpp = factories::make_generalized_planning_problem(arg_parser.get(), std::move(gd));
    //std::cout << gpp->to_string(true) << std::endl;
    // 4. make_engine
    auto engine = factories::make_engine(arg_parser.get(), std::move(gpp));
    auto res = engine->solve();
    ASSERT_TRUE(res != nullptr);
    EXPECT_STREQ("[NODE]: f1=0 f2=-1\n"
                 "0. vector_add(ptr_object_0,ptr_object_1)\n"
                 "1. set(ptr_object_1,ptr_object_0)\n"
                 "2. inc(ptr_object_0)\n"
                 "3. goto(0,!((zf=1)(cf=0)))\n"
                 "4. end\n", res->to_string().c_str());
}

// TEST(FactoriesTest, ProgramTest){}