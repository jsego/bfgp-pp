//
// Created by js on 1/10/22.
//

#include <gtest/gtest.h>
#include "../../src/variables/flag.h"
#include "../../src/variables/zero_flag.h"
#include "../../src/variables/carry_flag.h"

TEST(Flag, BaseAndZeroAndCarryFlags){
    auto base_flag = std::make_unique<variables::Flag>("base");
    EXPECT_EQ(0, base_flag->get_value());
    EXPECT_STREQ("(base=0)", base_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (base=0)", base_flag->to_string(true).c_str());
    base_flag->set_value(1);
    EXPECT_EQ(1, base_flag->get_value());
    EXPECT_STREQ("(base=1)", base_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (base=1)", base_flag->to_string(true).c_str());
    base_flag->set_value(0);
    EXPECT_EQ(0, base_flag->get_value());
    EXPECT_STREQ("(base=0)", base_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (base=0)", base_flag->to_string(true).c_str());

    std::unique_ptr<variables::Flag> zero_flag = std::make_unique<variables::ZeroFlag>();
    EXPECT_EQ(0, zero_flag->get_value());
    EXPECT_STREQ("(zf=0)", zero_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (zf=0)", zero_flag->to_string(true).c_str());
    zero_flag->set_value(0);
    EXPECT_EQ(1, zero_flag->get_value());
    EXPECT_STREQ("(zf=1)", zero_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (zf=1)", zero_flag->to_string(true).c_str());
    zero_flag->set_value(3);
    EXPECT_EQ(0, zero_flag->get_value());
    EXPECT_STREQ("(zf=0)", zero_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (zf=0)", zero_flag->to_string(true).c_str());

    std::unique_ptr<variables::Flag> carry_flag = std::make_unique<variables::CarryFlag>();
    EXPECT_EQ(0, carry_flag->get_value());
    EXPECT_STREQ("(cf=0)", carry_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (cf=0)", carry_flag->to_string(true).c_str());
    carry_flag->set_value(3);
    EXPECT_EQ(1, carry_flag->get_value());
    EXPECT_STREQ("(cf=1)", carry_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (cf=1)", carry_flag->to_string(true).c_str());
    carry_flag->set_value(0);
    EXPECT_EQ(0, carry_flag->get_value());
    EXPECT_STREQ("(cf=0)", carry_flag->to_string(false).c_str());
    EXPECT_STREQ("[FLAG]: (cf=0)", carry_flag->to_string(true).c_str());
}