#ifndef __EVALUATION_FUNCTION_H__
#define __EVALUATION_FUNCTION_H__

#include "../utils/common.h"
#include "../instructions/instruction.h"
#include "../program.h"
#include "../program_state.h"
#include "../generalized_planning_problem.h"

namespace evaluation_functions {
    class EvaluationFunction {
        /// Base class for evaluation functions with a default "trivial heuristic" (th)
    public:
        explicit EvaluationFunction(const std::string &name = "th") : _name(name) {}

        virtual ~EvaluationFunction() = default;

        [[nodiscard]] virtual std::string get_name() const {
            return _name;
        }

        // Program-based or Performance-based heuristic
        virtual value_t compute(Program *p, GeneralizedPlanningProblem *gpp) {
            return 0;
        }

    private:
        std::string _name;
    };
}

#endif
