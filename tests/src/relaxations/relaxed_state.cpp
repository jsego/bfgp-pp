//
// Created by js on 20/10/22.
//

#include "../../../src/parser/parser.h"
#include "../../../src/theories/assembler.h"
#include "../../../src/relaxations/relaxed_state.h"
#include <gtest/gtest.h>

TEST(RelaxedStateTests, RelaxedStates){
    /// 0. parse data and generate generalized planning problem
    /// BEGIN - source code taken from theories/assembler.cpp
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/search/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    gd->set_program_lines(5);
    gd->add_pointer(std::make_unique<variables::Pointer>("a", gd->get_domain()->get_object_type("object")));
    gd->add_pointer(std::make_unique<variables::Pointer>("b", gd->get_domain()->get_object_type("object")));
    auto th_assembler = std::make_unique<theory::Assembler>();
    th_assembler->build_theory(gd.get());
    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,"../../test_files/search/");
    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/search/1.txt");
    gpp->add_instance(std::move(ins));
    //std::cout << gpp->to_string(false) << std::endl;
    /// END - source code taken from theories/assembler.cpp

    auto rs = std::make_unique<relaxation::RelaxedState>(gpp->get_instance(0)->get_initial_state());
    //std::cout << rs->to_string() << std::endl;
    EXPECT_STREQ("[RELAXED-STATE]:\n"
                 "(vector(p0)={0})\n"
                 "(vector(p1)={1})\n"
                 "(vector(p2)={2})\n"
                 "(vector(p3)={3})\n"
                 "(vector(p4)={4})\n"
                 "(vector(p5)={5})\n", rs->to_string().c_str());

    /// 1.a Test if vector(p2)=2 exists in rs (true)
    auto func_vector = gpp->get_generalized_domain()->get_domain()->get_function("vector");
    auto objects = gpp->get_instance(0)->get_raw_objects();
    auto vec_objs = std::vector<Object*>({objects[2]});
    auto sv = std::make_unique<variables::StateVariable>(func_vector, vec_objs, value_t(2));
    EXPECT_TRUE(rs->has_fact(sv.get()));
    /// 1.b Test if vector(p2)=3 exists in rs (false)
    sv->set_value(value_t{3});
    EXPECT_FALSE(rs->has_fact(sv.get()));
    /// 1.c Test if vector(p3)=3 exists in rs (true)
    sv->set_object(objects[3], 0);
    EXPECT_TRUE(rs->has_fact(sv.get()));

    /// 2.a Test add value 4 to vector(p2)
    sv->set_object(objects[2], 0);
    sv->set_value(value_t{4});
    rs->add_fact(sv.get());
    EXPECT_STREQ("[RELAXED-STATE]:\n"
                 "(vector(p0)={0})\n"
                 "(vector(p1)={1})\n"
                 "(vector(p2)={2,4})\n"
                 "(vector(p3)={3})\n"
                 "(vector(p4)={4})\n"
                 "(vector(p5)={5})\n", rs->to_string().c_str());
    auto expected_outcomes = std::vector<bool>({true,false,true});
    for(value_t val = 2; val < 5; val++) {
        sv->set_value(val);
        EXPECT_EQ(expected_outcomes[val - 2], rs->has_fact(sv.get()));
    }
    /// 2.b Test add twice value 4 to vector(p2) (should have no new effect)
    rs->add_fact(sv.get());
    std::cout << rs->to_string() << std::endl;
    EXPECT_STREQ("[RELAXED-STATE]:\n"
                 "(vector(p0)={0})\n"
                 "(vector(p1)={1})\n"
                 "(vector(p2)={2,4})\n"
                 "(vector(p3)={3})\n"
                 "(vector(p4)={4})\n"
                 "(vector(p5)={5})\n", rs->to_string().c_str());

}