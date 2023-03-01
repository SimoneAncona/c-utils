#ifndef _NULL_H_
#define _NULL_H_

#include "type.h"

bool __int_is_null__(int_t); // since v1.0
bool __double_is_null__(double); // since v1.0
bool __ptr_is_null__(void*); // since v1.0

// STRING library
extern string_t str_null_string(void); // since v1.0

// UNIQUE STRING library
extern unique_string_t ustr_null_string(void); // since v1.0

// ANY library
extern bool __any_is_null__(any_t); // since v1.0

// VECTOR library
extern bool __vec_is_null__(vector_t v); // since v1.0
extern bool __int_vec_is_null__(int_vector_t v); // since v1.0
extern bool __uint_vec_is_null__(uint_vector_t v); // since v1.0
extern bool __byte_vec_is_null__(byte_vector_t v); // since v1.0
extern bool __float_vec_is_null__(float_vector_t v); // since v1.0
extern bool __double_vec_is_null__(double_vector_t v); // since v1.0
extern bool __bool_vec_is_null__(boolean_vector_t v); // since v1.0
extern bool __str_vec_is_null__(string_vector_t v); // since v1.0
extern bool __ustr_vec_is_null__(ustring_vector_t v); // since v1.0
extern int_vector_t int_vec_null_vector(); // since v1.0
extern uint_vector_t uint_vec_null_vector(); // since v1.0
extern byte_vector_t byte_vec_null_vector(); // since v1.0
extern float_vector_t float_vec_null_vector(); // since v1.0
extern double_vector_t double_vec_null_vector(); // since v1.0
extern boolean_vector_t bool_vec_null_vector(); // since v1.0
extern string_vector_t str_vec_null_vector(); // since v1.0
extern ustring_vector_t ustr_vec_null_vector(); // since v1.0

#endif