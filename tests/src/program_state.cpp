//
// Created by js on 1/10/22.
//


#include <gtest/gtest.h>
#include "../../src/program_state.h"

TEST(ProgramState, DefaultProgramState) {
    auto ps = std::make_unique<ProgramState>(std::make_unique<State>());
    //std::cout << ps->to_string() << std::endl;
    EXPECT_STREQ("[PROGRAM STATE]:\n"
                 "[LINE]: 0\n"
                 "[FLAGS]:\n"
                 "[POINTERS]:\n"
                 "[STATE]: ", ps->to_string().c_str());
}