//
// Created by js on 21/10/22.
//

#include "../../../src/parser/parser.h"
#include "../../../src/theories/assembler.h"
#include "../../../src/relaxations/relaxed_planning_graph.h"
#include <gtest/gtest.h>

TEST(RelaxedActionTests, RelaxedAction) {
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp (but updated to test_files/program/)
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/relaxation/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(8);
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_ball_0", gd->get_domain()->get_object_type("ball")));
    gd->add_pointer(
            std::make_unique<variables::Pointer>("ptr_gripper_0", gd->get_domain()->get_object_type("gripper")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_room_0", gd->get_domain()->get_object_type("room")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_room_1", gd->get_domain()->get_object_type("room")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd), true, "../../test_files/search/");
    auto ins = std::make_unique<Instance>("default", 0, gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/relaxation/1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp (but updated to test_files/program/)

    auto rpg = std::make_unique<relaxation::RelaxedPlanningGraph>(
            gpp->get_generalized_domain()->get_domain(), gpp->get_instance(0));
    rpg->build_relaxed_graph(gpp->get_instance(0)->get_initial_state());

    EXPECT_STREQ("[RELAXED-GRAPH]:\n"
                 "facts_0={(at_robby(roomA)=1),(at(b1,roomA)=1),(at(b2,roomA)=1),(free(left)=1),(free(right)=1)}\n"
                 "actions_0={pick(b1,roomA,left),pick(b1,roomA,right),pick(b2,roomA,left),pick(b2,roomA,right),"
                 "move(roomA,roomB)}\n"
                 "facts_1={(free(left)=0),(at(b1,roomA)=0),(carry(b1,left)=1),(free(right)=0),(carry(b1,right)=1),"
                 "(at(b2,roomA)=0),(carry(b2,left)=1),(carry(b2,right)=1),(at_robby(roomA)=0),(at_robby(roomB)=1)}\n"
                 "actions_1={drop(b1,roomB,left),drop(b1,roomB,right),drop(b2,roomB,left),drop(b2,roomB,right)}\n"
                 "facts_2={(at(b1,roomB)=1),(carry(b1,left)=0),(carry(b1,right)=0),(at(b2,roomB)=1),(carry(b2,left)=0),"
                 "(carry(b2,right)=0)}",
                 rpg->to_string().c_str());

    /// Test 2. Apply actions to pick b1 and b2 balls with left and right grippers, respectively.
    /// Then run the relaxed planning graph from this point.
    auto raw_dom = gpp->get_generalized_domain()->get_domain();
    auto raw_ins = gpp->get_instance(0);
    auto act_pick = raw_dom->get_action("pick(?b:ball,?r:room,?g:gripper)");
    std::vector<std::string> arg_names_1({"b1","roomA","left"});
    std::vector<std::string> arg_names_2({"b2","roomA","right"});
    std::vector<Object*> args_1, args_2;
    for(const auto& arg : arg_names_1) args_1.emplace_back(raw_ins->get_object(arg));
    for(const auto& arg : arg_names_2) args_2.emplace_back(raw_ins->get_object(arg));
    auto gr_act_pick_b1 = act_pick->copy_with_substitution(args_1);
    auto gr_act_pick_b2 = act_pick->copy_with_substitution(args_2);
    auto state = gpp->get_instance(0)->get_initial_state();
    gr_act_pick_b1->apply(state);
    gr_act_pick_b2->apply(state);
    rpg->build_relaxed_graph(state);

    EXPECT_STREQ("[RELAXED-GRAPH]:\n"
                 "facts_0={(at_robby(roomA)=1),(at(b1,roomA)=0),(at(b2,roomA)=0),(free(left)=0),(free(right)=0),"
                 "(carry(b1,left)=1),(carry(b2,right)=1)}\n"
                 "actions_0={drop(b1,roomA,left),drop(b2,roomA,right),move(roomA,roomB)}\n"
                 "facts_1={(free(left)=1),(at(b1,roomA)=1),(carry(b1,left)=0),(free(right)=1),(at(b2,roomA)=1),"
                 "(carry(b2,right)=0),(at_robby(roomA)=0),(at_robby(roomB)=1)}\n"
                 "actions_1={pick(b1,roomA,right),pick(b2,roomA,left),drop(b1,roomB,left),drop(b2,roomB,right)}\n"
                 "facts_2={(carry(b1,right)=1),(carry(b2,left)=1),(at(b1,roomB)=1),(at(b2,roomB)=1)}",
                 rpg->to_string().c_str());
}