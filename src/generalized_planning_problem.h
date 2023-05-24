#ifndef __GENERALIZED_PLANNING_PROBLEM_H__
#define __GENERALIZED_PLANNING_PROBLEM_H__

#include <utility>
#include "utils/common.h"
#include "domain.h"
#include "instance.h"
#include "generalized_domain.h"
//#include "landmarks/landmark_graph.h"

class GeneralizedPlanningProblem{
public:
	GeneralizedPlanningProblem(std::unique_ptr<GeneralizedDomain> gd,
                               bool infinite_detection,
                               //bool use_landmarks,
                               const std::string& problem_folder):
                               _gd(std::move(gd)),
                               _infinite_detection(infinite_detection),
                               //_use_landmarks(use_landmarks),
                               _problem_folder(problem_folder),
                               _actions_theory(false),
                               _progressive(false){

    };

    /// Owns _gd and _instances
	~GeneralizedPlanningProblem() = default;
	
	[[nodiscard]] GeneralizedDomain* get_generalized_domain() const{
		return _gd.get();
	}

    void activate_actions_theory(){ _actions_theory=true; }
    [[nodiscard]] bool is_actions_theory(){ return _actions_theory; }

	void add_instance(std::unique_ptr<Instance> ins ){
		_instances.emplace_back( std::move(ins) );
        _active_instances.emplace_back(true); // by default, all instances are active
        _active_instance_idxs.insert(_instances.size() - 1); // save the instance idx
        _all_instance_idxs.insert(_instances.size()-1); // save the instance idx
	}	
	
	[[nodiscard]] Instance* get_instance(size_t idx) const{
        assert(idx < _instances.size());
		return _instances[idx].get();
	}

	[[nodiscard]] size_t get_num_instances() const{
		return _instances.size();
	}

    void set_infinite_detection(bool infinite_detection){
        _infinite_detection = infinite_detection;
    }

    [[nodiscard]] bool get_infinite_detection() const{
        return _infinite_detection;
    }

    /*
    [[nodiscard]] landmarks::LandmarkGraph* get_landmark_graph(id_type id) const{
        assert(id < (id_type)_landmark_graphs.size());
        return _landmark_graphs[id].get();
    }

    void preprocess_landmark_graphs(bool dump_file=true){
        for(const auto& ins : _instances){
            _landmark_graphs.emplace_back(
                    std::make_unique<landmarks::LandmarkGraph>(
                            _gd->get_domain(),
                            ins.get(),
                            _gd->get_domain()->get_state_descriptor()->get_max_val()));
            if(dump_file){
                auto id = _landmark_graphs.size() - 1;
                std::ofstream ofs_prog(_problem_folder + "/landmark_graph_" + std::to_string(id) + ".txt" );
                ofs_prog << _landmark_graphs[id]->to_string() << "\n";
                ofs_prog.close();
            }
        }
    }


    [[nodiscard]] bool get_use_landmarks() const{
        return _use_landmarks;
    }
     */

    void activate_instance(id_type instance_id){
        assert(instance_id < (id_type)_active_instances.size());
        _active_instances[instance_id] = true;
        _active_instance_idxs.insert(instance_id);
    }

    void deactivate_instance(id_type instance_id){
        assert(instance_id < (id_type)_active_instances.size());
        _active_instances[instance_id] = false;
        _active_instance_idxs.erase(instance_id);
    }

    [[nodiscard]] bool is_instance_active(id_type instance_id) const{
        assert(instance_id < (id_type)_active_instances.size());
        return _active_instances[instance_id];
    }

    void set_progressive(bool progressive){
        _progressive = progressive;
    }

    [[nodiscard]] bool is_progressive() const{
        return _progressive;
    }

    [[nodiscard]] vec_bool_t get_active_instances() const{
        return _active_instances;
    }

    [[nodiscard]] std::set<id_type> get_active_instance_idxs() const{
        if(_progressive)
            return _active_instance_idxs;
        return _all_instance_idxs;
    }

    [[nodiscard]] std::string to_string(bool full_info) const{
        std::string ret = "[GENERALIZED-PLANNING-PROBLEM]:\n";
		if( _gd ) ret += _gd->to_string(full_info);
		for(auto & ins : _instances)
			ret += ins->to_string()+"\n";
		return ret;
	}
	
private:
    std::unique_ptr<GeneralizedDomain> _gd;
    std::vector< std::unique_ptr<Instance> > _instances;

    vec_bool_t _active_instances;
    bool _infinite_detection;
    //bool _use_landmarks;
    std::string _problem_folder;
    bool _actions_theory;
    bool _progressive;
    std::set<id_type> _active_instance_idxs;
    std::set<id_type> _all_instance_idxs;

    /// Possible data-structures to use in preprocessing and search
    //std::vector<std::unique_ptr<landmarks::LandmarkGraph> > _landmark_graphs;
};

#endif

