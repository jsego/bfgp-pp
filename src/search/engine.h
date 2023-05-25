#ifndef __SEARCH_ENGINE_H__
#define __SEARCH_ENGINE_H__

#include "../utils/common.h"
#include "node.h"
#include "../evaluation_functions/evaluation_function.h"
#include "../generalized_planning_problem.h"

namespace search{
class Engine{
public:
	Engine( std::unique_ptr<GeneralizedPlanningProblem> gpp ) :
            _evaluated_nodes(0), _expanded_nodes(0), _gpp(std::move(gpp)), _verbose(false){
    };

    /// Owns _evaluation_functions and _gpp
	virtual ~Engine() = default;
	
	[[nodiscard]] virtual bool is_empty() const = 0;
	
	// Add a node to search data structure
	virtual void add_node(std::shared_ptr<Node> node) = 0;
	
	// Select the next Node and update the data structure
    [[nodiscard]] virtual std::shared_ptr<Node> select_node() = 0;
	
	// Check if goal conditions hold in the current Node
    [[nodiscard]] virtual bool is_goal(Node* node) = 0;
	
	// Expand the current Node, adding all non-visited childs
	virtual std::vector<std::shared_ptr<Node>> expand_node(Node* node) = 0;

	// accumulated cost
	//virtual value_t g( Node* node ) = 0;

	// heuristic functions
	//virtual vec_value_t h(Node* node) = 0;

	// evaluation functions
	virtual vec_value_t f(Node* node) = 0;
	
	// Solve the problem starting from init Node
	virtual std::shared_ptr<Node> solve() = 0;
	
	// Add a new heuristic to the engine
	void add_evaluation_function(std::unique_ptr<evaluation_functions::EvaluationFunction> new_ef ){
        std::cout << "[INFO] Evaluation function " << new_ef->get_name() << " added.\n";
        _evaluation_functions.emplace_back(std::move(new_ef) );
    }

    void set_verbose(bool verbose){
        _verbose = verbose;
    }

    // Set a new theory for the syntactic constraints
    void set_theory(std::unique_ptr<theory::Theory> theory){
        _theory = std::move(theory);
    }
	
	[[nodiscard]] value_t get_expanded() const{
		return _expanded_nodes;
	}
	
	[[nodiscard]] value_t get_evaluated() const{
		return _evaluated_nodes;
	}

    [[nodiscard]] GeneralizedPlanningProblem* get_generalized_planning_problem() const{
        return _gpp.get();
    }

    [[nodiscard]] theory::Theory* get_theory() const{
        return _theory.get();
    }

    [[nodiscard]] bool get_verbose() const{
        return _verbose;
    }
	
protected:
	value_t _evaluated_nodes;
	value_t _expanded_nodes;
    std::vector<std::unique_ptr<evaluation_functions::EvaluationFunction>> _evaluation_functions;
	std::unique_ptr<GeneralizedPlanningProblem> _gpp;
    std::unique_ptr<theory::Theory> _theory;
    bool _verbose;
};

}
#endif //__SEARCH_ENGINE_H__
