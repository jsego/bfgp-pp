//
// Created by js on 8/03/23.
//

#ifndef __EVALUATION_FUNCTIONS_DISTANCE_TO_LAST_LINE_H__
#define __EVALUATION_FUNCTIONS_DISTANCE_TO_LAST_LINE_H__

#include "evaluation_function.h"

namespace evaluation_functions {

    class DistanceToLastLine : public EvaluationFunction {
    public:
        DistanceToLastLine() : EvaluationFunction("dll") {}

        ~DistanceToLastLine() override = default;

        value_t compute(Program *p, GeneralizedPlanningProblem *gpp) override {
            /// Return the minimum distance to last line for all non-terminated
            /// program executions, otherwise is 0
            //auto vps = p->run( gpp );
            auto vps = p->get_program_states();

            // Error when running the program over active instances
            if (vps.empty()) return INF;

            value_t max_line = -1;
            for(const auto& ps : vps){
                if(ps->get_line()+1 < p->get_num_instructions())
                    max_line = std::max(max_line, (value_t)ps->get_line());
            }
            return (max_line==-1?0:(value_t)p->get_num_instructions()-1-max_line);
        }
    };
}

#endif //__EVALUATION_FUNCTIONS_DISTANCE_TO_LAST_LINE_H__
