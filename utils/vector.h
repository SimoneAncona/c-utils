/**
 * @file vector.h
 * @author Ancona Simone
 * @brief This library includes dynamic vectors.
 * @version 01.0 (utils 1.0)
 * @date 2022-09-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef _VECTOR_H_
#define _VECTOR_H_

#define __VEC_BLOCK_SIZE__ 10

#include "type.h"
#include <stdarg.h>

extern bool str_destroy(string_t);

#define __vec_null_check__(v) v->__v__ == NULL && v->__len__ == 0

/**
 * Get the length of the vector
 * @param v the vector
 * @since v1.0
 */
#define vec_len(v) v->__len__

/**
 * Create a new vector
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define vector(l) vec_new_vector(l)

/**
 * Create a new vector of integers
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define int_vector(l) int_vec_new_vector(l)

/**
 * Create a new vector of unsigned integers
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define uint_vector(l) uint_vec_new_vector(l)

/**
 * Create a new vector of bytes
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define byte_vector(l) byte_vec_new_vector(l)

/**
 * Create a new vector of floats
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define float_vector(l) float_vec_new_vector(l)

/**
 * Create a new vector of doubles
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define double_vector(l) double_vec_new_vector(l)

/**
 * Create a new vector of strings
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define string_vector(l) str_vec_new_vector(l) // since v1.1

/**
 * Create a new vector of boolean
 * @param l the length of the vector
 * @return the new vector
 * @since v1.1
 */
#define boolean_vector(l) bool_vec_new_vector(l) // since v1.1

/**
 * Create a new vector
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
vector_t vec_new_vector(size_t);

/**
 * Get the null vector
 * @return the vull vector
 * @since v1.0
 */
vector_t vec_null_vector();

/**
 * Create a new vector of integers
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
int_vector_t int_vec_new_vector(size_t);

/**
 * Create a new vector of unsigned integers
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
uint_vector_t uint_vec_new_vector(size_t);

/**
 * Create a new vector of bytes
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
byte_vector_t byte_vec_new_vector(size_t);

/**
 * Create a new vector of floats
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
float_vector_t float_vec_new_vector(size_t);

/**
 * Create a new vector of double
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
double_vector_t double_vec_new_vector(size_t);

/**
 * Create a new vector of boolean
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
boolean_vector_t bool_vec_new_vector(size_t);

/**
 * Create a new vector of strings
 * @param len the length of the vector
 * @return the new vector
 * @since v1.0
 */
string_vector_t str_vec_new_vector(size_t);

/**
 * Destroy the given vector
 * @param x the vector
 * @since v1.0
 */
#define vec_destroy(x)                           \
	_Generic((x),                                \
		vector_t: __vec_destroy__,               \
		string_vector_t: __str_vector_destroy__, \
		default: __primitive_vector_destroy__)(x);                       \
	x = NULL

void __vec_destroy__(vector_t);				  // since v1.1
void __str_vector_destroy__(string_vector_t); // since v1.1
// #define __primitive_vector_destroy__(v) \
// 	free(v->__v__);                     \
// 	free(v);                            \
// 	v = NULL // since v1.1

void __primitive_vector_destroy__(void*);

size_t __vec_len__(vector_t);
size_t __int_vec_len__(int_vector_t);
size_t __uint_vec_len__(uint_vector_t);
size_t __byte_vec_len__(byte_vector_t);
size_t __float_vec_len__(float_vector_t);
size_t __double_vec_len__(double_vector_t);
size_t __boolean_vec_len__(boolean_vector_t);
size_t __str_vec_len__(string_vector_t);
// size_t __ustr_vec_len__(ustring_vector_t);	// since v1.2
#define __vec_append__(v, e)          \
	if (v->__len__ == v->__max_len__) \
		__vec_resize__(v);            \
	v->__v__[v->__len__] = e;         \
	v->__len__++
#define __vec_resize__(v) _Generic((v),  \
	vector_t: __vec_res__,               \
	int_vector_t: __int_vec_res__,       \
	uint_vector_t: __uint_vec_res__,     \
	byte_vector_t: __byte_vec_res__,     \
	float_vector_t: __float_vec_res__,   \
	double_vector_t: __double_vec_res__, \
	boolean_vector_t: __bool_vec_res__,  \
	string_vector_t: __str_vec_res__)(v)

void __vec_res__(vector_t);
void __int_vec_res__(int_vector_t);
void __uint_vec_res__(uint_vector_t);
void __byte_vec_res__(byte_vector_t);
void __float_vec_res__(float_vector_t);
void __double_vec_res__(double_vector_t);
void __bool_vec_res__(boolean_vector_t);
void __str_vec_res__(string_vector_t);
// void __ustr_vec_res__(ustring_vector_t);	// since v1.2

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.1
 */
#define vec_append(v, e) __vec_append__(v, any_new(e))

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void int_vec_append(int_vector_t, int_t);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void uint_vec_append(uint_vector_t, uint_t);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void byte_vec_append(byte_vector_t, uint8_t);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void float_vec_append(float_vector_t, float);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void double_vec_append(double_vector_t, double);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void bool_vec_append(boolean_vector_t, bool);

/**
 * Add a new element to the vector
 * @param v the vector
 * @param e the new element
 * @since v1.0
 */
void str_vec_append(string_vector_t, string_t);

#define __vec_get__(v, i) v->__v__[(size_t)i % v->__len__]
#define __vec_set__(v, i, e) v->__v__[(size_t)i % v->__len__] = e

/**
 * Set an element in the vector
 * @param v the vector
 * @param i the index of the element
 * @param e the new element
 * @since v1.0
 */
#define vec_set(v, i, e) __vec_set__(v, i, any_new(e))

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
any_t vec_get(vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
int_t int_vec_get(int_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
uint_t uint_vec_get(uint_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
uint8_t byte_vec_get(byte_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
float float_vec_get(float_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
double double_vec_get(double_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
bool bool_vec_get(boolean_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
string_t str_vec_get(string_vector_t, size_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void int_vec_set(int_vector_t, size_t, int_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void uint_vec_set(uint_vector_t, size_t, uint_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void byte_vec_set(byte_vector_t, size_t, uint8_t);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void float_vec_set(float_vector_t, size_t, float);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void double_vec_set(double_vector_t, size_t, double);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void bool_vec_set(boolean_vector_t, size_t, bool);

/**
 * Get an element of the vector
 * @param v the vector
 * @param i the index
 * @since v1.0
 */
void str_vec_set(string_vector_t, size_t, string_t);

#define __vec_subvec__(v, t, i1, i2)           \
	if (i1 > i2)                               \
		return NULL;                           \
	if (i1 >= v->__len__)                      \
		return NULL;                           \
	t new_vec;                                 \
	for (; i1 < i2; i1++)                      \
	{                                          \
		__vec_append__(new_vec, v->__v__[i1]); \
	}                                          \
	return new_vec;

#define vec_sort(v, r) _Generic((v), \
	int_vector_t: int_vec_sort,      \
	uint_vector_t: uint_vec_sort,    \
	byte_vector_t: byte_vec_sort,    \
	float_vector_t: float_vec_sort,  \
	double_vector_t: double_vec_sort)(v, r, 0, v->__len__)

void int_vec_sort(int_vector_t, bool, size_t, size_t);
void uint_vec_sort(uint_vector_t, bool, size_t, size_t);
void byte_vec_sort(byte_vector_t, bool, size_t, size_t);
void float_vec_sort(float_vector_t, bool, size_t, size_t);
void double_vec_sort(double_vector_t, bool, size_t, size_t);

vector_t vec_subvec(vector_t, size_t, size_t);
int_vector_t int_vec_subvec(int_vector_t, size_t, size_t);
uint_vector_t uint_vec_subvec(uint_vector_t, size_t, size_t);
byte_vector_t byte_vec_subvec(byte_vector_t, size_t, size_t);
float_vector_t float_vec_subvec(float_vector_t, size_t, size_t);
double_vector_t double_vec_subvec(double_vector_t, size_t, size_t);
boolean_vector_t bool_vec_subvec(boolean_vector_t, size_t, size_t);
string_vector_t str_vec_subvec(string_vector_t, size_t, size_t);

/**
 * Swap two elements of the vector
 * @param v the vector
 * @param i1 the first index
 * @param i2 the second index
 * @since v1.0
 */
#define vec_swap(v, i1, i2)                                                                                                    \
	v->__v__[(size_t)i1 % v->__len__] = (uint_t)v->__v__[(size_t)i1 % v->__len__] ^ (uint_t)v->__v__[(size_t)i2 % v->__len__]; \
	v->__v__[(size_t)i2 % v->__len__] = (uint_t)v->__v__[(size_t)i1 % v->__len__] ^ (uint_t)v->__v__[(size_t)i2 % v->__len__]; \
	v->__v__[(size_t)i1 % v->__len__] = (uint_t)v->__v__[(size_t)i1 % v->__len__] ^ (uint_t)v->__v__[(size_t)i2 % v->__len__]

/**
 * Reverse the vector
 * @param v the vector
 * @since v1.0
 */
#define vec_reverse(v)                          \
	for (size_t i = 0; i < v->__len__ / 2; i++) \
	{                                           \
		vec_swap(v, i, v->__len__ - 1 - i);     \
	}

#define __vec_remove__(v, i, t, n)         \
	if (i < v->__len__)                    \
	{                                      \
		t r = v->__v__[i];                 \
		for (; i < v->__len__ - 1; i++)    \
		{                                  \
			v->__v__[i] = v->__v__[i + 1]; \
		}                                  \
		v->__len__--;                      \
		return r;                          \
	}                                      \
	return n;

#define __vec_just_remove__(v, i)                   \
	if (i < v->__len__)                             \
	{                                               \
		for (size_t j = i; j < v->__len__ - 1; j++) \
		{                                           \
			v->__v__[j] = v->__v__[j + 1];          \
		}                                           \
		v->__len__--;                               \
	}

/**
 * Copy the vector src into the vector dest
 * @param dest the vector
 * @param src the vector to copy
 * @since v1.1
*/
#define vec_copy(dest, src)\
	vec_clear(dest);\
	for (size_t i = 0; i < src->__len__; i++)\
	{\
		_Generic((dest),\
			int_vector_t: int_vec_append,\
			uint_vector_t: uint_vec_append,\
			byte_vector_t: byte_vec_append,\
			float_vector_t: float_vec_append,\
			double_vector_t: double_vec_append,\
			boolean_vector_t: bool_vec_append,\
			string_vector_t: str_vec_append\
		)(dest, src->__v__[i]);\
	}\

/**
 * Remove all the elements from the vector
 * @param v the vector
 * @since v1.1
*/
#define vec_clear(v)\
	v->__len__ = 0

any_t vec_remove(vector_t, size_t);
int_t int_vec_remove(int_vector_t, size_t);
uint_t uint_vec_remove(uint_vector_t, size_t);
byte_t byte_vec_remove(byte_vector_t, size_t);
float float_vec_remove(float_vector_t, size_t);
double double_vec_remove(double_vector_t, size_t);
bool bool_vec_remove(boolean_vector_t, size_t);
string_t str_vec_remove(string_vector_t, size_t);

void vec_insert(vector_t, size_t, any_t);
void int_vec_insert(int_vector_t, size_t, int_t);
void uint_vec_insert(uint_vector_t, size_t, uint_t);
void byte_vec_insert(byte_vector_t, size_t, byte_t);
void float_vec_insert(float_vector_t, size_t, float);
void double_vec_insert(double_vector_t, size_t, double);
void bool_vec_insert(boolean_vector_t, size_t, bool);
void str_vec_insert(string_vector_t, size_t, string_t);

#define __vec_insert__(v, i, e)                     \
	if (i == v->__len__)\
	{\
		__vec_append__(v, e);\
	}\
	if (i < v->__len__)                         \
	{                                           \
		size_t j;\
		if (v->__len__ == v->__max_len__)\
		{\
			__vec_resize__(v);                  \
		}\
		v->__len__++;                           \
		for (j = v->__len__; j > i; j--) \
			v->__v__[j] = v->__v__[j - 1];      \
		v->__v__[i] = e;                        \
	}

vector_t vec_new_vector(size_t len)
{
	vector_t v = (vector_t)malloc(sizeof(__vector_struct_t__));
	v->__v__ = (any_ptr_t)malloc(sizeof(any_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = any_null();
	return v;
}

vector_t vec_null_vector()
{
	vector_t v = (vector_t)malloc(sizeof(__vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

int_vector_t int_vec_new_vector(size_t len)
{
	int_vector_t v = (int_vector_t)malloc(sizeof(__int_vector_struct_t__));
	v->__v__ = (int_t *)malloc(sizeof(int_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

int_vector_t int_vec_null_vector()
{
	int_vector_t v = (int_vector_t)malloc(sizeof(__int_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

uint_vector_t uint_vec_new_vector(size_t len)
{
	uint_vector_t v = (uint_vector_t)malloc(sizeof(__uint_vector_struct_t__));
	v->__v__ = (uint_t *)malloc(sizeof(uint_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

uint_vector_t uint_vec_null_vector()
{
	uint_vector_t v = (uint_vector_t)malloc(sizeof(__uint_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

byte_vector_t byte_vec_new_vector(size_t len)
{
	byte_vector_t v = (byte_vector_t)malloc(sizeof(__byte_vector_struct_t__));
	v->__v__ = (uint8_t *)malloc(sizeof(uint8_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

byte_vector_t byte_vec_null_vector()
{
	byte_vector_t v = (byte_vector_t)malloc(sizeof(__byte_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

float_vector_t float_vec_new_vector(size_t len)
{
	float_vector_t v = (float_vector_t)malloc(sizeof(__float_vector_struct_t__));
	v->__v__ = (float *)malloc(sizeof(float) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

float_vector_t float_vec_null_vector()
{
	float_vector_t v = (float_vector_t)malloc(sizeof(__float_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

double_vector_t double_vec_new_vector(size_t len)
{
	double_vector_t v = (double_vector_t)malloc(sizeof(__double_vector_struct_t__));
	v->__v__ = (double *)malloc(sizeof(double) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

double_vector_t double_vec_null_vector()
{
	double_vector_t v = (double_vector_t)malloc(sizeof(__double_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

boolean_vector_t bool_vec_new_vector(size_t len)
{
	boolean_vector_t v = (boolean_vector_t)malloc(sizeof(__boolean_vector_struct_t__));
	v->__v__ = (bool *)malloc(sizeof(bool) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = false;
	return v;
}

boolean_vector_t bool_vec_null_vector()
{
	boolean_vector_t v = (boolean_vector_t)malloc(sizeof(__boolean_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

string_vector_t str_vec_new_vector(size_t len)
{
	string_vector_t v = (string_vector_t)malloc(sizeof(__string_vector_struct_t__));
	v->__v__ = (string_ptr_t)malloc(sizeof(string_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = str_null_string();
	return v;
}

string_vector_t str_vec_null_vector()
{
	string_vector_t v = (string_vector_t)malloc(sizeof(__string_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

// ustring_vector_t ustr_vec_new_vector(size_t len)
// {
// 	ustring_vector_t v = (ustring_vector_t) malloc(sizeof(__ustring_vector_struct_t__));
// 	v->__v__ = (unique_string_ptr_t) malloc(sizeof(unique_string_t) * len);
// 	v->__len__ = len;
// 	v->__max_len__ = len;
// 	for (size_t i = 0; i < len; i++)
// 		v->__v__[i] = ustr_null_string();
// 	return v;
// }

// ustring_vector_t ustr_vec_null_vector()
// {
// 	ustring_vector_t v = (ustring_vector_t) malloc(sizeof(__ustring_vector_struct_t__));
// 	v->__v__ = NULL;
// 	v->__len__ = 0;
// 	v->__max_len__ = 0;
// 	return v;
// }

bool __vec_is_null__(vector_t v) { return __vec_null_check__(v); }
bool __int_vec_is_null__(int_vector_t v) { return __vec_null_check__(v); }
bool __uint_vec_is_null__(uint_vector_t v) { return __vec_null_check__(v); }
bool __byte_vec_is_null__(byte_vector_t v) { return __vec_null_check__(v); }
bool __float_vec_is_null__(float_vector_t v) { return __vec_null_check__(v); }
bool __double_vec_is_null__(double_vector_t v) { return __vec_null_check__(v); }
bool __bool_vec_is_null__(boolean_vector_t v) { return __vec_null_check__(v); }
bool __str_vec_is_null__(string_vector_t v) { return __vec_null_check__(v); }
// bool __ustr_vec_is_null__(ustring_vector_t v) { return __vec_null_check__(v); }
size_t __vec_len__(vector_t v) { return v->__len__; }
size_t __int_vec_len__(int_vector_t v) { return v->__len__; }
size_t __uint_vec_len__(uint_vector_t v) { return v->__len__; }
size_t __byte_vec_len__(byte_vector_t v) { return v->__len__; }
size_t __float_vec_len__(float_vector_t v) { return v->__len__; }
size_t __double_vec_len__(double_vector_t v) { return v->__len__; }
size_t __bool_vec_len__(boolean_vector_t v) { return v->__len__; }
size_t __str_vec_len__(string_vector_t v) { return v->__len__; }
// size_t __ustr_vec_len__(ustring_vector_t v) { return v->__len__; }

void __vec_res__(vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (any_ptr_t)realloc(v->__v__, sizeof(any_t) * v->__max_len__);
}

void __int_vec_res__(int_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (int_t *)realloc(v->__v__, sizeof(int_t) * v->__max_len__);
}

void __uint_vec_res__(uint_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (uint_t *)realloc(v->__v__, sizeof(uint_t) * v->__max_len__);
}

void __byte_vec_res__(byte_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (uint8_t *)realloc(v->__v__, sizeof(uint8_t) * v->__max_len__);
}

void __float_vec_res__(float_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (float *)realloc(v->__v__, sizeof(float) * v->__max_len__);
}

void __double_vec_res__(double_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (double *)realloc(v->__v__, sizeof(double) * v->__max_len__);
}

void __bool_vec_res__(boolean_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (bool *)realloc(v->__v__, sizeof(bool) * v->__max_len__);
}

void __str_vec_res__(string_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (string_ptr_t)realloc(v->__v__, sizeof(string_t) * v->__max_len__);
}

void __ustr_vec_res__(ustring_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (unique_string_ptr_t)realloc(v->__v__, sizeof(unique_string_t) * v->__max_len__);
}

#define __vec_init__(len, t, v)        \
	va_list args;                      \
	va_start(args, len);               \
	for (size_t i = 0; i < len; i++)   \
	{                                  \
		v->__v__[i] = va_arg(args, t); \
	}                                  \
	return v;

#define __vec_any_init__(len)                       \
	vector_t v = vector(len);                       \
	va_list args;                                   \
	va_start(args, len);                            \
	for (size_t i = 0; i < len; i++)                \
	{                                               \
		v->__v__[i] = any_new(va_arg(args, any_t)); \
	}                                               \
	return v;

#define __str_vec_init__(len)                                   \
	string_vector_t v = string_vector(len);                     \
	va_list args;                                               \
	va_start(args, len);                                        \
	for (size_t i = 0; i < len; i++)                            \
	{                                                           \
		v->__v__[i] = str_new_string(va_arg(args, char_ptr_t)); \
	}                                                           \
	return v;

#define __vec_sort__(v, r, start, end, ins)         \
	if (end - start <= 1)                      \
		return;                                \
	size_t i;                                  \
	size_t p = start;                              \
	for (i = start + 1; i < end; i++)          \
	{                                          \
		if (v->__v__[i] < v->__v__[p])     \
		{                                      \
			ins(v, start, v->__v__[i]); \
			__vec_just_remove__(v, i + 1);     \
			p++;                               \
		}                                      \
	}                                          \
	r(v, false, start, p + 1);                 \
	r(v, false, p + 1, end);

vector_t vec_init(size_t len, ...);
int_vector_t int_vec_init(size_t len, ...);
uint_vector_t uint_vec_init(size_t len, ...);
byte_vector_t byte_vec_init(size_t len, ...);
float_vector_t float_vec_init(size_t len, ...);
double_vector_t double_vec_init(size_t len, ...);
boolean_vector_t bool_vec_init(size_t len, ...);
string_vector_t str_vec_init(size_t len, ...);

void int_vec_append(int_vector_t v, int_t e) { __vec_append__(v, e); }
void uint_vec_append(uint_vector_t v, uint_t e) { __vec_append__(v, e); }
void byte_vec_append(byte_vector_t v, byte_t e) { __vec_append__(v, e); }
void float_vec_append(float_vector_t v, float e) { __vec_append__(v, e); }
void double_vec_append(double_vector_t v, double e) { __vec_append__(v, e); }
void bool_vec_append(boolean_vector_t v, bool e) { __vec_append__(v, e); }
void str_vec_append(string_vector_t v, string_t e) { __vec_append__(v, e); }
// void ustr_vec_append(ustring_vector_t v, unique_string_t e) { __vec_append__(v, e); }

any_t vec_get(vector_t v, size_t i) { return __vec_get__(v, i); }
int_t int_vec_get(int_vector_t v, size_t i) { return __vec_get__(v, i); }
uint_t uint_vec_get(uint_vector_t v, size_t i) { return __vec_get__(v, i); }
uint8_t byte_vec_get(byte_vector_t v, size_t i) { return __vec_get__(v, i); }
float float_vec_get(float_vector_t v, size_t i) { return __vec_get__(v, i); }
double double_vec_get(double_vector_t v, size_t i) { return __vec_get__(v, i); }
bool bool_vec_get(boolean_vector_t v, size_t i) { return __vec_get__(v, i); }
string_t str_vec_get(string_vector_t v, size_t i) { return __vec_get__(v, i); }
unique_string_t ustr_vec_get(ustring_vector_t v, size_t i) { return __vec_get__(v, i); }
void int_vec_set(int_vector_t v, size_t i, int_t e) { __vec_set__(v, i, e); }
void uint_vec_set(uint_vector_t v, size_t i, uint_t e) { __vec_set__(v, i, e); }
void byte_vec_set(byte_vector_t v, size_t i, byte_t e) { __vec_set__(v, i, e); }
void float_vec_set(float_vector_t v, size_t i, float e) { __vec_set__(v, i, e); }
void double_vec_set(double_vector_t v, size_t i, double e) { __vec_set__(v, i, e); }
void bool_vec_set(boolean_vector_t v, size_t i, bool e) { __vec_set__(v, i, e); }
void str_vec_set(string_vector_t v, size_t i, string_t e) { __vec_set__(v, i, e); }
void ustr_vec_set(ustring_vector_t v, size_t i, unique_string_t e) { __vec_set__(v, i, e); }

#define __vec_from_array__(array, len)    \
	vector_t v = vec_new_vector(len);     \
	for (size_t i = 0; i < len; i++)      \
	{                                     \
		vec_append(v, any_new(array[i])); \
	}                                     \
	return v

vector_t vec_from_int_array(int *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_uint_array(uint_t *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_byte_array(byte_t *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_float_array(float *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_double_array(double *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_boolean_array(bool *array, size_t len) { __vec_from_array__(array, len); }
vector_t vec_from_string_array(string_t *array, size_t len) { __vec_from_array__(array, len); }

void __vec_destroy__(vector_t v)
{
	for (size_t i = 0; i < v->__len__; i++)
		free(__vec_get__(v, i));
	free(v);
}

void __str_vector_destroy__(string_vector_t v)
{
	for (size_t i = 0; i < v->__len__; i++)
		str_destroy(__vec_get__(v, i));
	free(v);
}


void __primitive_vector_destroy__(void *v)
{
	free(((int_vector_t)v)->__v__);
	free(v);
}

vector_t vec_subvec(vector_t v, size_t start, size_t end) { __vec_subvec__(v, vector_t, start, end); }
int_vector_t int_vec_subvec(int_vector_t v, size_t start, size_t end) { __vec_subvec__(v, int_vector_t, start, end); }
uint_vector_t uint_vec_subvec(uint_vector_t v, size_t start, size_t end) { __vec_subvec__(v, uint_vector_t, start, end); }
byte_vector_t byte_vec_subvec(byte_vector_t v, size_t start, size_t end) { __vec_subvec__(v, byte_vector_t, start, end); }
float_vector_t float_vec_subvec(float_vector_t v, size_t start, size_t end) { __vec_subvec__(v, float_vector_t, start, end); }
double_vector_t double_vec_subvec(double_vector_t v, size_t start, size_t end) { __vec_subvec__(v, double_vector_t, start, end); }
boolean_vector_t bool_vec_subvec(boolean_vector_t v, size_t start, size_t end) { __vec_subvec__(v, boolean_vector_t, start, end); }
string_vector_t str_vec_subvec(string_vector_t v, size_t start, size_t end) { __vec_subvec__(v, string_vector_t, start, end); }

extern string_t int_vec_to_string(int_vector_t);

void int_vec_sort(int_vector_t v, bool reversed, size_t start, size_t end)
{
	__vec_sort__(v, int_vec_sort, start, end, int_vec_insert);
	if (reversed)
		vec_reverse(v);
}

void uint_vec_sort(uint_vector_t v, bool reversed, size_t start, size_t end)
{
	__vec_sort__(v, uint_vec_sort, start, end, uint_vec_insert);
	if (reversed)
		vec_reverse(v);
}

void byte_vec_sort(byte_vector_t v, bool reversed, size_t start, size_t end)
{
	__vec_sort__(v, byte_vec_sort, start, end, byte_vec_insert);
	if (reversed)
		vec_reverse(v);
}

void float_vec_sort(float_vector_t v, bool reversed, size_t start, size_t end)
{
	__vec_sort__(v, float_vec_sort, start, end, float_vec_insert);
	if (reversed)
		vec_reverse(v);
}

void double_vec_sort(double_vector_t v, bool reversed, size_t start, size_t end)
{
	__vec_sort__(v, double_vec_sort, start, end, double_vec_insert);
	if (reversed)
		vec_reverse(v);
}

vector_t vec_init(size_t len, ...) { __vec_any_init__(len); }
int_vector_t int_vec_init(size_t len, ...)
{
	int_vector_t v = int_vector(len);
	__vec_init__(len, int, v);
}
uint_vector_t uint_vec_init(size_t len, ...)
{
	uint_vector_t v = uint_vector(len);
	__vec_init__(len, int, v);
}
byte_vector_t byte_vec_init(size_t len, ...)
{
	byte_vector_t v = byte_vector(len);
	__vec_init__(len, int, v);
}
float_vector_t float_vec_init(size_t len, ...)
{
	float_vector_t v = float_vector(len);
	__vec_init__(len, double, v);
}
double_vector_t double_vec_init(size_t len, ...)
{
	double_vector_t v = double_vector(len);
	__vec_init__(len, double, v);
}
boolean_vector_t bool_vec_init(size_t len, ...)
{
	boolean_vector_t v = boolean_vector(len);
	__vec_init__(len, int, v);
}

string_vector_t str_vec_init(size_t len, ...) { __str_vec_init__(len); }

any_t vec_remove(vector_t v, size_t i) { __vec_remove__(v, i, any_t, NULL); }
int_t int_vec_remove(int_vector_t v, size_t i) { __vec_remove__(v, i, int_t, 0); }
uint_t uint_vec_remove(uint_vector_t v, size_t i) { __vec_remove__(v, i, uint_t, 0); }
byte_t byte_vec_remove(byte_vector_t v, size_t i) { __vec_remove__(v, i, byte_t, 0); }
float float_vec_remove(float_vector_t v, size_t i) { __vec_remove__(v, i, float, 0); }
double double_vec_remove(double_vector_t v, size_t i) { __vec_remove__(v, i, double, 0); }
bool bool_vec_remove(boolean_vector_t v, size_t i) { __vec_remove__(v, i, bool, false); }
string_t str_vec_remove(string_vector_t v, size_t i) { __vec_remove__(v, i, string_t, str_null_string()); }

void vec_insert(vector_t v, size_t i, any_t e) { __vec_insert__(v, i, e); }
void int_vec_insert(int_vector_t v, size_t i, int_t e) { __vec_insert__(v, i, e); }
void uint_vec_insert(uint_vector_t v, size_t i, uint_t e) { __vec_insert__(v, i, e); }
void byte_vec_insert(byte_vector_t v, size_t i, byte_t e) { __vec_insert__(v, i, e); }
void float_vec_insert(float_vector_t v, size_t i, float e) { __vec_insert__(v, i, e); }
void double_vec_insert(double_vector_t v, size_t i, double e) { __vec_insert__(v, i, e); }
void bool_vec_insert(boolean_vector_t v, size_t i, bool e) { __vec_insert__(v, i, e); }
void str_vec_insert(string_vector_t v, size_t i, string_t e) { __vec_insert__(v, i, e); }

#endif