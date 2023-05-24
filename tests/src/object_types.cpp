//
// Created by js on 21/09/22.
//

/// Test the Types class

#include "../../src/object_types.h"
#include <gtest/gtest.h>

// Expect the default Type attribute assignments
TEST(ObjectType, DefaultObject) {
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    EXPECT_STREQ("object", t_object->get_name().c_str());
}

TEST(ObjectType, TypeHierarchy) {
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    EXPECT_STREQ("object", t_object->get_name().c_str());
    EXPECT_STREQ("object", t_object->to_string(false).c_str());
    EXPECT_STREQ("[TYPE]: object", t_object->to_string(true).c_str());

    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto t_robot = std::make_unique<ObjectType>("robot", t_object.get());
    auto t_room = std::make_unique<ObjectType>("room", t_object.get());
    EXPECT_STREQ("object", t_object->to_string(false).c_str());
    EXPECT_STREQ("[TYPE]: object => {ball, robot, room}", t_object->to_string(true).c_str());
    EXPECT_STREQ("[TYPE]: ball:object", t_ball->to_string(true).c_str());
    EXPECT_STREQ("[TYPE]: robot:object", t_robot->to_string(true).c_str());
    EXPECT_STREQ("[TYPE]: room:object", t_room->to_string(true).c_str());

    auto t_object_subtypes = t_object->get_raw_subtypes();

    auto t_gripper = std::make_unique<ObjectType>("gripper", t_robot.get());

    EXPECT_STREQ("[TYPE]: robot:object => {gripper}", t_robot->to_string(true).c_str());

    auto t_robot_subtypes = t_object_subtypes[1]->get_raw_subtypes();

    // Test is_subtype on pointer variables of ObjectType
    EXPECT_FALSE(t_gripper->is_subtype(t_ball.get())); // gripper -> ball
    EXPECT_TRUE(t_gripper->is_subtype(t_robot.get())); // gripper -> robot
    EXPECT_FALSE(t_gripper->is_subtype(t_room.get())); // gripper -> room
    EXPECT_TRUE(t_gripper->is_subtype(t_object.get())); // gripper -> object

    // Test is_subtype on vectors of ObjectType
    EXPECT_FALSE(t_robot_subtypes[0]->is_subtype(t_object_subtypes[0])); // gripper -> ball
    EXPECT_TRUE(t_robot_subtypes[0]->is_subtype(t_object_subtypes[1])); // gripper -> robot
    EXPECT_FALSE(t_robot_subtypes[0]->is_subtype(t_object_subtypes[2])); // gripper -> room
    EXPECT_TRUE(t_robot_subtypes[0]->is_subtype(t_object.get())); // gripper -> object
}
