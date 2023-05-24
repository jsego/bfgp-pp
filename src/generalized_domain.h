#ifndef __GENERALIZED_DOMAIN_H__
#define __GENERALIZED_DOMAIN_H__

#include "utils/common.h"
#include "action.h"
#include "domain.h"
#include "instructions/instruction.h"

class GeneralizedDomain{
public:
	/// Instructions can be created only once but we keep the logic
	/// of which actions can be programmed in each line here, so the
	/// engine does not have to reason about it
	GeneralizedDomain(std::unique_ptr<Domain> domain): _domain(std::move(domain)){};

    /// Owns _instructions_line and _features
	~GeneralizedDomain() = default;

    void set_program_lines(size_t program_lines){
        _program_lines = program_lines;
    }

    void add_instruction(std::unique_ptr<instructions::Instruction> instruction){
        instruction->set_id(_instructions.size());
        _instructions.emplace_back(std::move(instruction));
    }

    void add_pointer(std::unique_ptr<variables::Pointer> pointer){
        _pointers.emplace_back(std::move(pointer));
    }

    void add_flag(std::unique_ptr<variables::Flag> flag){
        _flags.emplace_back(std::move(flag));
    }

    [[nodiscard]] variables::Pointer* get_pointer(size_t idx) const{
        assert(idx < _pointers.size());
        return _pointers[idx].get();
    }

    // FIXME (Issue #47): inefficient method
    [[nodiscard]] std::vector<instructions::Instruction*> get_instructions() const{
        std::vector<instructions::Instruction*> instructions;
        for(const auto& ins : _instructions){
            instructions.emplace_back(ins.get());
        }
		return instructions;
	}

    // FIXME (Issue #47): inefficient method
    [[nodiscard]] std::vector<variables::Pointer*> get_pointers() const{
        std::vector<variables::Pointer*> pointers;
        for(const auto& ptr : _pointers){
            pointers.emplace_back(ptr.get());
        }
        return pointers;
    }

    // FIXME (Issue #47): inefficient method
    [[nodiscard]] std::vector<variables::Flag*> get_flags() const{
        std::vector<variables::Flag*> flags;
        for(const auto& flag : _flags){
            flags.emplace_back(flag.get());
        }
        return flags;
    }

	[[nodiscard]] instructions::Instruction* get_instruction(size_t idx) const{
        if(idx >= _instructions.size()) return nullptr;  // Instruction not found
        return _instructions[idx].get();
	}

    [[nodiscard]] instructions::Instruction* get_instruction(const std::string &name) const{
        for(const auto& ins : _instructions){
            if(ins->get_name(true) == name || ins->get_name(false) == name)
                return ins.get();
        }
        return nullptr;  // Instruction not found
    }

    [[nodiscard]] size_t get_program_lines() const{
        return _program_lines;
    }

    /*[[nodiscard]] std::shared_ptr<instructions::Instruction> get_end_for(id_type ptr_id, int modifier, int from_line, int to_line ) const{
        auto it = _end_for_instructions.find(
                std::make_pair(std::make_pair(ptr_id,modifier),
                                  std::make_pair( from_line, to_line ) ) );
        assert( it != _end_for_instructions.end() );
        return it->second;
    }*/

    [[nodiscard]] Domain* get_domain() const{
        return _domain.get();
    }

    [[nodiscard]] std::string to_string(bool full_info) const{
        std::string ret = "[GENERALIZED-DOMAIN]:\n";
        ret += _domain->to_string(false); // print domain without actions (they are already encapsulated as instructions
        if(not _pointers.empty()) ret += "[POINTERS]:\n";
        for(const auto& ptr : _pointers)
            ret += ptr->to_string(full_info) + "\n";
        if(not _flags.empty()) ret += "[FLAGS]:\n";
        for(const auto& flag : _flags)
            ret += flag->to_string(full_info) + "\n";
        if(not _instructions.empty()) ret += "[INSTRUCTIONS]:\n";
        for(const auto& ins : _instructions)
            if(full_info) ret += ins->to_string(true) + "\n"; // print each instruction
            else ret += ins->get_name(true) + "\n";

        /*if( !_end_for_instructions.empty() ) {
            ret += "[ENDFOR INSTRUCTIONS]:\n";
            for (const auto& m: _end_for_instructions) {
                ret += (m.second)->to_string(true) + "\n";
            }
        }*/
		return ret;
	}


protected:
    std::unique_ptr<Domain> _domain;
    std::vector<std::unique_ptr<instructions::Instruction>> _instructions;
    std::vector<std::unique_ptr<variables::Pointer>> _pointers;
    std::vector<std::unique_ptr<variables::Flag>> _flags;
    size_t _program_lines;

    /// End for instructions => <<ptr_id,dir>,<from=for_line,to=end_for_line+1>> = std::shared_ptr<Instruction> EndFor
    //std::map< std::pair<std::pair<id_type ,int>,std::pair<int,int> >, std::shared_ptr<instructions::Instruction> > _end_for_instructions;
    //std::vector< std::vector< std::shared_ptr<expressions::conditions::Condition> > > _features;
};

#endif
