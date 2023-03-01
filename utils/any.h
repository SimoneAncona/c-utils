/**
 * @file any.h
 * @author Ancona Simone
 * @brief This library introduces the any type to improve
 * writing C code.
 * @version 1.0 (utils 1.0)
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#ifndef _ANY_H_
#define _ANY_H_

#include "type.h"

#define __any_alloc__() (any_t) malloc(sizeof(__any_struct_t__))
#define any_new(X) _Generic((X),\
	int16_t: __any_int__,\
	int32_t: __any_int__,\
	int64_t: __any_int__,\
	uint16_t: __any_uint__,\
	uint32_t: __any_uint__,\
	uint64_t: __any_uint__,\
	uint8_t: __any_byte__,\
	float: __any_float__,\
	double: __any_double__,\
	bool: __any_boolean__,\
	char_t: __any_char__,\
	string_t: __any_string__,\
	/*unique_string_t: __any_ustring__,*/\
	vector_t: __any_vector__,\
	int_vector_t: __any_int_vector__,\
	uint_vector_t: __any_uint_vector__,\
	byte_vector_t: __any_byte_vector__,\
	float_vector_t: __any_float_vector__,\
	double_vector_t: __any_double_vector__,\
	boolean_vector_t: __any_boolean_vector__,\
	string_vector_t: __any_string_vector__,\
	/*ustring_vector_t: __any_ustring_vector__,*/\
	int_t*: __any_int_ptr__,\
	uint_t*: __any_uint_ptr__,\
	uint8_t*: __any_byte_ptr__,\
	float*: __any_float_ptr__,\
	double*: __any_double_ptr__,\
	bool*: __any_boolean_ptr__,\
	default: __any_uint__\
) (X)


any_t __any_int__(int_t);	// since v1.0
any_t __any_uint__(uint_t);	// since v1.0
any_t __any_byte__(uint8_t);	// since v1.0
any_t __any_float__(float);	// since v1.0
any_t __any_double__(double);	// since v1.0
any_t __any_boolean__(bool);	// since v1.0
any_t __any_char__(char_t);	// since v1.0
any_t __any_string__(string_t);	// since v1.0
// any_t __any_ustring__(unique_string_t);	// since v1.1
any_t __any_vector__(vector_t);	// since v1.0
any_t __any_int_vector__(int_vector_t);	// since v1.0
any_t __any_uint_vector__(uint_vector_t);	// since v1.0
any_t __any_byte_vector__(byte_vector_t);	// since v1.0
any_t __any_float_vector__(float_vector_t);	// since v1.0
any_t __any_double_vector__(double_vector_t);	// since v1.0
any_t __any_boolean_vector__(boolean_vector_t);	// since v1.0
any_t __any_string_vector__(string_vector_t);	// since v1.0
any_t __any_ustring_vector__(ustring_vector_t);	// since v1.0
any_t __any_int_ptr__(int_t*);	// since v1.0	
any_t __any_uint_ptr__(uint_t*);	// since v1.0
any_t __any_byte_ptr__(uint8_t*);	// since v1.0
any_t __any_float_ptr__(float*);	// since v1.0	
any_t __any_double_ptr__(double*);	// since v1.0
any_t __any_boolean_ptr__(bool*);	// since v1.0
any_t any_null();	// since v1.0
bool any_is_int(any_t);	// since v1.0
bool any_is_uint(any_t);	// since v1.0
bool any_is_byte(any_t);	// since v1.0
bool any_is_float(any_t);	// since v1.0
bool any_is_double(any_t);	// since v1.0
bool any_is_boolean(any_t);	// since v1.0
bool any_is_char(any_t);	// since v1.0
bool any_is_string(any_t);	// since v1.0
bool any_is_vector(any_t);	// since v1.0
bool any_is_int_vector(any_t);	// since v1.0
bool any_is_uint_vector(any_t);	// since v1.0
bool any_is_byte_vector(any_t);	// since v1.0
bool any_is_float_vector(any_t);	// since v1.0
bool any_is_double_vector(any_t);	// since v1.0
bool any_is_boolean_vector(any_t);	// since v1.0
bool any_is_string_vector(any_t);	// since v1.0
bool any_is_int_ptr(any_t);	// since v1.0
bool any_is_uint_ptr(any_t);	// since v1.0
bool any_is_byte_ptr(any_t);	// since v1.0
bool any_is_float_ptr(any_t);	// since v1.0
bool any_is_double_ptr(any_t);	// since v1.0
bool any_is_boolean_ptr(any_t);	// since v1.0
int_t any_get_int(any_t);	// since v1.0
uint_t any_get_uint(any_t);	// since v1.0
uint8_t any_get_byte(any_t);	// since v1.0
float any_get_float(any_t);	// since v1.0
double any_get_double(any_t);	// since v1.0
bool any_get_boolean(any_t);	// since v1.0
char_t any_get_char(any_t);	// since v1.0
string_t any_get_string(any_t);	// since v1.0
vector_t any_get_vector(any_t);	// since v1.0
int_vector_t any_get_int_vector(any_t);	// since v1.0
uint_vector_t any_get_uint_vector(any_t);	// since v1.0
byte_vector_t any_get_byte_vector(any_t);	// since v1.0
float_vector_t any_get_float_vector(any_t);	// since v1.0
double_vector_t any_get_double_vector(any_t);	// since v1.0
boolean_vector_t any_get_boolean_vector(any_t);	// since v1.0
string_vector_t any_get_string_vector(any_t);	// since v1.0
int_t *any_get_int_ptr(any_t);	// since v1.0
uint_t *any_get_uint_ptr(any_t);	// since v1.0
uint8_t *any_get_byte_ptr(any_t);	// since v1.0
float *any_get_float_ptr(any_t);	// since v1.0
double *any_get_double_ptr(any_t);	// since v1.0
bool *any_get_boolean_ptr(any_t);	// since v1.0
string_ptr_t any_get_string_ptr(any_t);	// since v1.0
type_t any_typeof(any_t);	// since v1.0
// TODO: continue with other types

#endif