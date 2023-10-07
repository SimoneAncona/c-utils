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

#pragma once

#ifndef _ANY_H_
#define _ANY_H_

#include "type.h"

extern string_t str_new_string(char_ptr_t);

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
	char_ptr_t: __any_cstring__,\
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
any_t __any_cstring__(char_ptr_t);	// since v1.1
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
bool any_equals(any_t, any_t);	// since v1.1
// TODO: continue with other types


any_t __any_int__(int_t n)
{
	any_t a = __any_alloc__();
	a->__t__ = INTEGER;
	a->__value__ = (uint_t) n;

	return a;
}

any_t __any_uint__(uint_t n)
{
	any_t a = __any_alloc__();
	a->__t__ = UNSIGNED_INTEGER;
	a->__value__ = (uint_t) n;

	return a;
}

any_t __any_byte__(uint8_t b)
{
	any_t a = __any_alloc__();
	a->__t__ = BYTE;
	a->__value__ = (uint_t) b;
	
	return a;
}

any_t __any_float__(float f)
{
	any_t a = __any_alloc__();
	a->__t__ = FLOAT;
	a->__value__ = (uint_t) f;

	return a;
}

any_t __any_double__(double d)
{
	any_t a = __any_alloc__();
	a->__t__ = DOUBLE;
	a->__value__ = (uint_t) d;

	return a;
}

any_t __any_boolean__(bool d)
{
	any_t a = __any_alloc__();
	a->__t__ = BOOLEAN;
	a->__value__ = (uint_t) d;

	return a;
}

any_t __any_char__(char_t c)
{
	any_t a = __any_alloc__();
	char_t *p = (char_t*) malloc(sizeof(char_t));
	*p = c;
	a->__t__ = CHAR;
	a->__value__ = (uint_t) p;

	return a;
}

any_t __any_cstring__(char_ptr_t s)
{
	any_t a = __any_alloc__();
	a->__t__ = STRING;
	a->__value__ = (uint_t) str_new_string(s);

	return a;
}

any_t __any_string__(string_t s)
{
	any_t a = __any_alloc__();
	a->__t__ = STRING;
	a->__value__ = (uint_t) s;

	return a;
}

any_t __any_ustring__(unique_string_t u)
{
	any_t a = __any_alloc__();
	unique_string_t *p = (unique_string_t*) malloc(sizeof(unique_string_t));
	*p = u;
	a->__t__ = STRING;
	a->__value__ = (uint_t) p;

	return a;
}

any_t __any_vector__(vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_int_vector__(int_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = INTEGER_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_uint_vector__(uint_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = UNSIGNED_INTEGER_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_byte_vector__(byte_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = BYTE_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_float_vector__(float_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = FLOAT_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_double_vector__(double_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = DOUBLE_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_boolean_vector__(boolean_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = BOOLEAN_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_string_vector__(string_vector_t v)
{
	any_t a = __any_alloc__();
	a->__t__ = STRING_VECTOR;
	a->__value__ = (uint_t) v;

	return a;
}

any_t __any_ustring_vector__(ustring_vector_t v)
{
	any_t a = __any_alloc__();
	ustring_vector_t *p = (ustring_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = STRING_VECTOR;
	a->__value__ = (uint_t) p;

	return a;
}

any_t __any_int_ptr__(int_t *r) 
{
	any_t a = __any_alloc__();
	a->__t__ = INTEGER_PTR;
	a->__value__ = (uint_t) r;

	return a;
}	

any_t __any_uint_ptr__(uint_t *r) 
{
	any_t a = __any_alloc__();
	a->__t__ = UNSIGNED_INTEGER_PTR;
	a->__value__ = (uint_t) r;

	return a;
}

any_t __any_byte_ptr__(uint8_t *r) 
{
	any_t a = __any_alloc__();
	a->__t__ = BYTE_PTR;
	a->__value__ = (uint_t) r;

	return a;
}

any_t __any_float_ptr__(float *r) 
{
	any_t a = __any_alloc__();
	a->__t__ = FLOAT_PTR;
	a->__value__ = (uint_t) r;

	return a;
}	

any_t __any_double_ptr__(double *r)
{
	any_t a = __any_alloc__();
	a->__t__ = DOUBLE_PTR;
	a->__value__ = (uint_t) r;

	return a;
}

any_t __any_boolean_ptr__(bool *r)
{
	any_t a = __any_alloc__();
	a->__t__ = STRING_VECTOR;
	a->__value__ = (uint_t) r;

	return a;
}

bool any_is_int(any_t a) { return a->__t__ == INTEGER; }
bool any_is_uint(any_t a) { return a->__t__ == UNSIGNED_INTEGER; }
bool any_is_byte(any_t a) { return a->__t__ == BYTE; }
bool any_is_float(any_t a) { return a->__t__ == FLOAT; }
bool any_is_double(any_t a) { return a->__t__ == DOUBLE; }
bool any_is_boolean(any_t a) { return a->__t__ == BOOLEAN; }
bool any_is_char(any_t a) { return a->__t__ == CHAR; }
bool any_is_string(any_t a) { return a->__t__ == STRING; }
bool any_is_vector(any_t a) { return a->__t__ == VECTOR; }
bool any_is_int_vector(any_t a) { return a->__t__ == INTEGER_VECTOR; }
bool any_is_uint_vector(any_t a) { return a->__t__ == UNSIGNED_INTEGER_VECTOR; }
bool any_is_byte_vector(any_t a) { return a->__t__ == BYTE_VECTOR; }
bool any_is_float_vector(any_t a) { return a->__t__ == FLOAT_VECTOR; }
bool any_is_double_vector(any_t a) { return a->__t__ == DOUBLE_VECTOR; }
bool any_is_boolean_vector(any_t a) { return a->__t__ == BOOLEAN_VECTOR; }
bool any_is_string_vector(any_t a) { return a->__t__ == STRING_VECTOR; }
bool any_is_int_ptr(any_t a) { return a->__t__ == INTEGER_PTR; }
bool any_is_uint_ptr(any_t a) { return a->__t__ == UNSIGNED_INTEGER_PTR; }
bool any_is_byte_ptr(any_t a) { return a->__t__ == BYTE_PTR; }
bool any_is_float_ptr(any_t a) { return a->__t__ == FLOAT_PTR; }
bool any_is_double_ptr(any_t a) { return a->__t__ == DOUBLE_PTR; }
bool any_is_boolean_ptr(any_t a) { return a->__t__ == BOOLEAN_PTR; }
int_t any_get_int(any_t a) { return (int_t) (a->__value__); }
uint_t any_get_uint(any_t a) { return (uint_t) (a->__value__); }
uint8_t any_get_byte(any_t a) { return (uint8_t) (a->__value__); }
float any_get_float(any_t a) { return (float) (a->__value__); }
double any_get_double(any_t a) { return (double) (a->__value__); }
bool any_get_boolean(any_t a) { return (bool) (a->__value__); }
char_t any_get_char(any_t a) { return (char_t) (a->__value__); }
string_t any_get_string(any_t a) { return (string_t) (a->__value__); }
vector_t any_get_vector(any_t a) { return (vector_t) (a->__value__); }
int_vector_t any_get_int_vector(any_t a) { return (int_vector_t) (a->__value__); }
uint_vector_t any_get_uint_vector(any_t a) { return (uint_vector_t) (a->__value__); }
byte_vector_t any_get_byte_vector(any_t a) { return (byte_vector_t) (a->__value__); }
float_vector_t any_get_float_vector(any_t a) { return (float_vector_t) (a->__value__); }
double_vector_t any_get_double_vector(any_t a) { return (double_vector_t) (a->__value__); }
boolean_vector_t any_get_boolean_vector(any_t a) { return (boolean_vector_t) (a->__value__); }
string_vector_t any_get_string_vector(any_t a) { return (string_vector_t) (a->__value__); }
map_t any_get_map(any_t a) { return (map_t) (a->__value__); }
int_t *any_get_int_ptr(any_t a) { return (int_t*) (a->__value__); }
uint_t *any_get_uint_ptr(any_t a) { return (uint_t*) (a->__value__); }
uint8_t *any_get_byte_ptr(any_t a) { return (uint8_t*) (a->__value__); }
float *any_get_float_ptr(any_t a) { return (float*) (a->__value__); }
double *any_get_double_ptr(any_t a) { return (double*) (a->__value__); }
bool *any_get_boolean_ptr(any_t a) { return (bool*) (a->__value__); }
type_t any_typeof(any_t a) { return a->__t__; }

any_t any_null()
{
	any_t a = __any_alloc__();
	a->__t__ = NONE_TYPE;
	a->__value__ = 0;
	return a;
}

bool __any_is_null__(any_t a)
{
	return a == NULL || a->__t__ == NONE_TYPE && a->__value__ == 0;
}

bool any_equals(any_t a, any_t b)
{
	if (a->__t__ != b->__t__) return false;
	switch (a->__t__)
	{
	case NONE_TYPE: return false;
	case INTEGER:
	case UNSIGNED_INTEGER:
	case FLOAT:
	case DOUBLE:
	case BOOLEAN:
	case CHAR:
	case STRING:
	case BYTE:
	case INTEGER_PTR:
	case UNSIGNED_INTEGER_PTR:
	case FLOAT_PTR:
	case DOUBLE_PTR:
	case BOOLEAN_PTR:
	case STRING_PTR:
	case BYTE_PTR:
		return a->__value__ == b->__value__;
	case VECTOR:
		return false;
	case MAP:
		return false;
	default:
		return false;
	}
}

#endif