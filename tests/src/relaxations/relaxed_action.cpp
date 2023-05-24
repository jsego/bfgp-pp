//
// Created by js on 21/10/22.
//


#include "../../../src/parser/parser.h"
#include "../../../src/theories/assembler.h"
#include "../../../src/relaxations/relaxed_action.h"
#include <gtest/gtest.h>

TEST(RelaxedActionTests, RelaxedAction){
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp (but updated to test_files/program/)
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/program/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(8);
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_ball_0", gd->get_domain()->get_object_type("ball")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_gripper_0", gd->get_domain()->get_object_type("gripper")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_room_0", gd->get_domain()->get_object_type("room")));
    gd->add_pointer(std::make_unique<variables::Pointer>("ptr_room_1", gd->get_domain()->get_object_type("room")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,"../../test_files/search/");
    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/program/1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp (but updated to test_files/program/)

    /// BEGIN - source code taken from ../../../src/relaxations/relaxed_planning_graph.h
    std::vector<std::unique_ptr<relaxation::RelaxedAction>> relaxed_actions;
    auto grounder = std::make_unique<Grounder>();
    auto all_objs = gpp->get_instance(0)->get_raw_objects();
    for(const auto& a : gpp->get_generalized_domain()->get_domain()->get_actions()){
        /// Compute action "a" grounding over the instance objects
        std::vector<ObjectType*> arg_types;
        for(const auto& o : a->get_parameters()) arg_types.emplace_back(o->get_type());
        std::vector<std::vector<Object*>> groundings;
        std::vector<Object*> current_grounding(arg_types.size());
        grounder->ground_over_objects(arg_types, all_objs, groundings, current_grounding);

        for(const auto& gr : groundings){
            auto grounded_act = a->copy_with_substitution(gr);
            relaxed_actions.emplace_back(std::make_unique<relaxation::RelaxedAction>(grounded_act.get()));
        }
    }
    /// END - source code taken from ../../../src/relaxations/relaxed_planning_graph.h

    //for(const auto& ra : relaxed_actions)
    //    std::cout << ra->get_signature() << std::endl;

    /// 1. Test applicability in the initial relaxed state (all pick(*,roomA,*) and move(roomA,roomB))
    auto rs = std::make_unique<relaxation::RelaxedState>(gpp->get_instance(0)->get_initial_state());
    for(const auto& ra : relaxed_actions){
        auto sig = ra->get_signature();
        if( (sig.substr(0,4) == "pick" and sig.find("roomA") != std::string::npos)  or
            sig == "move(roomA,roomB)") EXPECT_TRUE(ra->is_applicable(rs.get()));
        else EXPECT_FALSE(ra->is_applicable(rs.get()));
    }

    /// 2.a Test fix point applicability
    std::vector<std::vector<relaxation::RelaxedAction*>> layers;
    while(true){
        // Get applicable actions
        std::vector<relaxation::RelaxedAction*> vec_ra;
        for(const auto& ra : relaxed_actions){
            if(ra->get_applied()) continue;
            if(not ra->is_applicable(rs.get())) continue;
            vec_ra.emplace_back(ra.get());
        }
        // Apply them
        for(const auto& ra : vec_ra){
            ra->apply(rs.get());
        }
        if(vec_ra.empty()) break;
        layers.emplace_back(vec_ra);
    }

    //std::cout << rs->to_string() << std::endl;
    ASSERT_EQ(3, int(layers.size()));
    /// 2.b First layer previously tested (Test 1.)
    /// 2.c Second layer (all drops and move(roomB,roomA))
    for(const auto& ra : layers[1]){
        EXPECT_TRUE(ra->get_name() == "drop" or ra->get_signature() == "move(roomB,roomA)");
    }
    /// 2.d Third layer (is the last one, contains all picks from roomB)
    for(const auto& ra : layers[2]){
        auto sig = ra->get_signature();
        EXPECT_TRUE(sig.substr(0,4) == "pick" and sig.find("roomB") != std::string::npos);
    }
}