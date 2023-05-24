//
// Created by js on 27/09/22.
//

#include <gtest/gtest.h>
#include "../../src/variables/state_variable.h"
#include "../../src/instance.h"
#include "../../src/expressions/conditions/equals.h"

TEST(Instance, DefaultInstance){
    auto instance = std::make_unique<Instance>();
    auto expected_default_ins ="[INSTANCE]: \n[DOMAIN]: \n[OBJECTS]:\n[INIT]:\n[GOAL]:";
    EXPECT_EQ(expected_default_ins, instance->to_string());
}

TEST(Instance, ArbitraryInstance){
    // Create object types
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto t_room = std::make_unique<ObjectType>("room", t_object.get());
    auto t_gripper = std::make_unique<ObjectType>("gripper", t_object.get());

    // Start with default instance
    auto domain = std::make_unique<Domain>("gripper");
    auto instance = std::make_unique<Instance>("Gripper-2", (id_type )0, domain.get());

    // Add new objects
    instance->add_object(std::make_unique<Object>("roomA", 0, t_room.get()));
    instance->add_object(std::make_unique<Object>("roomB", 1, t_room.get()));
    instance->add_object(std::make_unique<Object>("b1", 2, t_ball.get()));
    instance->add_object(std::make_unique<Object>("b2", 3, t_ball.get()));
    instance->add_object(std::make_unique<Object>("left", 4, t_gripper.get()));
    instance->add_object(std::make_unique<Object>("right", 5, t_gripper.get()));
    auto obj_ptrs = instance->get_raw_objects();

    // Create functions
    auto pred_at_rooby = std::make_unique<Function>("at-robby", (id_type )0);
    pred_at_rooby->add_parameter(std::make_unique<Object>("?r", 0, t_room.get()));
    auto pred_at = std::make_unique<Function>("at", (id_type )1);
    pred_at->add_parameter(std::make_unique<Object>("?b", 0, t_ball.get()));
    pred_at->add_parameter(std::make_unique<Object>("?r", 1, t_room.get()));
    auto pred_free = std::make_unique<Function>("free", (id_type )2);
    pred_free->add_parameter(std::make_unique<Object>("?g", 0, t_gripper.get()));
    auto pred_carry = std::make_unique<Function>("carry", (id_type )3);
    pred_carry->add_parameter(std::make_unique<Object>("?b", 0, t_ball.get()));
    pred_carry->add_parameter(std::make_unique<Object>("?g", 1, t_gripper.get()));

    // State variables
    auto sv_at_robby_roomA = std::make_unique<variables::StateVariable>(
            pred_at_rooby.get(), std::vector<Object*>({obj_ptrs[0]})); // at_robby(roomA)=1
    auto sv_at_b1_roomA = std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[2],obj_ptrs[0]})); // at(b1,roomA)=1
    auto sv_at_b2_roomA = std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[3],obj_ptrs[0]})); // at(b2,roomA)=1
    auto sv_free_left = std::make_unique<variables::StateVariable>(
            pred_free.get(), std::vector<Object*>({obj_ptrs[4]}));  // free(left)=1
    auto sv_free_right = std::make_unique<variables::StateVariable>(
            pred_free.get(), std::vector<Object*>({obj_ptrs[5]}));  // free(right)=1

    // Create initial state
    auto initial_state = std::make_unique<State>();
    initial_state->add_fact(sv_at_robby_roomA->copy());
    initial_state->add_fact(sv_at_b1_roomA->copy());
    initial_state->add_fact(sv_at_b2_roomA->copy());
    initial_state->add_fact(sv_free_left->copy());
    initial_state->add_fact(sv_free_right->copy());
    instance->set_initial_state(initial_state->copy());

    // Create goal condition
    auto c_at_b1_roomB = std::make_unique<expressions::conditions::Equals>(
            std::make_unique<variables::StateVariable>(pred_at.get(), std::vector<Object*>({obj_ptrs[2], obj_ptrs[1]})),
            std::make_unique<variables::ConstantValue>(value_t{1}));
    auto c_at_b2_roomB = std::make_unique<expressions::conditions::Equals>(
            std::make_unique<variables::StateVariable>(pred_at.get(), std::vector<Object*>({obj_ptrs[3], obj_ptrs[1]})),
            std::make_unique<variables::ConstantValue>(value_t{1}));
    instance->add_goal_condition(std::move(c_at_b1_roomB));
    instance->add_goal_condition(std::move(c_at_b2_roomB));

    auto expected_instance =
            "[INSTANCE]: Gripper-2\n"
            "[DOMAIN]: gripper\n"
            "[OBJECTS]: roomA:room roomB:room b1:ball b2:ball left:gripper right:gripper\n"
            "[INIT]: (at-robby(roomA)=1) (at(b1,roomA)=1) (at(b2,roomA)=1) (free(left)=1) (free(right)=1)\n"
            "[GOAL]: (at(b1,roomB)=1) (at(b2,roomB)=1)";
    EXPECT_STREQ(expected_instance, instance->to_string().c_str());

    /// Test non-existing and existing objects by name and index
    EXPECT_TRUE((nullptr == instance->get_object("table")));
    auto t_ptr_by_idx = instance->get_object(0);
    EXPECT_EQ("roomA", t_ptr_by_idx->to_string(false));
    auto t_ptr_by_name = instance->get_object("roomB");
    ASSERT_TRUE((nullptr != t_ptr_by_name));
    EXPECT_EQ("roomB", t_ptr_by_name->to_string(false));
    auto typed_empty_objs = instance->get_typed_objects("blocks");
    EXPECT_TRUE(typed_empty_objs.empty());
    auto typed_objs = instance->get_typed_objects("gripper");
    auto names = std::vector<std::string>({"left", "right"});
    for(size_t idx=0; idx < names.size(); idx++)
        EXPECT_STREQ(names[idx].c_str(), typed_objs[idx]->to_string(false).c_str());

    /// Test get goal condition pointers
    auto goal_cond_0 = instance->get_condition(0);
    EXPECT_FALSE(goal_cond_0->eval_condition(initial_state.get()));
    auto goal_cond_1 = instance->get_condition(1);
    EXPECT_FALSE(goal_cond_1->eval_condition(initial_state.get()));
    auto goal_state = std::make_unique<State>();
    goal_state->add_fact(std::make_unique<variables::StateVariable>(
            pred_at_rooby.get(), std::vector<Object*>({obj_ptrs[1]}))); // at-robby(roomB)=1
    goal_state->add_fact(std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[2], obj_ptrs[1]}))); // at(b1,roomB)=1
    goal_state->add_fact(std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[3], obj_ptrs[1]}))); // at(b2,roomB)=1
    for(const auto& goal_cond : instance->get_goal_condition())
        EXPECT_TRUE(goal_cond->eval_condition(goal_state.get()));
}