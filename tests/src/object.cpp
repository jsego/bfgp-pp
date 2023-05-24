//
// Created by js on 22/09/22.
//

#include <gtest/gtest.h>
#include "../../src/object.h"

/// Test the Object class

// Expect the default Object attribute assignments
TEST(Object, DefaultObject) {
    auto object = std::make_unique<Object>();
    EXPECT_STREQ("", object->get_name().c_str());
    EXPECT_EQ(-1, object->get_id());
    EXPECT_TRUE( nullptr == object->get_type());
    EXPECT_STREQ("", object->to_string(false).c_str());
    EXPECT_STREQ(":", object->to_string(true).c_str());
}

// Expect an arbitrary Object
TEST(Object, ArbitraryObject) {
    auto t_object = std::make_unique<ObjectType>("object",nullptr);
    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto object = std::make_unique<Object>("ball1", 0, t_ball.get());
    EXPECT_STREQ("ball1", object->get_name().c_str());
    EXPECT_EQ(0, object->get_id());
    EXPECT_TRUE( t_ball.get() == object->get_type());
    EXPECT_STREQ("ball1", object->to_string(false).c_str());
    EXPECT_STREQ("ball1:ball", object->to_string(true).c_str());
}

