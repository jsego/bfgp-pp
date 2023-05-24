//
// Created by js on 1/10/22.
//

#include <gtest/gtest.h>
#include "../../src/variables/variable.h"

TEST(Variable, ArbitraryVariable){
    auto var = std::make_unique<variables::Variable>("3", (value_t)3);
    EXPECT_STREQ("3", var->get_name().c_str());
    EXPECT_EQ(3, var->get_value());
    EXPECT_STREQ("3", var->to_string(false).c_str());
    EXPECT_STREQ("[VARIABLE]: 3=3", var->to_string(true).c_str());
    var->set_name("4");
    var->set_value(4);
    EXPECT_EQ(4, var->get_value());
    EXPECT_STREQ("4", var->get_name().c_str());
    EXPECT_STREQ("4", var->to_string(false).c_str());
    EXPECT_STREQ("[VARIABLE]: 4=4", var->to_string(true).c_str());
}
