#ifndef __COMMON_H__
#define __COMMON_H__

#include<bits/stdc++.h>
#include<filesystem>

#define PROGRAM_FREQUENCY 10000
#define INF 1000000000
#define NATURAL_ORDERING true
#define POINTER_LANDMARKS true

#define ERROR_INPUT (-1)
#define ERROR_DOMAIN_DOES_NOT_EXIST (-2)
#define ERROR_PARSING_DOMAIN (-3)
#define ERROR_PARSING_INSTANCE (-4)
#define ERROR_UNKNOWN_EVALUATION_FUNCTION (-5)
#define ERROR_TYPE_DOES_NOT_EXIST (-6)
#define ERROR_PROGRAM_DOES_NOT_EXIST (-7)
#define ERROR_INSTRUCTION_DOES_NOT_EXIST (-8)
#define ERROR_OUTPUT_DIRECTORY (-9)
#define ERROR_UNKNOWN_THEORY (-10)
#define ERROR_INCORRECT_PROGRAM (-11)
#define ERROR_INAPPLICABLE_INSTRUCTION (-12)
#define ERROR_INFINITE_PROGRAM (-13)
#define ERROR_DEADEND (-14)

#define NAME_VAR_TYPE_PREDICATE "predicate" // FIXME (Issue #32): delete this macro
#define NAME_VAR_TYPE_CONSTANT "constant" // FIXME (Issue #32): delete this macro
#define NAME_VAR_TYPE_POINTER "pointer" // FIXME (Issue #32): delete this macro
//enum class VarType{ pointer_t, constant_t, predicate_t}; // FIXME (Issue #32): create enum class for var types

#define NAME_ACT_TYPE_MATH "math" // FIXME (Issue #32): delete this macro
#define NAME_ACT_TYPE_MEMORY "memory" // FIXME (Issue #32): delete this macro
// FIXME (Issue #32): create an enum class for action types

typedef long long value_t;
typedef unsigned long long uvalue_t; // change this type depending on what is value_t
typedef long long id_type;  // constants require id_type to be long long
typedef std::vector<bool> vec_bool_t;
typedef std::vector<std::string> vec_str_t;
typedef std::vector<id_type> vec_id_t;
typedef std::vector<value_t> vec_value_t;
typedef std::set<id_type> set_id_t;
typedef std::set<value_t> set_value_t;
typedef std::map<std::string,size_t> map_str_idx_t;

#define MaxValue LLONG_MAX
#define MaxUValue ULLONG_MAX

#endif
