//
// Created by js on 4/10/22.
//

#ifndef __GROUNDER_H__
#define __GROUNDER_H__

#include "variables/pointer.h"
#include "action.h"
#include "instructions/planning_action.h"
#include "generalized_domain.h"

class Grounder{
    /// Class to ground action schemas over Pointers or Objects and add them as PlanningAction
    /// instructions into the GeneralizedDomain. Also work for grounding Flag evaluations.
public:
    Grounder() = default;
    ~Grounder() = default;

    void ground_over_objects(const std::vector<ObjectType*>& arg_types,
                             const std::vector<Object*> &all_objs,
                             std::vector<std::vector<Object*>> &obj_groundings,
                             std::vector<Object*> &current_grounding,
                             size_t pos = 0) {
        /// Function to ground argument types over all object combinations, and save them in obj_groundings container
        // Assumption: arg_types.size()==current_grounding.size() from input
        // If the all objects have been assigned, save the current grounding
        if( pos == arg_types.size()){
            obj_groundings.emplace_back(current_grounding);
            return;
        }
        // Otherwise, loop and assign valid objects and proceed to the next one
        for(const auto& ptr : all_objs){
            // Skip the current obj if it has been previously assigned to a parameter
            if(pos and std::any_of(current_grounding.begin(),current_grounding.begin()+pos,
                                   [ptr](const auto& prev_ptr){return ptr==prev_ptr;}))
                continue;
            // Assign the ptr to the current grounding if type (or subtype) matches with the argument type
            if((ptr->get_type() == arg_types[pos]) or (ptr->get_type()->is_subtype(arg_types[pos]))){
                current_grounding[pos] = ptr;
                ground_over_objects(arg_types, all_objs, obj_groundings, current_grounding, pos+1);
            }
        }

    }

    void ground_over_pointers(const std::vector<ObjectType*>& arg_types,
                              const std::vector<variables::Pointer*>& all_ptrs,
                              std::vector<std::vector<variables::Pointer*>> &ptr_groundings,
                              std::vector<variables::Pointer*> &current_grounding,
                              size_t pos = 0){
        /// Function to ground argument types over all pointer combinations, and save them in ptr_groundings container
        // Assumption: arg_types.size()==current_grounding.size() from input
        // If the all pointers have been assigned, save the current grounding
        if( pos == arg_types.size()){
            ptr_groundings.emplace_back(current_grounding);
            return;
        }
        // Otherwise, loop and assign valid pointers and proceed to the next one
        for(const auto& ptr : all_ptrs){
            // Skip the current ptr if it has been previously assigned to a parameter
            if(pos and std::any_of(current_grounding.begin(),current_grounding.begin()+pos,
                                   [ptr](const auto& prev_ptr){return ptr==prev_ptr;}))
                continue;
            // Assign the ptr to the current grounding if type (or subtype) matches with the argument type
            if((ptr->get_type() == arg_types[pos]) or (ptr->get_type()->is_subtype(arg_types[pos]))){
                current_grounding[pos] = ptr;
                ground_over_pointers(arg_types, all_ptrs, ptr_groundings, current_grounding, pos + 1);
            }
        }
    }

    void ground_flags(const std::vector<variables::Flag*>& flags,
                      std::vector<std::vector<value_t>> &flag_groundings,
                      std::vector<value_t> &current_grounding,
                      size_t pos=0){
        if(pos == flags.size()){
            flag_groundings.emplace_back(current_grounding);
            return;
        }
        for(value_t v = 0; v < 2; v++){
            current_grounding[pos] = v;
            ground_flags(flags, flag_groundings, current_grounding, pos + 1);
        }
    }
};

#endif //__GROUNDER_H__
