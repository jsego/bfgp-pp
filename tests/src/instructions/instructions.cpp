//
// Created by js on 1/10/22.
//


#include <gtest/gtest.h>
#include "../../../src/expressions/conditions/equals.h"
#include "../../../src/expressions/effects/assign.h"
#include "../../../src/variables/zero_flag.h"
#include "../../../src/variables/carry_flag.h"
#include "../../../src/instructions/instruction.h"
#include "../../../src/instructions/end.h"
#include "../../../src/instructions/ram/goto.h"
#include "../../../src/instructions/planning_action.h"
#include "../../../src/instructions/if.h"
#include "../../../src/instructions/for.h"
#include "../../../src/instructions/end_for.h"

TEST(Instructions, BaseInstruction){
    auto instance = std::make_unique<Instance>();  // create an empty instance
    auto ps = std::make_unique<ProgramState>(std::make_unique<State>());
    auto instruction = std::make_unique<instructions::Instruction>();
    EXPECT_FALSE(instruction->is_applicable(instance.get(), ps.get()));
    EXPECT_EQ(value_t{0}, instruction->apply(instance.get(), ps.get()));
    EXPECT_STREQ("empty", instruction->to_string(false).c_str());
    EXPECT_STREQ("[INSTRUCTION]: empty", instruction->to_string(true).c_str());
}

TEST(Instructions, RAMAndCPPInstructions){
    /// BEGIN - data taken from instance.cpp ********************************************
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
    auto sv_at_b1_roomB = std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[2],obj_ptrs[1]})); // at(b1,roomB)=1
    auto sv_at_b2_roomB = std::make_unique<variables::StateVariable>(
            pred_at.get(), std::vector<Object*>({obj_ptrs[3],obj_ptrs[1]})); // at(b2,roomB)=1
    auto sv_carry_b1_left = std::make_unique<variables::StateVariable>(
            pred_carry.get(), std::vector<Object*>({obj_ptrs[2],obj_ptrs[4]})); // carry(b1,left)=1

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
    /// END - data taken from instance.cpp ********************************************

    // Create the Program States
    auto ps_init = std::make_unique<ProgramState>(instance->get_initial_state()->copy());
    auto goal_state = std::make_unique<State>();
    goal_state->add_fact(sv_at_robby_roomA->copy());
    goal_state->add_fact(sv_at_b1_roomB->copy());
    goal_state->add_fact(sv_at_b2_roomB->copy());
    goal_state->add_fact(sv_free_left->copy());
    goal_state->add_fact(sv_free_right->copy());
    auto ps_goal = std::make_unique<ProgramState>(goal_state->copy());

    /// Instruction - END
    auto ins_end = std::make_unique<instructions::End>();
    EXPECT_STREQ("[INSTRUCTION]: end", ins_end->to_string(true).c_str());
    EXPECT_STREQ("end", ins_end->to_string(false).c_str());
    EXPECT_FALSE(ins_end->is_applicable(instance.get(), ps_init.get())); // is not a goal state
    EXPECT_TRUE(ins_end->is_applicable(instance.get(), ps_goal.get()));  // it is a goal state
    auto ps_init_copy = std::make_unique<ProgramState>(instance->get_initial_state()->copy());
    EXPECT_EQ(value_t{0}, ins_end->apply(instance.get(), ps_init.get()));
    EXPECT_STREQ(ps_init_copy->to_string().c_str(), ps_init->to_string().c_str());

    /// Instruction - GOTO
    auto c_0 = std::make_unique<variables::ConstantValue>(0);
    auto c_1 = std::make_unique<variables::ConstantValue>(1);
    auto zf = std::make_unique<variables::ZeroFlag>();
    auto cf = std::make_unique<variables::CarryFlag>();
    //   * create zero flag = 1 cond
    auto cond_zf = std::make_unique<expressions::conditions::Equals>(zf->copy(), c_1->copy());
    //   * create carry flag = 0 cond
    auto cond_cf = std::make_unique<expressions::conditions::Equals>(cf->copy(), c_0->copy());
    //   * create instruction and add conditions
    auto ins_goto = std::make_unique<instructions::Goto>(10);
    ins_goto->add_cond(zf.get(), value_t{1});
    ins_goto->add_cond(cf.get(), value_t{0});
    //   * test the instruction
    EXPECT_STREQ("[INSTRUCTION]: goto(10,!((zf=1)(cf=0)))", ins_goto->to_string(true).c_str());
    EXPECT_STREQ("goto(10,!((zf=1)(cf=0)))", ins_goto->to_string(false).c_str());
    EXPECT_TRUE(ins_goto->is_applicable(instance.get(), ps_init.get()));
    EXPECT_TRUE(ins_goto->is_applicable(instance.get(), ps_goal.get()));
    EXPECT_EQ(value_t{0}, ins_goto->apply(instance.get(), ps_init.get()));
    EXPECT_EQ(size_t{10}, ps_init->get_line());

    /// Instruction - PlanningAction
    /// BEGIN - create grounded Action act = pick(b1,roomA,left)
    auto act = std::make_unique<Action>("pick", ActionType::Memory);
    //   * add parameters
    act->add_parameter(instance->get_object("b1")->copy());
    act->add_parameter(instance->get_object("roomA")->copy());
    act->add_parameter(instance->get_object("left")->copy());
    auto params = act->get_parameters();
    //   * add preconditions
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_at_b1_roomA->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_at_robby_roomA->copy(), c_1->copy()));
    act->add_condition(std::make_unique<expressions::conditions::Equals>(sv_free_left->copy(), c_1->copy()));
    //   * add effects
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_at_b1_roomA->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_free_left->copy(), c_0->copy()));
    act->add_effect(std::make_unique<expressions::effects::Assign>(sv_carry_b1_left->copy(), c_1->copy()));
    /// END - create grounded Action act

    auto ins_act = std::make_unique<instructions::PlanningAction>(std::move(act));
    auto expected_ins_act_str =
            "[INSTRUCTION]: [ACTION]: pick(b1:ball,roomA:room,left:gripper)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (at(b1,roomA)=1) (at-robby(roomA)=1) (free(left)=1)\n"
            "[EFFECTS]: (at(b1,roomA)=0) (free(left)=0) (carry(b1,left)=1)";
    EXPECT_STREQ(expected_ins_act_str, ins_act->to_string(true).c_str());
    EXPECT_STREQ("pick(b1,roomA,left)", ins_act->to_string(false).c_str());
    EXPECT_TRUE(ins_act->is_applicable(instance.get(), ps_init_copy.get()));
    EXPECT_STREQ(
            "[PROGRAM STATE]:\n"
            "[LINE]: 0\n"
            "[FLAGS]:\n"
            "[POINTERS]:\n"
            "[STATE]: (at-robby(roomA)=1) (at(b1,roomA)=1) (at(b2,roomA)=1) (free(left)=1) (free(right)=1)",
            ps_init_copy->to_string().c_str());
    ins_act->apply(instance.get(), ps_init_copy.get());  // since it is applicable, it modifies the state and increases the line by 1
    EXPECT_STREQ(
            "[PROGRAM STATE]:\n"
            "[LINE]: 1\n"
            "[FLAGS]:\n"
            "[POINTERS]:\n"
            "[STATE]: (at-robby(roomA)=1) (at(b1,roomA)=0) (at(b2,roomA)=1) (free(left)=0) (free(right)=1) (carry(b1,left)=1)",
            ps_init_copy->to_string().c_str());
    EXPECT_FALSE(ins_act->is_applicable(instance.get(), ps_init_copy.get()));
    ins_act->apply(instance.get(), ps_init_copy.get());  // since it is inapplicable, it only increases de program line
    EXPECT_STREQ(
            "[PROGRAM STATE]:\n"
            "[LINE]: 2\n"
            "[FLAGS]:\n"
            "[POINTERS]:\n"
            "[STATE]: (at-robby(roomA)=1) (at(b1,roomA)=0) (at(b2,roomA)=1) (free(left)=0) (free(right)=1) (carry(b1,left)=1)",
            ps_init_copy->to_string().c_str());

    /// Instruction - IF
    auto ins_if = std::make_unique<instructions::If>(15);
    ins_if->add_cond(zf.get(), value_t{1});
    EXPECT_STREQ("if((zf=1),15)", ins_if->to_string(false).c_str());
    EXPECT_STREQ("[INSTRUCTION]: if((zf=1),15)", ins_if->to_string(true).c_str());
    EXPECT_EQ(2, ps_init_copy->get_line());
    EXPECT_TRUE(ins_if->is_applicable(instance.get(), ps_init_copy.get()));
    ins_if->apply(instance.get(), ps_init_copy.get());  // should only update the line from 2 to 15
    EXPECT_EQ(15, ps_init_copy->get_line());
    EXPECT_TRUE(ins_if->is_applicable(instance.get(), ps_init_copy.get()));
    auto ins_if_2 = std::make_unique<instructions::If>(20);
    auto cond_neg_zf = std::make_unique<expressions::conditions::Equals>(zf->copy(), c_0->copy());
    ins_if_2->add_cond(zf.get(), value_t{0});
    EXPECT_STREQ("if((zf=0),20)", ins_if_2->to_string(false).c_str());
    EXPECT_STREQ("[INSTRUCTION]: if((zf=0),20)", ins_if_2->to_string(true).c_str());
    EXPECT_TRUE(ins_if_2->is_applicable(instance.get(), ps_init_copy.get()));  // ifs are always applicable
    ins_if_2->apply(instance.get(), ps_init_copy.get());
    EXPECT_EQ(16, ps_init_copy->get_line()); // the PS line must be  only increased by 1, since conds eval to false


    /// Instruction - FOR / ENDFOR
    auto ptr_ball = std::make_unique<variables::Pointer>("ptr-ball", t_ball.get());
    ps_init_copy->set_line(6);
    ps_init_copy->add_pointer(ptr_ball.get());
    //auto ptr_ball = ps_init_copy->get_pointers()[0];  // ptr= Pointer("ptr-ball"), since it is the unique pointer in PS
    ptr_ball->set_value(1);  // check if the pointer value is also modified in the program state
    EXPECT_STREQ("[POINTER]: (ptr-ball=1)", ptr_ball->to_string(true).c_str());
    EXPECT_STREQ(
            "[PROGRAM STATE]:\n"
            "[LINE]: 6\n"
            "[FLAGS]:\n"
            "[POINTERS]: (ptr-ball=1)\n"
            "[STATE]: (at-robby(roomA)=1) (at(b1,roomA)=0) (at(b2,roomA)=1) (free(left)=0) (free(right)=1) (carry(b1,left)=1)",
            ps_init_copy->to_string().c_str());
    auto ins_for = std::make_unique<instructions::For>(ptr_ball.get(), 11);  // let's pose this instruction is at 6;
    EXPECT_STREQ("[INSTRUCTION]: for(ptr-ball++,11)", ins_for->to_string(true).c_str());
    EXPECT_STREQ("for(ptr-ball++,11)", ins_for->to_string(false).c_str());
    EXPECT_TRUE(ins_for->is_applicable(instance.get(), ps_init_copy.get()));  // always applicable
    ins_for->apply(instance.get(), ps_init_copy.get());
    EXPECT_EQ(0, ptr_ball->get_value());  // pointer has been reset
    EXPECT_EQ(7, ps_init_copy->get_line());  // line has been increased by one

    auto ins_end_for = std::make_unique<instructions::EndFor>(ptr_ball.get(), 6); // and this at 10;
    EXPECT_STREQ("[INSTRUCTION]: endfor(ptr-ball++,6)", ins_end_for->to_string(true).c_str());
    EXPECT_STREQ("endfor(ptr-ball++,6)", ins_end_for->to_string(false).c_str());
    EXPECT_TRUE(ins_end_for->is_applicable(instance.get(), ps_init_copy.get()));  // always applicable
    instance->add_object(std::make_unique<Object>("b3",instance->get_next_obj_id(), t_ball.get()));
    auto var_domain = instance->get_typed_variable_domain(ptr_ball->get_type()->get_name());
    ASSERT_EQ(3, var_domain);
    for(value_t var_it = 0; var_it + 1 < var_domain; var_it++) {
        /// Number of times the FOR-ENDFOR is repeated
        ps_init_copy->set_line(10);
        EXPECT_EQ(10, ps_init_copy->get_line());
        EXPECT_EQ(var_it, ptr_ball->get_value());
        ins_end_for->apply(instance.get(), ps_init_copy.get());
        EXPECT_EQ(7, ps_init_copy->get_line());
        EXPECT_EQ(var_it+1, ptr_ball->get_value());
    }
    ps_init_copy->set_line(10);
    ins_end_for->apply(instance.get(), ps_init_copy.get());
    EXPECT_EQ(11, ps_init_copy->get_line());  // moves to the next line after the endfor
    EXPECT_EQ(2, ptr_ball->get_value());  // points to the last ball element in instance


}