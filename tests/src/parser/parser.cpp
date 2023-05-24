//
// Created by js on 28/09/22.
//
#include <gtest/gtest.h>
#include "../../../src/parser/parser.h"

TEST(Parser, IsAndGetDefinition){
    auto parser = std::make_unique<parser::Parser>();
    auto minimum_def_style = std::string("n:t");
    EXPECT_TRUE(parser->is_definition(minimum_def_style));
    auto definition_style = std::string("variable_name:variable_type");
    EXPECT_TRUE(parser->is_definition(definition_style));
    auto def_pair = parser->get_definition(definition_style);
    EXPECT_STREQ("variable_name", def_pair.first.c_str());
    EXPECT_STREQ("variable_type", def_pair.second.c_str());
    auto wrong_def_no_name = std::string(":variable_type");
    EXPECT_FALSE(parser->is_definition(wrong_def_no_name));
    auto wrong_def_no_type = std::string("variable_name:");
    EXPECT_FALSE(parser->is_definition(wrong_def_no_type));
    auto wrong_def_no_separator = std::string("var_namevar_type");
    EXPECT_FALSE(parser->is_definition(wrong_def_no_separator));
    auto wrogn_def_wrong_separator = std::string("variable_name,variable_type");
    EXPECT_FALSE(parser->is_definition(wrong_def_no_separator));
}

TEST(Parser, IsAndGetStateVariable){
    auto parser = std::make_unique<parser::Parser>();

    auto minimal_state_variable = std::string("v()");
    EXPECT_TRUE(parser->is_lifted_state_variable(minimal_state_variable));
    auto min_sv_pair = parser->get_lifted_state_variable(minimal_state_variable);
    EXPECT_EQ("v", min_sv_pair.first);
    EXPECT_EQ(0, min_sv_pair.second.size());

    auto state_variable_no_arguments = std::string("variable_name()");
    EXPECT_TRUE(parser->is_lifted_state_variable(state_variable_no_arguments));
    auto sv_no_args = parser->get_lifted_state_variable(state_variable_no_arguments);
    EXPECT_EQ("variable_name", sv_no_args.first);
    EXPECT_EQ(0, sv_no_args.second.size());

    auto full_lifted_state_variable_one_argument = std::string("variable_name(?arg1)");
    EXPECT_TRUE(parser->is_lifted_state_variable(full_lifted_state_variable_one_argument));
    auto f_sv_one_arg = parser->get_lifted_state_variable(full_lifted_state_variable_one_argument);
    EXPECT_EQ("variable_name", f_sv_one_arg.first);
    ASSERT_EQ(1, f_sv_one_arg.second.size());
    EXPECT_EQ("?arg1", f_sv_one_arg.second[0]);

    auto full_lifted_state_variable_style = std::string("variable_name(?arg1,?arg2,?arg3,?arg4)");
    EXPECT_TRUE(parser->is_lifted_state_variable(full_lifted_state_variable_style));
    auto f_sv_multiple_args = parser->get_lifted_state_variable(full_lifted_state_variable_style);
    EXPECT_EQ("variable_name", f_sv_multiple_args.first);
    ASSERT_EQ(4, f_sv_multiple_args.second.size());
    EXPECT_EQ("?arg1", f_sv_multiple_args.second[0]);
    EXPECT_EQ("?arg2", f_sv_multiple_args.second[1]);
    EXPECT_EQ("?arg3", f_sv_multiple_args.second[2]);
    EXPECT_EQ("?arg4", f_sv_multiple_args.second[3]);

    auto state_variable_wrong_arguments = std::string("variable_name(?arg1,arg2,?arg3)");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_variable_wrong_arguments));
    auto state_variable_no_name = std::string("(?arg1)");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_variable_no_name));
    auto state_variable_wrong_left_parenthesis = std::string("variable_name(()");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_variable_wrong_left_parenthesis));
    auto state_variable_wrong_right_parenthesis = std::string("variable_name())");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_variable_wrong_right_parenthesis));
    auto state_wrong_extra_data = std::string("variable_name(?arg1,?arg2,?arg3,?arg4)wrong_data");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_wrong_extra_data));
    auto state_wrong_empty_argument = std::string("variable_name(?arg1,,?arg3)");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_wrong_empty_argument));
    auto state_wrong_last_empty_argument = std::string("variable_name(?arg1,?arg2,)");
    EXPECT_FALSE(parser->is_lifted_state_variable(state_wrong_last_empty_argument));
}

TEST(Parser, MakeVariable){
    auto parser = std::make_unique<parser::Parser>();
    // Test ConstantValues
    auto constant_1 = parser->make_variable("1");
    EXPECT_EQ(1, constant_1->get_value());
    auto constant_neg_1 = parser->make_variable("-1");
    EXPECT_EQ(-1,constant_neg_1->get_value());

    // Test StateVariable
    // 1. parse domain
    auto domain = std::make_unique<Domain>();
    parser->parse_domain(domain.get(),"../../test_files/test_domain_no_actions.txt"); // ignore its actions
    // 2. create an action with the domain function symbols
    auto action = std::make_unique<Action>("move", ActionType::Memory);
    action->add_parameter(std::make_unique<Object>("?r1", 0, domain->get_object_type("room")));
    action->add_parameter(std::make_unique<Object>("?r2", 1, domain->get_object_type("room")));
    // 3.i parse correct StateVariable
    auto state_variable_str = std::string("at-robby(?r1)");
    auto var_ptr = parser->make_variable(state_variable_str, domain.get(), action.get());
    auto sv_ptr = dynamic_cast<variables::StateVariable*>(var_ptr.get());
    ASSERT_TRUE( (sv_ptr != nullptr) );
    EXPECT_EQ("at-robby(?r1)",sv_ptr->to_string(false));

    // 3.ii parse state variable with wrong function symbol (throws a system_error)
    //auto sv_wrong_func = std::string("at-rob(?r1)");
    //EXPECT_EQ(ERROR_PARSING_DOMAIN, (int)parser->make_variable(sv_wrong_func, domain.get(), nullptr, action.get()));

    // 3.iii parse state variable with wrong lifted variable
    auto sv_wrong_lifted_var_str = std::string("at-robby(r1)"); // no '?' in front of r1
    var_ptr = parser->make_variable(sv_wrong_lifted_var_str, domain.get(), action.get());
    sv_ptr = dynamic_cast<variables::StateVariable*>(var_ptr.get());
    EXPECT_TRUE(sv_ptr == nullptr);
}

TEST(Parser, IsAndGetExpression){
    auto parser = std::make_unique<parser::Parser>();
    // a. valid minimal expression
    auto expr_str = std::string("(1<2)");
    EXPECT_TRUE(parser->is_expression(expr_str));
    auto expr_vec_str = parser->get_expression(expr_str);
    ASSERT_EQ(3, expr_vec_str.size());
    EXPECT_EQ("1", expr_vec_str[0]);
    EXPECT_EQ("<", expr_vec_str[1]);
    EXPECT_EQ("2", expr_vec_str[2]);

    // b. assignment to state variable
    expr_str = std::string("(vector(?pos)+=2)");
    EXPECT_TRUE(parser->is_expression(expr_str));
    expr_vec_str = parser->get_expression(expr_str);
    ASSERT_EQ(3, expr_vec_str.size());
    EXPECT_EQ("vector(?pos)", expr_vec_str[0]);
    EXPECT_EQ("+=", expr_vec_str[1]);
    EXPECT_EQ("2", expr_vec_str[2]);
}

TEST(Parser, ParsingDomain){
    auto parser = std::make_unique<parser::Parser>();
    auto domain = std::make_unique<Domain>();

    // The source code is in build/ subfolder, so add "../../" in front of local files to redirect to the root "tests/"
    parser->parse_domain(domain.get(), "../../test_files/test_domain_with_actions.txt");
    //std::cout << domain->to_string() << std::endl;
    auto expected_domain = std::string(
            "[DOMAIN]: Blocksworld\n"
            "[TYPES]:\n"
            "block:object\n"
            "[FUNCTIONS]:\n"
            "on(?b1:block,?b2:block)\n"
            "ontable(?b:block)\n"
            "handempty()\n"
            "clear(?b:block)\n"
            "holding(?b:block)\n"
            "[ACTIONS]:\n"
            "[ACTION]: pickup(?b:block)\n"
            "[TYPE]: memory\n"
            "[PRECONDITIONS]: (handempty()=1) (ontable(?b)=1) (clear(?b)=1)\n"
            "[EFFECTS]: (handempty()=0) (ontable(?b)=0) (clear(?b)=0) (holding(?b)=1)\n");
    EXPECT_STREQ(expected_domain.c_str(), domain->to_string(true).c_str() );
}

TEST(Parser, ParsingInstance){
    auto parser = std::make_unique<parser::Parser>();
    auto domain = std::make_unique<Domain>();
    parser->parse_domain(domain.get(), "../../test_files/test_domain_with_actions.txt");
    auto ins = std::make_unique<Instance>(std::string(""), (id_type)0, domain.get());
    parser->parse_instance(ins.get(), "../../test_files/blocksworld-2.txt");
    //std::cout << ins->to_string() << std::endl;
    auto expected_instance = std::string(
            "[INSTANCE]: blocksworld-2\n"
            "[DOMAIN]: Blocksworld\n"
            "[OBJECTS]: b1:block b2:block\n"
            "[INIT]: (ontable(b1)=1) (ontable(b2)=1) (handempty()=1) (clear(b1)=1) (clear(b2)=1)\n"
            "[GOAL]: (holding(b1)=1)"
    );
    EXPECT_STREQ(expected_instance.c_str(), ins->to_string().c_str());
}