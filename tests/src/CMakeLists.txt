add_executable( all_tests )
target_sources(
        all_tests
        PRIVATE
        actions.cpp
        constant_value.cpp
        domain.cpp
        expressions/conditions.cpp
        expressions/effects.cpp
        flags.cpp
        function.cpp
        instance.cpp
        instructions/instructions.cpp
        state_variable.cpp
        object.cpp
        object_types.cpp
        parser/parser.cpp
        pointer.cpp
        program_state.cpp
        state.cpp
        variable.cpp
)
target_link_libraries(all_tests gtest_main)
gtest_discover_tests(all_tests)

add_executable(ram_instructions_tests instructions/ram_instructions.cpp)
target_link_libraries(ram_instructions_tests gtest_main)
gtest_discover_tests(ram_instructions_tests)

add_executable(gd_tests generalized_domain.cpp)
target_link_libraries(gd_tests gtest_main)
gtest_discover_tests(gd_tests)

add_executable(gpp_tests generalized_planning_problem.cpp)
target_link_libraries(gpp_tests gtest_main)
gtest_discover_tests(gpp_tests)

add_executable(grounding_tests grounder.cpp)
target_link_libraries(grounding_tests gtest_main)
gtest_discover_tests(grounding_tests)

add_executable(theories_tests theories/theories.cpp)
target_link_libraries(theories_tests gtest_main)
gtest_discover_tests(theories_tests)

add_executable(program_tests program.cpp)
target_link_libraries(program_tests gtest_main)
gtest_discover_tests(program_tests)

add_executable(evaluation_function_tests evaluation_functions.cpp)
target_link_libraries(evaluation_function_tests gtest_main)
gtest_discover_tests(evaluation_function_tests)

add_executable(best_first_search_tests search/best_first_search.cpp)
target_link_libraries(best_first_search_tests gtest_main)
gtest_discover_tests(best_first_search_tests)

add_executable(factories_tests factories.cpp)
target_link_libraries(factories_tests gtest_main)
gtest_discover_tests(factories_tests)

add_executable(relaxed_state_tests relaxations/relaxed_state.cpp)
target_link_libraries(relaxed_state_tests gtest_main)
gtest_discover_tests(relaxed_state_tests)

add_executable(relaxed_action_tests relaxations/relaxed_action.cpp)
target_link_libraries(relaxed_action_tests gtest_main)
gtest_discover_tests(relaxed_action_tests)

add_executable(relaxed_planning_graph_tests relaxations/relaxed_planning_graph.cpp)
target_link_libraries(relaxed_planning_graph_tests gtest_main)
gtest_discover_tests(relaxed_planning_graph_tests)
