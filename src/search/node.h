#ifndef __NODE_H__
#define __NODE_H__

#include "../utils/common.h"
#include "../program.h"

namespace search {
    class Node {
    public:
        explicit Node(std::unique_ptr<Program> p,
                      const vec_value_t &evaluations = {0},
                      id_type id = 0) :
                _evaluations(evaluations), _id(id), _program(std::move(p)) {};

        /// Owns _program
        ~Node() = default;

        void set_f(const vec_value_t &eval) {
            _evaluations = eval;
        }

        void set_id(id_type id) {
            _id = id;
        }

        [[nodiscard]] vec_value_t f() const {
            return _evaluations;
        }

        [[nodiscard]] id_type get_id() const {
            return _id;
        }

        [[nodiscard]] Program *get_program() const {
            return _program.get();
        }

        [[nodiscard]] std::string to_string() const {
            std::string ret = "[NODE]:";
            for (int i = 0; i < int(_evaluations.size()); i++) {
                ret += " f" + std::to_string(i + 1) + "=" + std::to_string(_evaluations[i]);
            }
            ret += "\n";
            if (_program) ret += _program->to_string(false);
            return ret;
        }

    private:
        vec_value_t _evaluations;
        id_type _id;
        std::unique_ptr<Program> _program;
    };

    class NodeComparator {
    public:
        NodeComparator() = default;
        ~NodeComparator() = default;
        bool operator()(const std::shared_ptr<Node> &lhs, const std::shared_ptr<Node> &rhs) const {
            /// Returns true if the LHS evaluations are smaller than the RHS, tie breaking by node ID
            //return (lhs->f() < rhs->f()) or (lhs->f() == rhs->f() and lhs->get_id() < rhs->get_id());
            return (lhs->f() > rhs->f()) or (lhs->f() == rhs->f() and lhs->get_id() > rhs->get_id());
        }
    };
}
#endif
