//
// Created by js on 24/09/22.
//

#include <gtest/gtest.h>
#include "../../../src/utils/common.h"
#include "../../../src/state.h"
#include "../../../src/expressions/effects/effect.h"
#include "../../../src/expressions/effects/add_assign.h"
#include "../../../src/expressions/effects/assign.h"
#include "../../../src/expressions/effects/compare.h"
#include "../../../src/expressions/effects/subtrack_assign.h"

TEST(Effects, DefaultEffect) {
    auto eff = std::make_unique<expressions::effects::Effect>();
    EXPECT_STREQ("[EFFECT]: ()", eff->to_string(true).c_str());
    EXPECT_STREQ("()", eff->to_string(false).c_str());
}

// Test generic effects
TEST(Effects, GeneralOperations) {
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
    EXPECT_STREQ("[STATE]: (holding(b1)=1)", state->to_string(true).c_str());

    // Create Effect 1-=1
    auto eff_sub_1 = std::make_unique<expressions::effects::SubtractAssign>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[EFFECT]: (holding(b1)-=1)", eff_sub_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)-=1)", eff_sub_1->to_string(false).c_str());
    EXPECT_EQ(value_t{0}, eff_sub_1->get_effect(state.get()));
    eff_sub_1->set_effect(state.get(), eff_sub_1->get_effect(state.get()));
    EXPECT_STREQ("[STATE]: (holding(b1)=0)", state->to_string(true).c_str());

    // Create Effect 0+=1
    auto eff_add_1 = std::make_unique<expressions::effects::AddAssign>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[EFFECT]: (holding(b1)+=1)", eff_add_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)+=1)", eff_add_1->to_string(false).c_str());
    EXPECT_EQ(value_t{1}, eff_add_1->get_effect(state.get()));
    eff_add_1->set_effect(state.get(), eff_add_1->get_effect(state.get()));
    EXPECT_STREQ("[STATE]: (holding(b1)=1)", state->to_string(true).c_str());

    // Create Effect 1<=>1 (only used to update flags)
    auto eff_cmp_1 = std::make_unique<expressions::effects::Compare>(
            std::move(holding_b1->copy()),
            std::move(c_1->copy()));
    EXPECT_STREQ("[EFFECT]: (holding(b1)-1)", eff_cmp_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)-1)", eff_cmp_1->to_string(false).c_str());
    EXPECT_EQ(value_t{0}, eff_cmp_1->get_effect(state.get()));
    eff_cmp_1->set_effect(state.get(), eff_cmp_1->get_effect(state.get()));
    EXPECT_STREQ("[STATE]: (holding(b1)=1)", state->to_string(true).c_str());

    // Create Effect 1<-0
    auto eff_asg_1 = std::make_unique<expressions::effects::Assign>(
            std::move(holding_b1->copy()),
            std::move(c_0->copy()));
    EXPECT_STREQ("[EFFECT]: (holding(b1)=0)", eff_asg_1->to_string(true).c_str());
    EXPECT_STREQ("(holding(b1)=0)", eff_asg_1->to_string(false).c_str());
    EXPECT_EQ(value_t{0}, eff_asg_1->get_effect(state.get()));
    eff_asg_1->set_effect(state.get(), eff_asg_1->get_effect(state.get()));
    EXPECT_STREQ("[STATE]: (holding(b1)=0)", state->to_string(true).c_str());
}

// Test Bitvec operators on bitvec state variables
//TEST(Effects, BitvecOperations){
//
//}