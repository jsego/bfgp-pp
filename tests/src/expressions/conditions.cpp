//
// Created by js on 24/09/22.
//


#include <gtest/gtest.h>
#include "../../../src/variables/constant_value.h"
#include "../../../src/state.h"
#include "../../../src/expressions/conditions/condition.h"
#include "../../../src/expressions/conditions/add.h"
#include "../../../src/expressions/conditions/different.h"
#include "../../../src/expressions/conditions/equals.h"
#include "../../../src/expressions/conditions/greater.h"
#include "../../../src/expressions/conditions/greater_equal.h"
#include "../../../src/expressions/conditions/lesser.h"
#include "../../../src/expressions/conditions/lesser_equal.h"
#include "../../../src/expressions/conditions/subtrack.h"


TEST(ConditionsTest, DefaultCondition) {
    auto c = std::make_unique<expressions::conditions::Condition>();
    EXPECT_STREQ("[CONDITION]: ()", c->to_string(true).c_str());
    EXPECT_STREQ("()", c->to_string(false).c_str());
}

TEST(ConditionsTest, AllConditions) {
    // Create object types
    auto object_t = std::make_unique<ObjectType>("object", nullptr);
    auto obj_type = std::make_unique<ObjectType>("block", object_t.get());
    // Create specific objects
    auto obj = std::make_unique<Object>("b1", 0, obj_type.get());
    // Create predicates (functions)
    auto pred_holding = std::make_unique<Function>("holding", (id_type ) 0);
    // Create state variables
    auto sv_holding_obj = std::make_unique<variables::StateVariable>(pred_holding.get(),
                                                          std::vector<Object *>({obj.get()}), value_t{1});

    // Create variables
    auto holding_b1 = sv_holding_obj->copy();
    auto c_0 = std::make_unique<variables::ConstantValue>(0);
    auto c_1 = std::make_unique<variables::ConstantValue>(1);
    auto c_99 = std::make_unique<variables::ConstantValue>(99);

    // Create a state that is holding(b1)=1, although it is predicate, we use it as a numeric state variable in this test
    auto state = std::make_unique<State>();
    state->add_fact(std::move(holding_b1->copy()));

    // Create condition 1+1
    auto c_add_1 = std::make_unique<expressions::conditions::Add>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)+1)", c_add_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)+1)", c_add_1->to_string(false).c_str());
    EXPECT_TRUE(c_add_1->eval_condition(state.get()));

    // Create condition 1+99 (since max value is expected to be 100, it should return false)
    auto c_add_99 = std::make_unique<expressions::conditions::Add>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)+99)", c_add_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)+99)", c_add_99->to_string(false).c_str());
    EXPECT_FALSE(c_add_99->eval_condition(state.get()));

    // Create condition 1!=1
    auto c_diff_1 = std::make_unique<expressions::conditions::Different>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)!=1)", c_diff_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)!=1)", c_diff_1->to_string(false).c_str());
    EXPECT_FALSE(c_diff_1->eval_condition(state.get()));

    // Create condition 1!=99
    auto c_diff_99 = std::make_unique<expressions::conditions::Different>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)!=99)", c_diff_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)!=99)", c_diff_99->to_string(false).c_str());
    EXPECT_TRUE(c_diff_99->eval_condition(state.get()));

    // Create condition 1==1
    auto c_eq_1 = std::make_unique<expressions::conditions::Equals>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)=1)", c_eq_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)=1)", c_eq_1->to_string(false).c_str());
    EXPECT_TRUE(c_eq_1->eval_condition(state.get()));

    // Create condition 1==99
    auto c_eq_99 = std::make_unique<expressions::conditions::Equals>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)=99)", c_eq_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)=99)", c_eq_99->to_string(false).c_str());
    EXPECT_FALSE(c_eq_99->eval_condition(state.get()));

    // Create condition 1>0
    auto c_gt_0 = std::make_unique<expressions::conditions::Greater>(
            std::move(holding_b1->copy()),
            std::move(c_0->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>0)", c_gt_0->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>0)", c_gt_0->to_string(false).c_str());
    EXPECT_TRUE(c_gt_0->eval_condition(state.get()));

    // Create condition 1>1
    auto c_gt_1 = std::make_unique<expressions::conditions::Greater>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>1)", c_gt_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>1)", c_gt_1->to_string(false).c_str());
    EXPECT_FALSE(c_gt_1->eval_condition(state.get()));

    // Create condition 1>99
    auto c_gt_99 = std::make_unique<expressions::conditions::Greater>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>99)", c_gt_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>99)", c_gt_99->to_string(false).c_str());
    EXPECT_FALSE(c_gt_99->eval_condition(state.get()));

    // Create condition 1>=0
    auto c_ge_0 = std::make_unique<expressions::conditions::GreaterEqual>(
            std::move(holding_b1->copy()),
            std::move(c_0->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>=0)", c_ge_0->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>=0)", c_ge_0->to_string(false).c_str());
    EXPECT_TRUE(c_ge_0->eval_condition(state.get()));

    // Create condition 1>=1
    auto c_ge_1 = std::make_unique<expressions::conditions::GreaterEqual>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>=1)", c_ge_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>=1)", c_ge_1->to_string(false).c_str());
    EXPECT_TRUE(c_ge_1->eval_condition(state.get()));

    // Create condition 1>=99
    auto c_ge_99 = std::make_unique<expressions::conditions::GreaterEqual>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)>=99)", c_ge_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)>=99)", c_ge_99->to_string(false).c_str());
    EXPECT_FALSE(c_ge_99->eval_condition(state.get()));

    // Create condition 1<0
    auto c_lt_0 = std::make_unique<expressions::conditions::Lesser>(
            std::move(holding_b1->copy()),
            std::move(c_0->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<0)", c_lt_0->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<0)", c_lt_0->to_string(false).c_str());
    EXPECT_FALSE(c_lt_0->eval_condition(state.get()));

    // Create condition 1<1
    auto c_lt_1 = std::make_unique<expressions::conditions::Lesser>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<1)", c_lt_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<1)", c_lt_1->to_string(false).c_str());
    EXPECT_FALSE(c_lt_1->eval_condition(state.get()));

    // Create condition 1<99
    auto c_lt_99 = std::make_unique<expressions::conditions::Lesser>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<99)", c_lt_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<99)", c_lt_99->to_string(false).c_str());
    EXPECT_TRUE(c_lt_99->eval_condition(state.get()));

    // Create condition 1<=0
    auto c_le_0 = std::make_unique<expressions::conditions::LesserEqual>(
            std::move(holding_b1->copy()),
            std::move(c_0->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<=0)", c_le_0->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<=0)", c_le_0->to_string(false).c_str());
    EXPECT_FALSE(c_le_0->eval_condition(state.get()));

    // Create condition 1<=1
    auto c_le_1 = std::make_unique<expressions::conditions::LesserEqual>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<=1)", c_le_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<=1)", c_le_1->to_string(false).c_str());
    EXPECT_TRUE(c_le_1->eval_condition(state.get()));

    // Create condition 1<=99
    auto c_le_99 = std::make_unique<expressions::conditions::LesserEqual>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)<=99)", c_le_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)<=99)", c_le_99->to_string(false).c_str());
    EXPECT_TRUE(c_le_99->eval_condition(state.get()));

    // Create condition 1-1 (since minimum allowed value is 0, this must return true)
    auto c_sub_1 = std::make_unique<expressions::conditions::Subtract>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)-1)", c_sub_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)-1)", c_sub_1->to_string(false).c_str());
    EXPECT_TRUE(c_sub_1->eval_condition(state.get()));

    // Create condition 1-99 (since minimum allowed value is 0, this must return false)
    auto c_sub_99 = std::make_unique<expressions::conditions::Subtract>(
            std::move(holding_b1->copy()),
            std::move(c_99->copy()));
    EXPECT_STREQ("[CONDITION]: (holding(b1)-99)", c_sub_99->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)-99)", c_sub_99->to_string(false).c_str());
    EXPECT_FALSE(c_sub_99->eval_condition(state.get()));
}
