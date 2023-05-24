//
// Created by js on 27/09/22.
//

#include <gtest/gtest.h>
#include "../../src/expressions/conditions/equals.h"
#include "../../src/expressions/effects/assign.h"
#include "../../src/action.h"
#include "../../src/domain.h"

TEST(Domain, ArbitraryDomain){
    /// Take action test for action creation
    // Create the domain pointer
    auto domain = std::make_unique<Domain>("Blocksworld");

    // Create object types
    auto base_object_type = domain->get_object_type("object");
    ASSERT_TRUE(base_object_type != nullptr);
    auto obj_block_t = std::make_unique<ObjectType>("block", base_object_type);

    // Create specific objects
    auto param_b = std::make_unique<Object>("?b", 0, obj_block_t.get());

    // Create predicates (functions)
    auto pred_clear = std::make_unique<Function>("clear", (id_type ) 0);
    pred_clear->add_parameter(param_b->copy());
    auto pred_handempty = std::make_unique<Function>("handempty", (id_type ) 1);
    auto pred_holding = std::make_unique<Function>("holding", (id_type ) 2);
    pred_holding->add_parameter(param_b->copy());
    auto pred_ontable = std::make_unique<Function>("ontable", (id_type ) 3);
    pred_ontable->add_parameter(param_b->copy());

    // Create state variables
    auto sv_holding_obj =
            std::make_unique<variables::StateVariable>(pred_holding.get(),
                                            std::vector<Object *>({param_b.get()}),
                                            value_t{1});
    auto sv_handempty =
            std::make_unique<variables::StateVariable>(pred_handempty.get(),
                                            std::vector<Object *>({}),
                                            value_t{1} );
    auto sv_ontable_obj =
            std::make_unique<variables::StateVariable>(pred_ontable.get(),
                                            std::vector<Object *>({param_b.get()}),
                                            value_t{1});
    auto sv_clear_obj =
            std::make_unique<variables::StateVariable>(pred_clear.get(),
                                            std::vector<Object *>({param_b.get()}),
                                            value_t{1});

    // Create constant values
    auto c_0 = std::make_unique<variables::ConstantValue>(0);
    auto c_1 = std::make_unique<variables::ConstantValue>(1);

    auto act = std::make_unique<Action>("pickup",ActionType::Memory);
    // Parameters: add ball b1 as a grounded parameter to pickup action
    act->add_parameter(std::move(param_b));
    // Preconditions: the ball must be onto the table and clear, and the hand empty to pick it up
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_handempty->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_ontable_obj->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_clear_obj->copy(), c_1->copy()));
    // Effects: all precs are false, while the hand is holding the ball
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_handempty->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_ontable_obj->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_clear_obj->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_holding_obj->copy(), c_1->copy()));

    /// Start filling domain data
    domain->add_object_type(std::move(obj_block_t));
    // empty constants
    domain->add_function(pred_clear->copy());
    domain->add_function(pred_handempty->copy());
    domain->add_function(pred_holding->copy());
    domain->add_function(pred_ontable->copy());
    domain->add_action(std::move(act));

    auto expected_action =
            "[ACTION]: pickup(?b:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1)\n"
            "[EFFECTS]: (handempty()=0) (ontable(?b)=0) (clear(?b)=0) (holding(?b)=1)";
    auto expected_domain_str =
            std::string("[DOMAIN]: Blocksworld\n")+
            "[TYPES]:\n"+
            "block:object\n"+
            "[FUNCTIONS]:\n"+
            "clear(?b:block)\n"+
            "handempty()\n"+
            "holding(?b:block)\n"+
            "ontable(?b:block)\n"+
            "[ACTIONS]:\n";
    expected_domain_str += expected_action + std::string("\n");

    // Test expected domain
    EXPECT_STREQ(expected_domain_str.c_str(), domain->to_string(true).c_str());

    // Test non-existing and existing object types
    EXPECT_TRUE((nullptr == domain->get_object_type("table")));
    auto t_ptr_by_idx = domain->get_object_type(1);
    EXPECT_EQ("block", t_ptr_by_idx->to_string(false));
    auto t_ptr_by_name = domain->get_object_type("block");
    ASSERT_TRUE((nullptr != t_ptr_by_name));
    EXPECT_EQ("block", t_ptr_by_name->to_string(false));

    // Test non-existing and existing functions
    EXPECT_TRUE((nullptr == domain->get_function("on(?b1:block,?b2:block)")));
    auto f_ptr_by_idx = domain->get_function(0);
    EXPECT_EQ("clear(?b:block)", f_ptr_by_idx->to_string(false));
    auto f_ptr_by_name = domain->get_function("holding");
    ASSERT_TRUE((nullptr != f_ptr_by_name));
    EXPECT_EQ("holding(?b:block)", f_ptr_by_name->to_string(false));

    // Test non-existing and existing actions
    EXPECT_TRUE((nullptr == domain->get_action("putdown(?b:block)")));
    auto act_ptr_by_idx= domain->get_action(0);
    EXPECT_EQ(expected_action, act_ptr_by_idx->to_string(true));
    auto act_ptr_by_signature = domain->get_action("pickup(?b:block)");
    ASSERT_TRUE((nullptr != act_ptr_by_signature));
    EXPECT_EQ(expected_action, act_ptr_by_signature->to_string(true));



}