//
// Created by js on 22/09/22.
//

#ifndef __OBJECT_H__
#define __OBJECT_H__

#include "utils/common.h"
#include "object_types.h"

class Object{
public:
    explicit Object(const std::string &name = "", id_type id = -1, ObjectType *t = nullptr) : _name(name), _id(id), _t(t){}

    explicit Object(Object* o) : _name(o->get_name()), _id(o->get_id()), _t(o->get_type()){}

    ~Object() = default;

    // ToDo: test this function
    std::unique_ptr<Object> copy(){
        return std::make_unique<Object>(this);
    }

    void set_name(const std::string &name){
        _name = name;
    }

    [[nodiscard]] std::string get_name() const{
        return _name;
    }

    [[nodiscard]] id_type get_id() const{
        return _id;
    }

    [[nodiscard]] ObjectType* get_type() const{
        return _t;
    }

    [[nodiscard]] std::string to_string(bool full_info) const{
        if(not full_info) return _name;
        return _name + ":" + (_t!= nullptr?_t->get_name():"");
        //return "[OBJECT]: #" + std::to_string(_id) + " " + _name + ":" + (_t!= nullptr?_t->get_name():"");
    }

private:
    std::string _name;
    id_type _id;
    ObjectType *_t;
};

#endif //__OBJECT_H__
