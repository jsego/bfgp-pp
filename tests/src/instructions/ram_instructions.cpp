//
// Created by js on 6/10/22.
//


#include <gtest/gtest.h>
#include "../../../src/instructions/ram/pointer_inc.h"

TEST(RAMInstructionsTests, PointerInstructions) {
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
    /// END - data taken from instance.cpp ********************************************

    auto ps = std::make_unique<ProgramState>(std::make_unique<State>());

    /// Test - Ball pointer
    auto ptr = std::make_unique<variables::Pointer>("ptr_ball",t_ball.get());
    ptr->set_value(0);
    ps->add_pointer(ptr.get());
    auto ptr_inc = std::make_unique<instructions::PointerInc>(ptr.get());
    EXPECT_STREQ("[PROGRAM STATE]:\n"
                 "[LINE]: 0\n"
                 "[FLAGS]:\n"
                 "[POINTERS]: (ptr_ball=0)\n"
                 "[STATE]: " , ps->to_string().c_str());
    EXPECT_TRUE(ptr_inc->is_applicable(instance.get(),ps.get()));
    ptr_inc->apply(instance.get(),ps.get());
    EXPECT_FALSE(ptr_inc->is_applicable(instance.get(), ps.get()));

    /// Test - Object pointer
    auto ptr_obj = std::make_unique<variables::Pointer>("ptr_obj", t_object.get());
    ptr->set_value(0);
    ps->add_pointer(ptr_obj.get());
    auto ptr_obj_inc = std::make_unique<instructions::PointerInc>(ptr_obj.get());
    EXPECT_EQ(6, instance->get_raw_objects().size());
    for(size_t v = 1; v < instance->get_raw_objects().size(); v++){
        EXPECT_TRUE(ptr_obj_inc->is_applicable(instance.get(), ps.get()));
        ptr_obj_inc->apply(instance.get(), ps.get());
    }
    EXPECT_FALSE(ptr_obj_inc->is_applicable(instance.get(), ps.get()));
}