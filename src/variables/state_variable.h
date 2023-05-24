//
// Created by js on 20/09/22.
//

#ifndef __STATE_VARIABLE_H__
#define __STATE_VARIABLE_H__

#include "variable.h"
#include "../function.h"
#include "../object.h"
#include "pointer.h"

namespace variables {
    class StateVariable : public Variable {
    public:
        /// Constructor for state variables with object parameters (no pointers)
        explicit StateVariable(Function *function, const std::vector<Object *> &objects,
                               const value_t &value = value_t{1}) :
                Variable("", value), _function(function), _objects(objects) {
            // Set the "complex" name var
            _name = function->get_name() +"(";
            for(const auto& o: objects){
                _name += (o!=*objects.begin()?",":"") + o->get_name();
            }
            _name += ")";
            //FIXME (Issue #47): remove duplicate data regarding smart/raw pointers
            /// Build the list of object ids
            for (const auto &o: _objects)
                _objects_ids.emplace_back(o->get_id());
        };

        /// Copy constructor
        explicit StateVariable(StateVariable* fact) :
                Variable("", fact->get_value()),
                _function(fact->get_function()),
                _pointers(fact->get_pointers()),
                _objects(fact->get_objects()),
                _objects_ids(fact->get_objects_ids()) { //FIXME (Issue #47): remove duplicate data regarding smart/raw pointers
            // Set the "complex" name var
            _name = _function->get_name() +"(";
            if(not _pointers.empty()){
                for(const auto&p: _pointers){
                    _name += (p != *_pointers.begin()?",":"") + p->get_name();
                }
            }
            else {
                for (const auto &o: _objects) {
                    _name += (o != *_objects.begin() ? "," : "") + o->get_name();
                }
            }
            _name += ")";
        }

        ~StateVariable() override = default;

        // ToDo: test in state_variable.cpp
        [[nodiscard]] std::unique_ptr<Variable> copy_var() override{
            return std::make_unique<StateVariable>(this);
        }

        [[nodiscard]] std::unique_ptr<StateVariable> copy(){
            return std::make_unique<StateVariable>(this);
        }

        [[nodiscard]] std::unique_ptr<StateVariable> copy_no_pointers(){
            std::vector<Object*> objects;
            if(not _pointers.empty()){
                for(const auto& p : _pointers)
                    objects.emplace_back(p->get_object());
            }
            else objects = _objects;
            return std::make_unique<StateVariable>(_function, objects, _value);
        }

        void set_pointer_references(const std::vector<Variable*> &pointers) override{
            /// Downcast Variable pointers to Pointer pointers
            _pointers.clear();
            _pointers.reserve(_objects.size());
            for(const auto& o : _objects){
                auto idx = o->get_id(); // parameter index
                assert(idx < (id_type)pointers.size());
                auto ptr = dynamic_cast<Pointer*>(pointers[idx]);
                assert(ptr != nullptr);
                _pointers.emplace_back(ptr);
            }
        }

        void update_object_references(const std::vector<Object*> &new_obj_refs ) override{
            /// Useful for grounding lifted state variables, where object ids represent their indexes in
            /// the list of action parameters, and each is substituted by the current object in that location
            for(size_t pos=0; pos<_objects.size(); pos++){
                assert(_objects_ids[pos] < (id_type)new_obj_refs.size());
                _objects[pos] = new_obj_refs[_objects_ids[pos]];
            }
        }

        void set_object(Object *obj, size_t pos){
            assert(pos < _objects.size());
            _objects[pos] = obj;
        }

        [[nodiscard]] Function *get_function() const {
            return _function;
        }

        [[nodiscard]] std::vector<Object *> get_objects() const {
            return _objects;
        }

        [[nodiscard]] std::vector<Pointer*> get_pointers() const{
            return _pointers;
        }

        [[nodiscard]] vec_id_t get_objects_ids() const {
            // Return default object ids if there are no pointers
            if(_pointers.empty()) return _objects_ids;
            // Otherwise, get the object ids the pointers are pointing to
            vec_id_t obj_ids;
            obj_ids.reserve(_pointers.size());
            for(const auto& p : _pointers){
                obj_ids.emplace_back((id_type)p->get_value());
            }
            return obj_ids;
        }

        [[nodiscard]] std::string get_name() const override{
            auto name = "("+_function->get_name()+"(";
            if(not _pointers.empty()){
                for(const auto&p: _pointers){
                    name += (p != *_pointers.begin()?",":"") + p->get_object()->get_name();
                }
            }
            else {
                for (const auto &o: _objects) {
                    name += (o != *_objects.begin() ? "," : "") + o->get_name();
                }
            }
            name += ")="+std::to_string(_value)+")";
            return name;
        }

        [[nodiscard]] std::string to_string(bool full_info) const override {
            auto state_var_str = (full_info ? "(" : "") + _function->get_name();
            state_var_str.append("(");
            if(not _pointers.empty()){
                for(const auto& ptr : _pointers){
                    state_var_str += ((ptr != *_pointers.begin())?",":"")+ptr->get_name();
                }
            }
            else {
                for(size_t idx = 0; idx < _objects.size(); idx++)
                    state_var_str += (idx?",":"") + _objects[idx]->to_string(false);
            }
            state_var_str.append(")");
            if (full_info) state_var_str += "=" + std::to_string(_value) + ")";
            return state_var_str;
        }

    private:
        Function *_function;  // function symbol that maps objects into a value in the domain of T
        /// Function parameters might be pointers or objects (but not both!)
        std::vector<Pointer*> _pointers; // vector of pointers (e.g., ptr_block:block)
        std::vector<Object*> _objects;  // vector of object (e.g., params of type ?b:block, or instance objects b1:block)

        /// Extra variable to speed up FactComparer (Issue #47)
        vec_id_t _objects_ids;
    };


    class StateVariableComparer {
    public:
        /*bool operator<(const std::unique_ptr<StateVariable> &lhs, const std::unique_ptr<StateVariable> &rhs) const {
            return std::tie(lhs->get_function()->get_id(), lhs->get_objects_ids()) <
                    std::tie(rhs->get_function()->get_id(), rhs->get_objects_ids());
        }*/
        // ToDo: 3-way comparison should improve these results (less calls to functions)
        bool operator()(const std::unique_ptr<StateVariable> &lhs, const std::unique_ptr<StateVariable> &rhs) const {
            if (lhs->get_function()->get_id() > rhs->get_function()->get_id()) return false;
            if (lhs->get_function()->get_id() < rhs->get_function()->get_id()) return true;
            if (lhs->get_objects_ids() > rhs->get_objects_ids()) return false;
            return lhs->get_objects_ids() < rhs->get_objects_ids();
        }
    };
}

#endif //__STATE_VARIABLE_H__
