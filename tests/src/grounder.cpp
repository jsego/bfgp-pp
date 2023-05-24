//
// Created by js on 5/10/22.
//

#include "../../src/parser/parser.h"
#include "../../src/instructions/planning_action.h"
#include "../../src/generalized_domain.h"
#include "../../src/generalized_planning_problem.h"
#include "../../src/grounder.h"
#include <gtest/gtest.h>


TEST(Grounder, InstructionPointerGroundingAndApplicability) {
    auto parser = std::make_unique<parser::Parser>();
    auto dom = std::make_unique<Domain>();
    parser->parse_domain(dom.get(), "../../test_files/gpp/domain.txt");
    auto gd = std::make_unique<GeneralizedDomain>(std::move(dom));
    auto block_t = gd->get_domain()->get_object_type("block");
    gd->add_pointer(std::make_unique<variables::Pointer>("z1", block_t));
    gd->add_pointer(std::make_unique<variables::Pointer>("z2", block_t));
    auto ptrs = gd->get_pointers();
    auto grounder = std::make_unique<Grounder>();
    for (const auto &act: gd->get_domain()->get_actions()) {
        /// BEGIN - Code from theories/core/strips.h
        std::vector<ObjectType*> arg_types;
        for(const auto& o : act->get_parameters()){
            arg_types.emplace_back(o->get_type());
        }
        auto all_ptrs = gd->get_pointers();
        std::vector<std::vector<variables::Pointer*>> ptr_groundings;
        std::vector<variables::Pointer*> current_grounding(arg_types.size());
        grounder->ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding);

        for(const auto& grounding : ptr_groundings){
            // copy action schema (with references to new parameters)
            std::vector<variables::Variable*> var_grounding;
            for(const auto& ptr : grounding)
                var_grounding.emplace_back(ptr);
            gd->add_instruction(std::make_unique<instructions::PlanningAction>(
                    act->copy_with_substitution(var_grounding)));
        }
        /// END - Code from theories/core/strips.h
    }

    //std::cout << gd->to_string(true) << std::endl;
    auto expected_gd = "[GENERALIZED-DOMAIN]:\n"
                       "[DOMAIN]: Blocksworld\n"
                       "[TYPES]:\n"
                       "block:object\n"
                       "[FUNCTIONS]:\n"
                       "on(?b1:block,?b2:block)\n"
                       "ontable(?b:block)\n"
                       "handempty()\n"
                       "clear(?b:block)\n"
                       "holding(?b:block)\n"
                       "[POINTERS]:\n"
                       "[POINTER]: (z1=0)\n"
                       "[POINTER]: (z2=0)\n"
                       "[INSTRUCTIONS]:\n"
                       "[INSTRUCTION]: [ACTION]: pickup(z1:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (handempty()=1) (ontable(z1)=1) (clear(z1)=1)\n"
                       "[EFFECTS]: (handempty()=0) (ontable(z1)=0) (clear(z1)=0) (holding(z1)=1)\n"
                       "[INSTRUCTION]: [ACTION]: pickup(z2:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (handempty()=1) (ontable(z2)=1) (clear(z2)=1)\n"
                       "[EFFECTS]: (handempty()=0) (ontable(z2)=0) (clear(z2)=0) (holding(z2)=1)\n"
                       "[INSTRUCTION]: [ACTION]: putdown(z1:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (holding(z1)=1)\n"
                       "[EFFECTS]: (handempty()=1) (ontable(z1)=1) (clear(z1)=1) (holding(z1)=0)\n"
                       "[INSTRUCTION]: [ACTION]: putdown(z2:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (holding(z2)=1)\n"
                       "[EFFECTS]: (handempty()=1) (ontable(z2)=1) (clear(z2)=1) (holding(z2)=0)\n"
                       "[INSTRUCTION]: [ACTION]: unstack(z1:block,z2:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (handempty()=1) (on(z1,z2)=1) (clear(z1)=1)\n"
                       "[EFFECTS]: (handempty()=0) (on(z1,z2)=0) (clear(z1)=0) (clear(z2)=1) (holding(z1)=1)\n"
                       "[INSTRUCTION]: [ACTION]: unstack(z2:block,z1:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (handempty()=1) (on(z2,z1)=1) (clear(z2)=1)\n"
                       "[EFFECTS]: (handempty()=0) (on(z2,z1)=0) (clear(z2)=0) (clear(z1)=1) (holding(z2)=1)\n"
                       "[INSTRUCTION]: [ACTION]: stack(z1:block,z2:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (holding(z1)=1) (clear(z2)=1)\n"
                       "[EFFECTS]: (handempty()=1) (on(z1,z2)=1) (clear(z1)=1) (clear(z2)=0) (holding(z1)=0)\n"
                       "[INSTRUCTION]: [ACTION]: stack(z2:block,z1:block)\n"
                       "[TYPE]: memory\n"
                       "[PRECONDITIONS]: (holding(z2)=1) (clear(z1)=1)\n"
                       "[EFFECTS]: (handempty()=1) (on(z2,z1)=1) (clear(z2)=1) (clear(z1)=0) (holding(z2)=0)\n";
    EXPECT_STREQ(expected_gd, gd->to_string(true).c_str());

    /// Parse an instance and add it to the GPP
    auto gpp = std::make_unique<GeneralizedPlanningProblem>(
            std::move(gd),true,"../../test_files/gpp/");
    auto gd_ptr = gpp->get_generalized_domain();
    auto ins = std::make_unique<Instance>(
            "default",0,gd_ptr->get_domain());
    parser->parse_instance(ins.get(), "../../test_files/gpp/1.txt");
    gpp->add_instance(std::move(ins));

    /// Create a Program State
    auto instance = gpp->get_instance(0);
    auto init_state = instance->get_initial_state();
    auto ps = std::make_unique<ProgramState>(init_state->copy());
    ps->set_line(0);
    auto z1 = gd_ptr->get_pointer(0);
    z1->set_object(instance->get_typed_objects(z1->get_type()->get_name())[0]);
    auto z2 = gd_ptr->get_pointer(1);
    z2->set_object(instance->get_typed_objects(z2->get_type()->get_name())[0]);
    z2->set_value(1); // redirect z2 to block b2
    z2->set_object(instance->get_typed_objects(z2->get_type()->get_name())[1]);
    ps->add_pointer(z1);  // get z1 pointer from Generalized Domain
    ps->add_pointer(z2);  // get z2 pointer from Generalized Domain

    auto expected_applicability = std::vector<bool>({true, true, false, false, false, false, false, false});
    size_t ins_idx = 0;
    auto all_ins = gd_ptr->get_instructions();
    for(const auto& ins : all_ins){
        EXPECT_EQ(expected_applicability[ins_idx++],
                  ins->is_applicable(instance, ps.get()));
    }
    // In init, pickup(b1) & pickup(b2) are applicable
    // Apply first pickup(b2)
    all_ins[1]->apply(instance, ps.get());  // apply: pickup(z2) = pickup(b2)
    all_ins[3]->apply(instance, ps.get()); // apply: putdown(z2) = putdown(b2)
    EXPECT_STREQ("[STATE]: (ontable(b1)=1) (ontable(b2)=1) (handempty()=1) (clear(b1)=1) (clear(b2)=1) (holding(b2)=0)",
                 ps->get_state()->to_string(true).c_str());

    all_ins[0]->apply(instance, ps.get()); // apply: pickup(z1) = pickup(b1)

    // Check that holding(b1) is the instance goal
    auto state = ps->get_state();
    auto goal_conds = instance->get_goal_condition();
    EXPECT_TRUE(std::all_of(goal_conds.begin(), goal_conds.end(),
                            [state](expressions::conditions::Condition *c){
                                        return c->eval_condition(state); }));

    all_ins[6]->apply(instance, ps.get()); // apply: stack(z1,z2) = stack(b1,b2)
    EXPECT_STREQ("[STATE]: (on(b1,b2)=1) (ontable(b1)=0) (ontable(b2)=1) (handempty()=1) (clear(b1)=1) (clear(b2)=0) (holding(b1)=0) (holding(b2)=0)",
                 ps->get_state()->to_string(true).c_str());

    // z1 points to b2
    z1->set_value(1);
    z1->set_object(instance->get_typed_objects(z1->get_type()->get_name())[1]);

    // z2 points to b1
    z2->set_value(0);
    z2->set_object(instance->get_typed_objects(z2->get_type()->get_name())[0]);

    expected_applicability = {false, false, false, false, false, true, false, false};
    ins_idx = 0;
    for(const auto& ins : all_ins){
        //std::cout << ins->to_string(true) << " applicable? " << ins->is_applicable(instance, ps.get()) << std::endl;
        EXPECT_EQ(expected_applicability[ins_idx++], ins->is_applicable(instance, ps.get()));
    }
}
