/**
 * @file unique_string.h
 * @author Ancona Simone
 * @brief The unique string library is part of the utils library collection
 * and string library collection. This libraryessentially offers the same 
 * functionality as the string library, without using a string pool
 * @version 1.0 (utils 1.0)
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _UNIQUE_STRING_H_
#define _UNIQUE_STRING_H_

#include "type.h"

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

#define __ustr_extend__(s, e) size_t old_size = ustr_len(s) + 1; s = realloc(s, (old_size + e) * sizeof(char_t)); for (size_t i = old_size; i < old_size + e; i++) s[i] = 0	// since v1.0
unique_string_t ustr_new_string(char_ptr_t);	// since v1.0
unique_string_t ustr_substr(unique_string_t, size_t, size_t);	// since v1.0
unique_string_t ustr_from_char(char_t);	// since v1.0
unique_string_t ustr_from_int(int_t);	// since v1.0
unique_string_t ustr_from_int_base(int64_t, uint8_t);	// since v1.0
unique_string_t ustr_from_uint(uint64_t);	// since v1.0
unique_string_t ustr_from_uint_base(uint64_t, uint8_t);	// since v1.0
unique_string_t ustr_from_float(float);	// since v1.0
unique_string_t ustr_from_double(double);	// since v1.0
unique_string_t ustr_from_boolean(bool);	// since v1.0
unique_string_t __str_to_ustring__(string_t);	// since v1.0
unique_string_t vec_to_ustring(vector_t);	// since v1.0
unique_string_t int_vec_to_ustring(int_vector_t);	// since v1.0
unique_string_t uint_vec_to_ustring(uint_vector_t);	// since v1.0
unique_string_t byte_vec_to_ustring(byte_vector_t);	// since v1.0
unique_string_t float_vec_to_ustring(float_vector_t);	// since v1.0
unique_string_t double_vec_to_ustring(double_vector_t);	// since v1.0
unique_string_t bool_vec_to_ustring(boolean_vector_t);	// since v1.0
unique_string_t str_vec_to_ustring(string_vector_t);	// since v1.0
unique_string_t ustr_vec_to_ustring(ustring_vector_t);	// since v1.0
unique_string_t any_to_ustring(any_t); 	// since v1.0
void ustr_lower_case(unique_string_t);	// since v1.0
void ustr_upper_case(unique_string_t);	// since v1.0
void ustr_concat(unique_string_t, unique_string_t);	// since v1.0
void ustr_replace(unique_string_t, unique_string_t, unique_string_t);	// since v1.0
void ustr_append(unique_string_t, char_t);	// since v1.0
void ustr_insert(unique_string_t, char_t, size_t);	// since v1.0
uint8_t ustr_cmp(unique_string_t, unique_string_t);	// since v1.0
char_t ustr_char_at(unique_string_t, size_t);	// since v1.0
bool ustr_starts_with(unique_string_t, unique_string_t);	// since v1.0
bool ustr_ends_with(unique_string_t, unique_string_t);	// since v1.0
bool ustr_includes(unique_string_t, unique_string_t);	// since v1.0
#define ustr_destroy(s) free((void*) s);	// since v1.0
bool ustr_is_int(unique_string_t);	// since v1.0
bool ustr_is_number(unique_string_t);	// since v1.0
bool ustr_is_alpha(unique_string_t);	// since v1.0
bool ustr_is_alnum(unique_string_t);	// since v1.0
bool ustr_is_identifier(unique_string_t);	// since v1.0
bool ustr_is_lower(unique_string_t);	// since v1.0
bool ustr_is_upper(unique_string_t);	// since v1.0
bool ustr_equals(unique_string_t, unique_string_t);	// since v1.0
size_t ustr_index_of(unique_string_t, unique_string_t);	// since v1.0
size_t ustr_last_index_of(unique_string_t, unique_string_t);	// since v1.0
size_t ustr_len(unique_string_t);	// since v1.0
void __ustr_copy__(char_ptr_t, char_ptr_t);	// since v1.0
void __ustr_shift_right__(unique_string_t, size_t);	// since v1.0

#endif