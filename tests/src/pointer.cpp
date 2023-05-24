//
// Created by js on 1/10/22.
//

#include <gtest/gtest.h>
#include "../../src/variables/pointer.h"

TEST(Pointer, ArbitraryPointer){
    auto obj_type = std::make_unique<ObjectType>("object", nullptr);
    auto ptr = std::make_unique<variables::Pointer>("z1", obj_type.get());
    EXPECT_STREQ("z1", ptr->get_name().c_str());
    EXPECT_EQ(value_t{0}, ptr->get_value());
    EXPECT_STREQ("(z1=0)", ptr->to_string(false).c_str());
    EXPECT_STREQ("[POINTER]: (z1=0)", ptr->to_string(true).c_str());

    ptr->set_value(10);
    EXPECT_EQ(value_t{10}, ptr->get_value());
    EXPECT_STREQ("(z1=10)", ptr->to_string(false).c_str());
    EXPECT_STREQ("[POINTER]: (z1=10)", ptr->to_string(true).c_str());
}