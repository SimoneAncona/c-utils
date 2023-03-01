/**
 * @file string.h
 * @author Ancona Simone
 * @brief The string library adds strings and related functions, which are useful 
 * for making C code cleaner.
 * @version 1.0 (utils 1.0)
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _STRING_H_
#define _STRING_H_

#include "type.h"

#define __INITAL_STR_POOL_SIZE___ 10
#define __STR_POOL_BLOCK_SIZE___ 15
#define __NULL_STRING_POOL_INDEX__ 0
#ifndef __ENDING_CODE__
	#define __ENDING_CODE__ 0
#endif
#ifndef EQUAL
	#define EQUAL (uint8_t) true
#endif
#ifndef NOT_EQUAL
	#define NOT_EQUAL (uint8_t) false
#endif
#ifndef GRATER
	#define GRATER (uint8_t) 2
#endif
#ifndef LESS
	#define LESS (uint8_t) 3
#endif
#ifndef NOT_FOUND
	#define NOT_FOUND (size_t) -1
#endif

string_t __str_pool_ref__(char_ptr_t);	// since v1.0
string_t str_new_string(char_ptr_t);	// since v1.0
string_t str_lower_case(string_t);	// since v1.0
string_t str_upper_case(string_t);	// since v1.0
string_t str_substr(string_t, size_t, size_t);	// since v1.0
string_t str_replace(string_t, string_t, string_t);	// since v1.0
string_t str_concat(string_t, string_t);	// since v1.0
string_t str_from_char(char_t);	// since v1.0
string_t str_from_int(int_t);	// since v1.0
string_t str_from_int_base(int_t, uint8_t);	// since v1.0
string_t str_from_uint(uint_t);	// since v1.0
string_t str_from_uint_base(uint_t, uint8_t);	// since v1.0
string_t str_from_float(float);	// since v1.0
string_t str_from_double(double);	// since v1.0
string_t str_from_boolean(bool);	// since v1.0
string_t __str_to_string__(string_t);	// since v1.0
string_t __ustr_to_string__(unique_string_t);	// since v1.0
string_t vec_to_string(vector_t);	// since v1.0
string_t int_vec_to_string(int_vector_t);	// since v1.0
string_t uint_vec_to_string(uint_vector_t);	// since v1.0
string_t byte_vec_to_string(byte_vector_t);	// since v1.0
string_t float_vec_to_string(float_vector_t);	// since v1.0
string_t double_vec_to_string(double_vector_t);	// since v1.0
string_t bool_vec_to_string(boolean_vector_t);	// since v1.0
string_t str_vec_to_string(string_vector_t);	// since v1.0
string_t ustr_vec_to_string(ustring_vector_t);	// since v1.0
string_t any_to_string(any_t); 	// since v1.0
uint8_t str_cmp(string_t, string_t);	// since v1.0
char_t str_char_at(string_t, size_t);	// since v1.0
bool str_starts_with(string_t, string_t);	// since v1.0
bool str_ends_with(string_t, string_t);	// since v1.0
bool str_includes(string_t, string_t);	// since v1.0
bool str_destroy(string_t);	// since v1.0
bool str_is_int(string_t);	// since v1.0
bool str_is_number(string_t);	// since v1.0
bool str_is_alpha(string_t);	// since v1.0
bool str_is_alnum(string_t);	// since v1.0
bool str_is_identifier(string_t);	// since v1.0
bool str_is_lower(string_t);	// since v1.0
bool str_is_upper(string_t);	// since v1.0
#define str_equals(s1, s2) s1 == s2;	// since v1.0
bool __str_is_null__(string_t);	// since v1.0
size_t str_index_of(string_t, string_t);	// since v1.0
size_t str_last_index_of(string_t, string_t);	// since v1.0
size_t str_len(string_t);	// since v1.0
void __str_pool_append__(string_t);	// since v1.0
void __str_copy__(char_ptr_t, char_ptr_t);	// since v1.0

#endif