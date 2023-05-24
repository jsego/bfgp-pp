//
// Created by js on 26/09/22.
//


#include <gtest/gtest.h>
#include "../../src/expressions/conditions/equals.h"
#include "../../src/expressions/effects/assign.h"
#include "../../src/action.h"

TEST(Actions, DefaultAction){
    auto act = std::make_unique<Action>();
    EXPECT_STREQ("[ACTION]: ()\n[TYPE]: math\n[PRECONDITIONS]:\n[EFFECTS]:", act->to_string(true).c_str());
    EXPECT_STREQ("()", act->to_string(false).c_str());
}

TEST(Actions, GroundedAction){
    // Create object types
    auto object_t = std::make_unique<ObjectType>("object", nullptr);
    auto obj_block_t = std::make_unique<ObjectType>("block", object_t.get());

    // Create specific objects
    auto obj_b1 = std::make_unique<Object>("b1", 0, obj_block_t.get());
    auto obj_b2 = std::make_unique<Object>("b2", 1, obj_block_t.get());

    // Create predicates (functions)
    auto pred_clear = std::make_unique<Function>("clear", (id_type ) 0);
    auto pred_handempty = std::make_unique<Function>("handempty", (id_type ) 1);
    auto pred_holding = std::make_unique<Function>("holding", (id_type ) 2);
    auto pred_ontable = std::make_unique<Function>("ontable", (id_type ) 3);

    // Create state variables
    auto sv_holding_obj =
            std::make_unique<variables::StateVariable>(pred_holding.get(),
                                                       std::vector<Object *>({obj_b1.get()}),
                                                       value_t{1});
    auto sv_handempty =
            std::make_unique<variables::StateVariable>(pred_handempty.get(),
                                                       std::vector<Object *>({}),
                                                       value_t{1} );
    auto sv_ontable_obj =
            std::make_unique<variables::StateVariable>(pred_ontable.get(),
                                                       std::vector<Object *>({obj_b1.get()}),
                                                       value_t{1});
    auto sv_clear_obj =
            std::make_unique<variables::StateVariable>(pred_clear.get(),
                                                       std::vector<Object *>({obj_b1.get()}),
                                                       value_t{1});

    // Create constant values
    auto c_0 = std::make_unique<variables::ConstantValue>(0);
    auto c_1 = std::make_unique<variables::ConstantValue>(1);

    auto act = std::make_unique<Action>("pickup",ActionType::Memory);
    // Parameters: add ball b1 as a grounded parameter to pickup action
    act->add_parameter(obj_b1->copy());
    // Preconditions: the ball must be onto the table and clear, and the hand empty to pick it up
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_handempty->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_ontable_obj->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_clear_obj->copy(), c_1->copy()));
    // Effects: all precs are false, while the hand is holding the ball
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_handempty->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_ontable_obj->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_clear_obj->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_holding_obj->copy(), c_1->copy()));

    // Test action content
    auto expected_act_str =
            "[ACTION]: pickup(b1:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (ontable(b1)=1) (clear(b1)=1)\n"
            "[EFFECTS]: (handempty()=0) (ontable(b1)=0) (clear(b1)=0) (holding(b1)=1)";
    EXPECT_STREQ(expected_act_str, act->to_string(true).c_str());

    // Create a state with two objects
    auto state = std::make_unique<State>();
    state->add_fact(sv_handempty->copy());
    state->add_fact(sv_clear_obj->copy());
    state->add_fact(sv_ontable_obj->copy());
    state->add_fact(std::make_unique<variables::StateVariable>(pred_clear.get(),std::vector<Object*>({obj_b2.get()}),value_t{1}));
    state->add_fact(std::make_unique<variables::StateVariable>(pred_ontable.get(),std::vector<Object*>({obj_b2.get()}),value_t{1}));
    EXPECT_STREQ("[STATE]: (clear(b1)=1) (clear(b2)=1) (handempty()=1) (ontable(b1)=1) (ontable(b2)=1)", state->to_string(true).c_str());

    // Test applicability of act on state
    EXPECT_TRUE(act->is_applicable(state.get()));
    act->apply(state.get());
    EXPECT_STREQ("[STATE]: (clear(b1)=0) (clear(b2)=1) (handempty()=0) (holding(b1)=1) (ontable(b1)=0) (ontable(b2)=1)",
                 state->to_string(true).c_str());

    // Test the action hasn't changed
    EXPECT_STREQ(expected_act_str, act->to_string(true).c_str());

    // Test inapplicability of the action on the current state
    EXPECT_FALSE(act->is_applicable(state.get()));

}