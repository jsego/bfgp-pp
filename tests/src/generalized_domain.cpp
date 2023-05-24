//
// Created by js on 3/10/22.
//

#include "../../src/parser/parser.h"
#include "../../src/instructions/planning_action.h"
#include "../../src/generalized_domain.h"
#include <gtest/gtest.h>

TEST(GeneralizedDomain, ArbitraryDomain){
    /// Test that parsed domain is correctly moved into GeneralizedDomain
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/test_domain_with_actions.txt");

    auto expected_domain = std::string(
                          "[DOMAIN]: Blocksworld\n"
                          "[TYPES]:\n"
                          "block:object\n"
                          "[FUNCTIONS]:\n"
                          "on(?b1:block,?b2:block)\n"
                          "ontable(?b:block)\n"
                          "handempty()\n"
                          "clear(?b:block)\n"
                          "holding(?b:block)\n");
    auto expect_actions = std::string(
                          "[ACTIONS]:\n"
                          "[ACTION]: pickup(?b:block)\n"
                          "[TYPE]: memory\n"
                          "[PRECONDITIONS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1)\n"
                          "[EFFECTS]: (handempty()=0) (ontable(?b)=0) (clear(?b)=0) (holding(?b)=1)\n");
        ;
    EXPECT_STREQ((expected_domain+expect_actions).c_str(), dom->to_string(true).c_str());

    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    // Actions are subsumed by Instructions, hence no need to print them
    EXPECT_STREQ((std::string("[GENERALIZED-DOMAIN]:\n")+ expected_domain).c_str(), gd->to_string(true).c_str() );

    /// Test add / get / print instructions
    auto pickup_copy = gd->get_domain()->get_action("pickup(?b:block)")->copy();
    gd->add_instruction(std::make_unique<instructions::PlanningAction>(std::move(pickup_copy)));
    auto expected_instruction =
            "[INSTRUCTION]: [ACTION]: pickup(?b:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1)\n"
            "[EFFECTS]: (handempty()=0) (ontable(?b)=0) (clear(?b)=0) (holding(?b)=1)";
    EXPECT_STREQ(expected_instruction, gd->get_instruction(0)->to_string(true).c_str() );
    EXPECT_STREQ(expected_instruction, gd->get_instruction("pickup(?b:block)")->to_string(true).c_str() );
    EXPECT_TRUE( (nullptr == gd->get_instruction(1)));
}