//
// Created by js on 20/09/22.
//

#include <gtest/gtest.h>
#include "../../src/variables/state_variable.h"

/// Test the StateVariable class

// Expect a StateVariable with arbitrary attributes
TEST(StateVariable, ArbitraryStateVariablenAndCopy) {
    // Create object types
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto t_room = std::make_unique<ObjectType>("room", t_object.get());

    // Create  function
    auto function = std::make_unique<Function>("at", (id_type )0);
    function->add_parameter(std::make_unique<Object>("?r", 0, t_room.get()));
    function->add_parameter(std::make_unique<Object>("?b", 1, t_ball.get()));

    // Create objects
    auto room_obj = std::make_unique<Object>("roomA", 0, t_room.get());
    auto ball_obj = std::make_unique<Object>("b1", 1, t_ball.get());
    std::vector<Object*> grounding = {room_obj.get(), ball_obj.get()};

    // Create a state var
    auto state_var = std::make_unique<variables::StateVariable>(function.get(),grounding, (value_t)1);

    // Tests
    EXPECT_EQ("at(?r:room,?b:ball)", state_var->get_function()->get_signature());
    EXPECT_FALSE(state_var->get_objects().empty());
    EXPECT_STREQ("at(roomA,b1)", state_var->to_string(false).c_str());
    EXPECT_STREQ("(at(roomA,b1)=1)", state_var->to_string(true).c_str());

    auto fact2= std::make_unique<variables::StateVariable>(state_var.get());
    auto fact2_obj_ids = fact2->get_objects_ids();
    EXPECT_EQ(0, fact2_obj_ids[0]); // roomA is first argument with id=0
    EXPECT_EQ(1, fact2_obj_ids[1]); // b1 is second argument with id=1

}
