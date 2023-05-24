//
// Created by js on 24/09/22.
//


#include <gtest/gtest.h>
#include "../../src/variables/constant_value.h"

// Test arbitrary constant values
TEST(ConstantValue, ArbitraryValues){
    // Test booleans True and False
    auto c_true = std::make_unique<variables::ConstantValue>(true);
    EXPECT_TRUE(c_true->get_value());
    EXPECT_STREQ("[CONSTANT]: 1", c_true->to_string(true).c_str());
    EXPECT_STREQ("1", c_true->to_string(false).c_str());

    auto c_false = std::make_unique<variables::ConstantValue>(false);
    EXPECT_FALSE(c_false->get_value());

    // Test int (negative, 0, positive, max)
    auto int_values = std::vector<int>({-20, 0, 50, INT_MAX});
    for(const auto& v : int_values ){
        auto constant = std::make_unique<variables::ConstantValue>(v);
        EXPECT_EQ(v, constant->get_value());
    }

    /*auto double_values = std::vector<double>({-20.000000591212, 0.000001, 9.9999});
    for(const auto&v : double_values){
        auto constant = std::make_unique<variables::ConstantValue>(v);
        EXPECT_DOUBLE_EQ(v, constant->get_value());
    }*/
}