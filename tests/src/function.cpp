//
// Created by js on 22/09/22.
//

#include <gtest/gtest.h>
#include "../../src/function.h"

/// Test the Function class

// Expect the default Function attribute assignments
TEST(Function, DefaultFunction) {
    auto function = std::make_unique<Function>();
    EXPECT_STREQ("", function->get_name().c_str());
    EXPECT_STREQ("()", function->get_signature().c_str());
    EXPECT_STREQ("()", function->to_string(false).c_str());
    EXPECT_STREQ("[FUNCTION]: #-1 ()", function->to_string(true).c_str());
}

// Expect an arbitrary Object
TEST(Function, ArbitraryFunction) {
    // Create ObjectTypes
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto t_room = std::make_unique<ObjectType>("room", t_object.get());

    // Create parameters (Objects)
    auto param_room = std::make_unique<Object>("?r", 0, t_room.get());
    auto param_ball = std::make_unique<Object>("?b",1,t_ball.get());

    // Create function
    auto function = std::make_unique<Function>("at", (id_type )0);
    function->add_parameter(std::move(param_room));
    function->add_parameter(std::move(param_ball));

    EXPECT_STREQ("at", function->get_name().c_str());
    EXPECT_STREQ("at(?r:room,?b:ball)", function->get_signature().c_str());
    EXPECT_STREQ("at(?r:room,?b:ball)", function->to_string(false).c_str());
    EXPECT_STREQ("[FUNCTION]: #0 at(?r:room,?b:ball)", function->to_string(true).c_str());

    std::vector<std::string> expected_params = {"?r:room","?b:ball"};
    size_t idx = 0;
    for(auto p : function->get_parameters()){
        EXPECT_STREQ(expected_params[idx].c_str(), p->to_string(true).c_str());
        idx++;
    }
}

