//
// Created by js on 22/09/22.
//

#include <gtest/gtest.h>
#include "../../src/utils/common.h"
#include "../../src/state.h"

// Expect a State with arbitrary attributes
TEST(State, ArbitraryStateAndCopyAndUpdate) {
    // Create object types
    auto t_object = std::make_unique<ObjectType>("object",nullptr);;
    auto t_ball = std::make_unique<ObjectType>("ball", t_object.get());
    auto t_room = std::make_unique<ObjectType>("room", t_object.get());

    // Create functions
    auto pred_at = std::make_unique<Function>("at", (id_type )0);
    pred_at->add_parameter(std::make_unique<Object>("?r", 0, t_room.get()));
    pred_at->add_parameter(std::make_unique<Object>("?b", 1, t_ball.get()));

    auto pred_handempty = std::make_unique<Function>("handempty", (id_type )1);
    // no parameters

    // Create objects
    auto room_obj = std::make_unique<Object>("roomA", 0, t_room.get());
    auto ball_obj = std::make_unique<Object>("b1", 1, t_ball.get());
    std::vector<Object*> grounding = {room_obj.get(), ball_obj.get()};


    // Create facts
    auto sv_at = std::make_unique<variables::StateVariable>(pred_at.get(),grounding, value_t{1});
    auto fact_handempty = std::make_unique<variables::StateVariable>(pred_handempty.get(), std::vector<Object*>(), value_t{1});

    // Create state_1
    auto state_1 = std::make_unique<State>();
    state_1->add_fact(std::move(fact_handempty));  // Add first handempty()=1
    state_1->add_fact(std::move(sv_at));  // Add second at(roomA,b1)=1

    // Test that raw pointers are correct
    auto facts_1 = state_1->get_facts();
    //auto it = facts_1.begin();
    ASSERT_STREQ("at(roomA,b1)", facts_1[0]->to_string(false).c_str());
    //ASSERT_EQ((value_t)1,it->second); it++;
    ASSERT_STREQ("handempty()", facts_1[1]->to_string(false).c_str());
    //ASSERT_EQ((value_t)1,it->second); it++;

    // Test the string is well-formed and -contained
    ASSERT_STREQ("(at(roomA,b1)=1) (handempty()=1)", state_1->to_string(false).c_str());
    ASSERT_STREQ("[STATE]: (at(roomA,b1)=1) (handempty()=1)", state_1->to_string(true).c_str());

    // Test copy and modification
    auto state_2 = state_1->copy();
    ASSERT_STREQ("(at(roomA,b1)=1) (handempty()=1)", state_2->to_string(false).c_str());
    ASSERT_STREQ("[STATE]: (at(roomA,b1)=1) (handempty()=1)", state_2->to_string(true).c_str());
    auto facts_2 = state_2->get_facts();
    state_2->set_value(facts_2[0], value_t{0}); // Update at(roomA,b1)=1 to at(roomA,b1)=0
    facts_2 = state_2->get_facts(); // update facts_2 after the change
    // New value in state_1 2
    ASSERT_STREQ("[STATE]: (at(roomA,b1)=0) (handempty()=1)", state_2->to_string(true).c_str());
    // However, state_1 1 is unaffected
    ASSERT_STREQ("[STATE]: (at(roomA,b1)=1) (handempty()=1)", state_1->to_string(true).c_str());

    // Test that states only take fact signatures to get the fact evaluation
    ASSERT_EQ((value_t)0, state_2->get_value(facts_2[0]));  // at(roomA,b1)=0 is 0 in state_2
    ASSERT_EQ((value_t)1, state_1->get_value(facts_2[0]));   // at(roomA,b1)=0 is 1 in state_1

    // Test non-existing fact in a state_1 returns 0 (false)
    auto pred_holding = std::make_unique<Function>("holding", (id_type )2);
    pred_holding->add_parameter(std::make_unique<Object>("?b", 0, t_ball.get()));
    auto pars_holding = std::vector<Object*>({ball_obj.get()});
    auto fact_holding = std::make_unique<variables::StateVariable>(pred_holding.get(), pars_holding, value_t{0});
    ASSERT_EQ((value_t)0, state_1->get_value(fact_holding.get()));

    // Test that an existing fact can update its value from an argument fact
    state_1->set_value(facts_2[0], facts_2[0]->get_value());
    ASSERT_EQ((value_t)0, state_1->get_value(facts_2[0]));  // at(roomA,b1)=0 was 1 in state_1, now it must be 0

}