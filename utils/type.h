#include <ctype.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>
#include <stdio.h>

#ifndef _TYPE_H_
#define _TYPE_H_

#if INTPTR_MAX == INT64_MAX
	#define __64ENV__
	typedef int64_t int_t;
	typedef uint64_t uint_t;
#elif INTPTR_MAX == INT32_MAX
	#define __32ENV__
	typedef int32_t int_t;
	typedef uint32_t uint_t;
#else
	#error Missing dependencies
#endif

typedef uint8_t type_t;

#define INTEGER 						(type_t) 0
#define UNSIGNED_INTEGER 				(type_t) 1
#define FLOAT 							(type_t) 2
#define DOUBLE 							(type_t) 3
#define BOOLEAN 						(type_t) 4
#define NUMBER /*variable precision*/	(type_t) 5	// available in utils 2.0
#define STRING 							(type_t) 6
#define VECTOR 							(type_t) 7
#define LIST 							(type_t) 8	// available in utils 1.1
#define INTEGER_VECTOR 					(type_t) 9
#define UNSIGNED_INTEGER_VECTOR 		(type_t) 10
#define FLOAT_VECTOR 					(type_t) 11
#define DOUBLE_VECTOR 					(type_t) 12
#define BOOLEAN_VECTOR 					(type_t) 13
#define NUMBER_VECTOR 					(type_t) 14
#define BYTE 							(type_t) 15
#define BYTE_VECTOR 					(type_t) 16
#define CHAR 							(type_t) 17
#define STRING_VECTOR					(type_t) 18
#define INTEGER_PTR						(type_t) 19
#define UNSIGNED_INTEGER_PTR			(type_t) 20
#define FLOAT_PTR						(type_t) 21
#define DOUBLE_PTR						(type_t) 22
#define BOOLEAN_PTR						(type_t) 23
#define NUMBER_PTR						(type_t) 24	// available in utils 2.0
#define STRING_PTR						(type_t) 25
#define VECTOR_PTR						(type_t) 26
#define LIST_PTR						(type_t) 27
#define INTEGER_VECTOR_PTR 				(type_t) 28	
#define UNSIGNED_INTEGER_VECTOR_PTR 	(type_t) 29
#define FLOAT_VECTOR_PTR 				(type_t) 30
#define DOUBLE_VECTOR_PTR				(type_t) 31
#define BOOLEAN_VECTOR_PTR 				(type_t) 32
#define NUMBER_VECTOR_PTR 				(type_t) 33	// available in utils 2.0
#define BYTE_PTR 						(type_t) 34
#define BYTE_VECTOR_PTR 				(type_t) 35	// available in utils 1.1
#define STRING_VECTOR_PTR				(type_t) 36	// available in utils 1.1
#define MAP								(type_t) 37	// available in utils 1.1
#define MAP_PTR							(type_t) 38	// available in utils x.x
#define MAP_VECTOR						(type_t) 39	// available in utils 1.1
#define MAP_VECTOR_PTR					(type_t) 40	// available in utils x.x
#define FUNCTION						(type_t) 41 // available in utils x.x
#define STREAM							(type_t) 42 // available in utils 1.1
#define STREAM_PTR						(type_t) 43 // available in utils 1.1
#define RANGE							(type_t) 44 // available in utils 1.1
#define RANGE_PTR						(type_t) 45 // available in utils 1.1
#define QUEUE							(type_t) 46 // available in utils 1.2
#define QUEUE_PTR						(type_t) 47 // available in utils 1.2
// #define THREAD							(type_t) 48 // available in utils 1.2
#define ANY								(type_t) -2
#define NONE_TYPE						(type_t) -1

// #ifndef WCHAR
typedef char char_t;	// since v1.0
typedef uint8_t byte_t;	// since v1.1
// #else
// 	typedef wchar_t char_t;
// #endif
typedef char_t *char_ptr_t;	// since v1.0

// STRING library
typedef const char_t *string_t;	// since v1.0
typedef string_t *string_ptr_t;	// since v1.0
typedef struct __sri__
{
	string_t str;		// string
	uint64_t refs;		// number of references
} __str_ref_info_t__;

// UNIQUE STRING library
typedef char_ptr_t unique_string_t;	// since v1.0
typedef unique_string_t *unique_string_ptr_t;	// since v1.0

// ANY library
typedef struct __any_struct__
{
	type_t __t__;
	uint64_t __value__;
} __any_struct_t__;
typedef __any_struct_t__ *any_t;	// since v1.0
typedef any_t *any_ptr_t;	// since v1.0

// VECTOR library
typedef struct __vector_struct__ { any_ptr_t __v__; size_t __len__; size_t __max_len__; } __vector_struct_t__;	// since v1.0
typedef struct __int_vector_struct__ { int_t *__v__; size_t __len__; size_t __max_len__;} __int_vector_struct_t__;	// since v1.0
typedef struct __uint_vecor_struct__ { uint_t *__v__; size_t __len__; size_t __max_len__;} __uint_vector_struct_t__;	// since v1.0
typedef struct __byte_vector_struct__ { byte_t *__v__; size_t __len__; size_t __max_len__;} __byte_vector_struct_t__;	// since v1.0
typedef struct __float_vector_struct__ { float *__v__; size_t __len__; size_t __max_len__;} __float_vector_struct_t__;	// since v1.0
typedef struct __double_vector_struct__ { double *__v__; size_t __len__; size_t __max_len__;} __double_vector_struct_t__;	// since v1.0
typedef struct __boolean_vector_struct__ { bool *__v__; size_t __len__; size_t __max_len__;} __boolean_vector_struct_t__;	// since v1.0
typedef struct __string_vector_struct__ { string_ptr_t __v__; size_t __len__; size_t __max_len__;} __string_vector_struct_t__;	// since v1.0
typedef struct __ustring_vector_struct__ { unique_string_ptr_t __v__; size_t __len__; size_t __max_len__;} __ustring_vector_struct_t__;	// since v1.0
typedef __vector_struct_t__ *vector_t;	// since v1.0
typedef __int_vector_struct_t__ *int_vector_t;	// since v1.0
typedef __uint_vector_struct_t__ *uint_vector_t;	// since v1.0
typedef __byte_vector_struct_t__ *byte_vector_t;	// since v1.0
typedef __float_vector_struct_t__ *float_vector_t;	// since v1.0
typedef __double_vector_struct_t__ *double_vector_t;	// since v1.0
typedef __boolean_vector_struct_t__ *boolean_vector_t;	// since v1.0
typedef __string_vector_struct_t__ *string_vector_t;	// since v1.0
typedef __ustring_vector_struct_t__ *ustring_vector_t;	// since v1.0
typedef vector_t *vector_ptr_t;	// since v1.0
typedef int_vector_t *int_vector_ptr_t;	// since v1.0
typedef uint_vector_t *uint_vector_ptr_t;	// since v1.0
typedef byte_vector_t *byte_vector_ptr_t;	// since v1.0
typedef float_vector_t *float_vector_ptr_t;	// since v1.0
typedef double_vector_t *double_vector_ptr_t;	// since v1.0
typedef boolean_vector_t *boolean_vector_ptr_t;	// since v1.0
typedef string_vector_t *string_vector_ptr_t;	// since v1.0
typedef ustring_vector_t *ustring_vector_ptr_t;	// since v1.0

typedef struct __map_struct__
{
	any_t __k__;
	any_t __v__;
	void *__next__;
} __map_struct_t__;

typedef __map_struct_t__ *map_t;
typedef map_t *map_ptr_t;

typedef struct __iterator_struct_t__
{
	size_t __size__;
	void *ptr;
	type_t __type__;
} iterator_t;

typedef iterator_t *iterator_ptr_t;

typedef byte_vector_t number_t;

#endif