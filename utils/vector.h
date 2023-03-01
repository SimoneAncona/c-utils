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

#ifndef _VECTOR_H_
#define _VECTOR_H_

#define __VEC_BLOCK_SIZE__ 10

#include "type.h"

#define __vec_null_check__(v) v->__v__ == NULL && v->__len__ == 0	// since v1.0
#define vec_len(v) v->__len__	// since v1.0
vector_t vec_new_vector(size_t);	// since v1.0
vector_t vec_null_vector();	// since v1.0
int_vector_t int_vec_new_vector(size_t);	// since v1.0
uint_vector_t uint_vec_new_vector(size_t);	// since v1.0
byte_vector_t byte_vec_new_vector(size_t);	// since v1.0
float_vector_t float_vec_new_vector(size_t);	// since v1.0
double_vector_t double_vec_new_vector(size_t);	// since v1.0
boolean_vector_t bool_vec_new_vector(size_t);	// since v1.0
string_vector_t str_vec_new_vector(size_t);	// since v1.0
// ustring_vector_t ustr_vec_new_vector(size_t);	// since v1.2
#define vec_destroy(X) free(X)	// since v1.0
size_t __vec_len__(vector_t);	// since v1.0
size_t __int_vec_len__(int_vector_t);	// since v1.0
size_t __uint_vec_len__(uint_vector_t);	// since v1.0
size_t __byte_vec_len__(byte_vector_t);	// since v1.0
size_t __float_vec_len__(float_vector_t);	// since v1.0
size_t __double_vec_len__(double_vector_t);	// since v1.0
size_t __boolean_vec_len__(boolean_vector_t);	// since v1.0
size_t __str_vec_len__(string_vector_t);	// since v1.0
// size_t __ustr_vec_len__(ustring_vector_t);	// since v1.2
#define __vec_append__(v, e)\
	if (v->__len__ == v->__max_len__) __vec_resize__(v);\
	v->__v__[v->__len__] = e;\
	v->__len__++	// since v1.0
#define __vec_resize__(v) _Generic((v), \
	vector_t: __vec_res__,\
	int_vector_t: __int_vec_res__,\
	uint_vector_t: __uint_vec_res__,\
	byte_vector_t: __byte_vec_res__,\
	float_vector_t: __float_vec_res__,\
	double_vector_t: __double_vec_res__,\
	boolean_vector_t: __bool_vec_res__,\
	string_vector_t: __str_vec_res__\
	/*ustring_vector_t: __ustr_vec_res__*/\
) (v)	// since v1.0
void __vec_res__(vector_t);	// since v1.0
void __int_vec_res__(int_vector_t);	// since v1.0
void __uint_vec_res__(uint_vector_t);	// since v1.0
void __byte_vec_res__(byte_vector_t);	// since v1.0
void __float_vec_res__(float_vector_t);	// since v1.0
void __double_vec_res__(double_vector_t);	// since v1.0
void __bool_vec_res__(boolean_vector_t);	// since v1.0
void __str_vec_res__(string_vector_t);	// since v1.0
// void __ustr_vec_res__(ustring_vector_t);	// since v1.2
void vec_append(vector_t, any_t);	// since v1.0
void int_vec_append(int_vector_t, int_t);	// since v1.0
void uint_vec_append(uint_vector_t, uint_t);	// since v1.0
void byte_vec_append(byte_vector_t, uint8_t);	// since v1.0
void float_vec_append(float_vector_t, float);	// since v1.0
void double_vec_append(double_vector_t, double);	// since v1.0
void bool_vec_append(boolean_vector_t, bool);	// since v1.0
void str_vec_append(string_vector_t, string_t);	// since v1.0
// void ustr_vec_append(ustring_vector_t, unique_string_t);	// since v1.2
#define __vec_get__(v, i) v->__v__[(size_t)i % v->__len__]	// since v1.0
#define __vec_set__(v, i, e) v->__v__[(size_t) i % v->__len__] = e	// since v1.0
any_t vec_get(vector_t, size_t);	// since v1.0
int_t int_vec_get(int_vector_t, size_t);	// since v1.0
uint_t uint_vec_get(uint_vector_t, size_t);	// since v1.0
uint8_t byte_vec_get(byte_vector_t, size_t);	// since v1.0
float float_vec_get(float_vector_t, size_t);	// since v1.0
double double_vec_get(double_vector_t, size_t);	// since v1.0
bool bool_vec_get(boolean_vector_t, size_t);	// since v1.0
string_t str_vec_get(string_vector_t, size_t);	// since v1.0
// unique_string_t ustr_vec_get(ustring_vector_t, size_t);	// since v1.2
void vec_set(vector_t, size_t, any_t);	// since v1.0
void int_vec_set(int_vector_t, size_t, int_t);	// since v1.0
void uint_vec_set(uint_vector_t, size_t, uint_t);	// since v1.0
void byte_vec_set(byte_vector_t, size_t, uint8_t);	// since v1.0
void float_vec_set(float_vector_t, size_t, float);	// since v1.0
void double_vec_set(double_vector_t, size_t, double);	// since v1.0
void bool_vec_set(boolean_vector_t, size_t, bool);	// since v1.0
void str_vec_set(string_vector_t, size_t, string_t);	// since v1.0
// void ustr_vec_set(ustring_vector_t, size_t, unique_string_t);	// since v1.2

void int_vec_sort(int_vector_t, bool);	// since v1.0
void uint_vec_sort(uint_vector_t, bool);	// since v1.0
void byte_vec_sort(byte_vector_t, bool);	// since v1.0
void float_vec_sort(float_vector_t, bool);	// since v1.0
void double_vec_sort(double_vector_t, bool);	// since v1.0
void bool_vec_sort(boolean_vector_t, bool);	// since v1.0

#define vec_swap(v, i1, i2)\
	v->__v__[(size_t) i1 % v->__len__] = (uint_t) v->__v__[(size_t) i1 % v->__len__] ^ (uint_t) v->__v__[(size_t) i2 % v->__len__];\
	v->__v__[(size_t) i2 % v->__len__] = (uint_t) v->__v__[(size_t) i1 % v->__len__] ^ (uint_t) v->__v__[(size_t) i2 % v->__len__];\
	v->__v__[(size_t) i1 % v->__len__] = (uint_t) v->__v__[(size_t) i1 % v->__len__] ^ (uint_t) v->__v__[(size_t) i2 % v->__len__]	// since v1.0
// TODO: vector functions
#define vec_reverse(v)\
	for (size_t i = 0; i < v->__len__ / 2; i++)\
	{\
		vec_swap(v, i, v->__len__ - 1 - i);\
	} // since v1.0

#endif
