//
// Created by js on 25/05/22.
//

#ifndef __INSTRUCTIONS_IF_H__
#define __INSTRUCTIONS_IF_H__

#include "instruction.h"

namespace instructions{
    class If : public Instruction{
    public:
        explicit If( int dest_line ) : Instruction("if"), _dest_line( dest_line ){}

        ~If() override = default;

        [[nodiscard]] size_t get_destination_line() const{
            return _dest_line;
        }

        /*void add_cond(std::unique_ptr<expressions::conditions::Condition> cond) {
            /// Add a new condition to the GOTO
            _conds.emplace_back(std::move(cond));
        }*/
        void add_cond(variables::Flag* flag, value_t expected_val){
            _conds.emplace_back(std::make_pair(flag, expected_val));
        }

        bool is_applicable(Instance* ins, ProgramState *ps) const override{
            /// An IF instruction is always applicable
            return true;
        }

        value_t apply(Instance* ins, ProgramState* ps) override{
            //auto s = ps->get_state();
            auto line = ps->get_line();
            //bool eval = std::all_of(_conds.begin(), _conds.end(),
            //                              [s](const auto& c){
            //                                        return c->eval_condition(s); });

            // Flags are references of program state flags, hence we can directly access their value
            bool eval = std::all_of(_conds.begin(), _conds.end(),
                                    [](const auto& c){ return c.first->get_value() == c.second; });

            if( eval ) ps->set_line(line + 1); // If all conditions are True, move to next line
            else ps->set_line(_dest_line); // otherwise, move to destination line
            return value_t{0}; // always return 0
        }

        [[nodiscard]] std::vector<std::pair<variables::Flag*,value_t>> get_conds() const{
            return _conds;
        }


        [[nodiscard]] std::string get_name(bool full_info) const override{
            std::string ret = "if(";
            for(const auto& cond : _conds)
                ret += "("+ cond.first->get_name() + "=" + std::to_string(cond.second) +")";
            ret += "," + std::to_string(_dest_line) + ")";
            return ret;
        }

        [[nodiscard]] std::string to_string(bool full_info ) const override{
            return (full_info?"[INSTRUCTION]: ":"") + get_name(full_info);
        }

    private:
        size_t _dest_line;
        std::vector<std::pair<variables::Flag*,value_t>> _conds;
    };
}
#endif //__INSTRUCTIONS_IF_H__
