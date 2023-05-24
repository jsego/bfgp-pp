//
// Created by js on 7/09/22.
//

#ifndef __EVALUATION_FUNCTIONS_LANDMARK_COUNT_H__
#define __EVALUATION_FUNCTIONS_LANDMARK_COUNT_H__

#include "evaluation_function.h"
#include "../landmarks/landmark_graph.h"

namespace evaluation_functions{
    class LandmarkCount : public EvaluationFunction{
    public:
        LandmarkCount() : EvaluationFunction("lmc") {};
        ~LandmarkCount() override = default;

        // Computing the landmark counting semi-heuristic during program execution.
        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            //return p->get_landmark_count();  // ToDo: landmarks to be implemented
            return value_t{0};
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_LANDMARK_COUNT_H__
