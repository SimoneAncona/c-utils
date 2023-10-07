/**
 * @file common.h
 * @author Ancona Simone
 * @brief This library is a common library between
 * libraries belonging to the utils library collection
 * @version 1.0 (utils 1.0)
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "type.h"

#pragma once

#define len(X) _Generic((X),\
	string_t: str_len,\
	unique_string_t: ustr_len,\
	vector_t: __vec_len__,\
	int_vector_t: __int_vec_len__,\
	uint_vector_t: __uint_vec_len__,\
	byte_vector_t: __byte_vec_len__,\
	float_vector_t: __float_vec_len__,\
	double_vector_t: __double_vec_len__,\
	boolean_vector_t: __boolean_vec_len__\
) (X) // since v1.0

#define is_null(X) _Generic((X),\
	int8_t: __int_is_null__,\
	int16_t: __int_is_null__,\
	int32_t: __int_is_null__,\
	int64_t: __int_is_null__,\
	uint8_t: __int_is_null__,\
	uint16_t: __int_is_null__,\
	uint32_t: __int_is_null__,\
	uint64_t: __int_is_null__,\
	float: __float_is_null__,\
	double: __double_is_null__,\
	void*: __ptr_is_null__,\
	string_t: __str_is_null__,\
	vector_t: __vec_is_null__,\
	int_vector_t: __int_vec_is_null__,\
	uint_vector_t: __uint_vec_is_null__,\
	byte_vector_t: __byte_vec_is_null__,\
	float_vector_t: __float_vec_is_null__,\
	double_vector_t: __double_vec_is_null__,\
	boolean_vector_t: __bool_vec_is_null__,\
	string_vector_t: __str_vec_is_null__,\
	ustring_vector_t: __ustr_vec_is_null__,\
	any_t: __any_is_null__\
) (X) // since v1.0

#define to_string(X) _Generic((X),\
	int16_t: str_from_int,\
	int32_t: str_from_int,\
	int64_t: str_from_int,\
	uint16_t: str_from_uint,\
	uint32_t: str_from_uint,\
	uint64_t: str_from_uint,\
	float: str_from_float,\
	double: str_from_double,\
	bool: str_from_boolean,\
	char_t: str_from_char,\
	string_t: __str_to_string__,\
	unique_string_t: __ustr_to_string__,\
	any_t: any_to_string,\
	vector_t: vec_to_string,\
	int_vector_t: int_vec_to_string,\
	uint_vector_t: uint_vec_to_string,\
	byte_vector_t: byte_vec_to_string,\
	float_vector_t: float_vec_to_string,\
	double_vector_t: double_vec_to_string,\
	boolean_vector_t: bool_vec_to_string,\
	string_vector_t: str_vec_to_string,\
	ustring_vector_t: ustr_vec_to_string,\
	map_t: map_to_string,\
	default: str_from_uint\
) (X) // since v1.0

#define to_unique_string(X) _Generic((X),\
	int8_t: ustr_from_int,\
	int16_t: ustr_from_int,\
	int32_t: ustr_from_int,\
	int64_t: ustr_from_int,\
	uint16_t: ustr_from_uint,\
	uint32_t: ustr_from_uint,\
	uint64_t: ustr_from_uint,\
	float: ustr_from_float,\
	double: ustr_from_double,\
	bool: ustr_from_boolean,\
	char_t: ustr_from_char,\
	string_t: __str_to_ustring__,\
	any_t: any_to_ustring,\
	vector_t: vec_to_ustring,\
	int_vector_t: int_vec_to_ustring,\
	uint_vector_t: uint_vec_to_ustring,\
	byte_vector_t: byte_vec_to_ustring,\
	float_vector_t: float_vec_to_ustring,\
	double_vector_t: double_vec_to_ustring,\
	boolean_vector_t: bool_vec_to_ustring,\
	string_vector_t: str_vec_to_ustring,\
	ustring_vector_t: ustr_vec_to_ustring,\
	default: ustr_from_uint\
) (X) // since v1.0