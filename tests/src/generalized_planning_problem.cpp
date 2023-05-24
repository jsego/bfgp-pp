//
// Created by js on 4/10/22.
//

#include "../../src/parser/parser.h"
#include "../../src/instructions/planning_action.h"
#include "../../src/generalized_domain.h"
#include "../../src/generalized_planning_problem.h"
#include <gtest/gtest.h>


TEST(GeneralizedPlanningProblem, ArbitraryGPP){
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/gpp/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    for(const auto& a : gd->get_domain()->get_actions()) {
        gd->add_instruction(std::make_unique<instructions::PlanningAction>(a->copy()));
    }
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
    auto expected_instructions = std::string( "[INSTRUCTIONS]:\n"
            "[INSTRUCTION]: [ACTION]: pickup(?b:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1)\n"
            "[EFFECTS]: (handempty()=0) (ontable(?b)=0) (clear(?b)=0) (holding(?b)=1)\n"
            "[INSTRUCTION]: [ACTION]: putdown(?b:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (holding(?b)=1)\n"
            "[EFFECTS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1) (holding(?b)=0)\n"
            "[INSTRUCTION]: [ACTION]: unstack(?b1:block,?b2:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (on(?b1,?b2)=1) (clear(?b1)=1)\n"
            "[EFFECTS]: (handempty()=0) (on(?b1,?b2)=0) (clear(?b1)=0) (clear(?b2)=1) (holding(?b1)=1)\n"
            "[INSTRUCTION]: [ACTION]: stack(?b1:block,?b2:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (holding(?b1)=1) (clear(?b2)=1)\n"
            "[EFFECTS]: (handempty()=1) (on(?b1,?b2)=1) (clear(?b1)=1) (clear(?b2)=0) (holding(?b1)=0)\n");

    EXPECT_STREQ((std::string("[GENERALIZED-DOMAIN]:\n")+
                    expected_domain +
                    expected_instructions).c_str(), gd->to_string(true).c_str() );

    auto gpp =
            std::make_unique<GeneralizedPlanningProblem>(std::move(gd),true,"../../test_files/gpp/");

    EXPECT_STREQ(("[GENERALIZED-PLANNING-PROBLEM]:\n"
                  "[GENERALIZED-DOMAIN]:\n"+
                  expected_domain+expected_instructions).c_str(), gpp->to_string(true).c_str());

    auto ins = std::make_unique<Instance>("default",0,gpp->get_generalized_domain()->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/gpp/1.txt");
    gpp->add_instance(std::move(ins));
    auto expected_instance = std::string(
            "[INSTANCE]: blocksworld-2\n"
            "[DOMAIN]: Blocksworld\n"
            "[OBJECTS]: b1:block b2:block\n"
            "[INIT]: (ontable(b1)=1) (ontable(b2)=1) (handempty()=1) (clear(b1)=1) (clear(b2)=1)\n"
            "[GOAL]: (holding(b1)=1)\n");

    EXPECT_STREQ(("[GENERALIZED-PLANNING-PROBLEM]:\n"
                  "[GENERALIZED-DOMAIN]:\n"+
                expected_domain+
                expected_instructions+
                expected_instance).c_str(), gpp->to_string(true).c_str());

    auto expected_instructions_signatures = std::string(
            "[INSTRUCTIONS]:\n"
            "pickup(?b:block)\n"
            "putdown(?b:block)\n"
            "unstack(?b1:block,?b2:block)\n"
            "stack(?b1:block,?b2:block)\n");

    EXPECT_STREQ(("[GENERALIZED-PLANNING-PROBLEM]:\n"
                 "[GENERALIZED-DOMAIN]:\n"+
                 expected_domain+
                 expected_instructions_signatures+
                 expected_instance).c_str(), gpp->to_string(false).c_str());
}

