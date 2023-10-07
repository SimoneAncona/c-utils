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

// unique_string_t ustr_null_string()
// {
// 	unique_string_t s = (unique_string_t) malloc(sizeof(char_t));
// 	s[0] = __ENDING_CODE__;
// 	return s;
// }

// unique_string_t ustr_new_string(char_ptr_t s)
// {
// 	unique_string_t str = (unique_string_t) malloc(sizeof(char_t) * (ustr_len(s) + 1));
// 	__ustr_copy__(str, s);
// 	return str;
// }

// unique_string_t ustr_substr(unique_string_t s, size_t start, size_t end)
// {
// 	size_t s_len = ustr_len(s);
// 	if (end <= start || end > s_len || start > s_len) return ustr_null_string();
// 	size_t st_len = end - start;
// 	unique_string_t str = (unique_string_t) malloc(sizeof(char_t) * (st_len + 1));
// 	for (size_t i = 0; i < st_len; i++)
// 		str[i] = s[i + start];
// 	str[st_len] = __ENDING_CODE__;
// 	return str;
// }

// unique_string_t ustr_from_char(char_t c)
// {
// 	unique_string_t s = (unique_string_t) malloc(sizeof(char_t) * 2);
// 	s[0] = c; s[1] = __ENDING_CODE__;
// 	return s;
// }

// unique_string_t ustr_from_int(int_t n)
// {
// 	if (n == 0) return ustr_new_string("0");
// 	unique_string_t nstr = ustr_new_string("");
// 	int8_t d;
// 	string_t c;
// 	int_t nn = n;

// 	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
// 	{
// 		d = nn % 10;
// 		d = d < 0 ? -d : d;
// 		if (d < 10)
// 			ustr_insert(nstr, '0' + d, 0);
// 		else
// 			ustr_insert(nstr, 'a' + d - 10, 0);
// 		nn = nn / 10;
// 	}

// 	if (n < 0)
// 	{
// 		ustr_insert(nstr, '-', 0);
// 	}
 
// 	return nstr;
// }

// unique_string_t ustr_from_int_base(int_t n, uint8_t base)
// {
// 	if (n == 0) return ustr_new_string("0");
// 	if (base > 32) return ustr_null_string();
// 	unique_string_t nstr = ustr_new_string("");
// 	int8_t d;
// 	string_t c;
// 	int_t nn = n;

// 	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
// 	{
// 		d = nn % base;
// 		d = d < 0 ? -d : d;
// 		if (d < 10)
// 			ustr_insert(nstr, '0' + d, 0);
// 		else
// 			ustr_insert(nstr, 'a' + d - 10, 0);
// 		nn = nn / base;
// 	}

// 	if (n < 0)
// 	{
// 		ustr_insert(nstr, '-', 0);
// 	}
 
// 	return nstr;
// }

// unique_string_t ustr_from_uint(uint_t n)
// {
// 	if (n == 0) return ustr_new_string("0");
// 	unique_string_t nstr = ustr_new_string("");
// 	int8_t d;
// 	string_t c;
// 	int_t nn = n;

// 	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
// 	{
// 		d = nn % 10;
// 		d = d < 0 ? -d : d;
// 		if (d < 10)
// 			ustr_insert(nstr, '0' + d, 0);
// 		else
// 			ustr_insert(nstr, 'a' + d - 10, 0);
// 		nn = nn / 10;
// 	}
 
// 	return nstr;
// }

// unique_string_t ustr_from_uint_base(uint_t n, uint8_t base)
// {
// 	if (n == 0) return ustr_new_string("0");
// 	if (base > 32) return ustr_null_string();
// 	unique_string_t nstr = ustr_new_string("");
// 	int8_t d;
// 	string_t c;
// 	int_t nn = n;

// 	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
// 	{
// 		d = nn % base;
// 		d = d < 0 ? -d : d;
// 		if (d < 10)
// 			ustr_insert(nstr, '0' + d, 0);
// 		else
// 			ustr_insert(nstr, 'a' + d - 10, 0);
// 		nn = nn / base;
// 	}

// 	if (n < 0)
// 	{
// 		ustr_insert(nstr, '-', 0);
// 	}
 
// 	return nstr;
// }

// unique_string_t ustr_from_float(float f)
// {
// 	bool is_neg = f < 0;

//     float f1 = f;
//     unique_string_t s = malloc(sizeof(char_t) * FLT_DIG + 2);
//     size_t dp = 0;
//     size_t i;
    
//     while (f1 > 1)
//     {
//         dp++;
//         f1 /= 10;    
//     }
    
//     for(i = 0; i < FLT_DIG + 1; i++)
//     {
//         if (i == dp)
//         {
//             s[i] = '.';
//             continue;
//         }
//         f1 *= 10;
//         s[i] = ((uint8_t) f1) + '0';
//         f1 = f1 - (uint8_t) f1;
//     }

//     s[i] = 0;

// 	if(is_neg)
// 	{
// 		ustr_insert(s, '-', 0);
// 	}
// 	return s;
// }

// unique_string_t ustr_from_double(double d)
// {
// 	bool is_neg = d < 0;

//     double d1 = d;
//     unique_string_t s = malloc(sizeof(char_t) * DBL_DIG + 2);
//     size_t dp = 0;
//     size_t i;
    
//     while (d1 > 1)
//     {
//         dp++;
//         d1 /= 10;    
//     }
    
//     for(i = 0; i < DBL_DIG + 1; i++)
//     {
//         if (i == dp)
//         {
//             s[i] = '.';
//             continue;
//         }
//         d1 *= 10;
//         s[i] = ((uint8_t) d1) + '0';
//         d1 = d1 - (uint8_t) d1;
//     }

//     s[i] = 0;

// 	if(is_neg)
// 	{
// 		ustr_insert(s, '-', 0);
// 	}
// 	return s;
// }

// unique_string_t ustr_from_boolean(bool b)
// {
// 	if (b) return ustr_new_string("true");
// 	return ustr_new_string("false");
// }

// unique_string_t __str_to_ustring__(string_t s)
// {
// 	unique_string_t ns = ustr_null_string();
// 	size_t l = str_len(s);
// 	for (size_t i = 0; i < l + 1; i++)
// 		ustr_append(ns, s[i]);

// 	return ns;
// }

// unique_string_t vec_to_ustring(vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, any_to_ustring(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, any_to_ustring(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t int_vec_to_ustring(int_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_int(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_int(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t uint_vec_to_ustring(uint_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_uint(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_uint(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t byte_vec_to_ustring(byte_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_uint(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_uint(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t float_vec_to_ustring(float_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_float(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_float(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t double_vec_to_ustring(double_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_double(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_double(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t bool_vec_to_ustring(boolean_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, ustr_from_boolean(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, ustr_from_boolean(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t str_vec_to_ustring(string_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, __str_to_ustring__(__vec_get__(v, i)));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, __str_to_ustring__(__vec_get__(v, i)));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t ustr_vec_to_ustring(ustring_vector_t v)
// {
// 	unique_string_t s = ustr_new_string("[");
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		ustr_concat(s, __vec_get__(v, i));
// 		ustr_concat(s, ", ");
// 	}
// 	ustr_concat(s, __vec_get__(v, i));
// 	ustr_concat(s, "]");
// 	return s;
// }

// unique_string_t any_to_ustring(any_t a)
// {
// 	switch (any_typeof(a))
// 	{
// 	case INTEGER:
// 		return ustr_from_int(any_get_int(a));
// 	case UNSIGNED_INTEGER:
// 		return ustr_from_uint(any_get_uint(a));
// 	case FLOAT:
// 		return ustr_from_float(any_get_float(a));
// 	case DOUBLE:
// 		return ustr_from_int(any_get_int(a));
// 	case BOOLEAN:
// 		return ustr_from_boolean(any_get_boolean(a));
// 	case NUMBER:
// 		break;
// 	case STRING:
// 		return __str_to_ustring__(any_get_string(a));
// 	case VECTOR:
// 		return vec_to_ustring(any_get_vector(a));
// 	case LIST:
// 		break;
// 	case INTEGER_VECTOR:
// 		return int_vec_to_ustring(any_get_int_vector(a));
// 	case UNSIGNED_INTEGER_VECTOR:
// 		return uint_vec_to_ustring(any_get_uint_vector(a));
// 	case FLOAT_VECTOR:
// 		return float_vec_to_ustring(any_get_float_vector(a));
// 	case DOUBLE_VECTOR:
// 		return double_vec_to_ustring(any_get_double_vector(a));
// 	case BOOLEAN_VECTOR:
// 		return bool_vec_to_ustring(any_get_boolean_vector(a));
// 	case NUMBER_VECTOR:
// 		break;
// 	case BYTE:
// 		return ustr_from_int(any_get_byte(a));
// 	case BYTE_VECTOR:
// 		return byte_vec_to_ustring(any_get_byte_vector(a));
// 	case CHAR:
// 		return ustr_from_char(any_get_char(a));
// 	case STRING_VECTOR:
// 		return str_vec_to_ustring(any_get_string_vector(a));
// 	case INTEGER_PTR:
// 		return ustr_from_uint((uint_t) any_get_int_ptr(a));
// 	case UNSIGNED_INTEGER_PTR:
// 		return ustr_from_uint((uint_t) any_get_uint_ptr(a));
// 	case FLOAT_PTR:
// 		return ustr_from_uint((uint_t) any_get_float_ptr(a));
// 	case DOUBLE_PTR:
// 		return ustr_from_uint((uint_t) any_get_double_ptr(a));
// 	case BOOLEAN_PTR:
// 		return ustr_from_uint((uint_t) any_get_boolean_ptr(a));
// 	case NUMBER_PTR:
// 		break;
// 	case STRING_PTR:
// 		break;
// 	case VECTOR_PTR:
// 		break;
// 	case LIST_PTR:
// 		break;
// 	case INTEGER_VECTOR_PTR:
// 		break;
// 	case UNSIGNED_INTEGER_VECTOR_PTR:
// 		break;
// 	case FLOAT_VECTOR_PTR:
// 		break;
// 	case DOUBLE_VECTOR_PTR:
// 		break;
// 	case BOOLEAN_VECTOR_PTR:
// 		break;
// 	case NUMBER_VECTOR_PTR:
// 		break;
// 	case BYTE_PTR:
// 		return ustr_from_uint((uint_t) any_get_byte_ptr(a));
// 	case BYTE_VECTOR_PTR:
// 	case STRING_VECTOR_PTR:
// 	case NONE_TYPE:
// 		return ustr_new_string("null");
// 	default:
// 		break;
// 	}

// 	return ustr_null_string();
// }

// void ustr_lower_case(unique_string_t s)
// {
// 	size_t s_len = ustr_len(s) + 1;
// 	for (size_t i = 0; i < s_len; i++)
// 		s[i] = chr_to_lower(s[i]);
// }

// void ustr_upper_case(unique_string_t s)
// {
// 	size_t s_len = ustr_len(s) + 1;
// 	for (size_t i = 0; i < s_len; i++)
// 		s[i] = chr_to_upper(s[i]);
// }

// void ustr_concat(unique_string_t s1, unique_string_t s2)
// {
// 	size_t s1_len = ustr_len(s1);
// 	size_t s2_len = ustr_len(s2);
// 	size_t new_size = s1_len + s2_len + 1;
// 	s1 = (unique_string_t) realloc(s1, sizeof(char_t) * new_size);

// 	for (size_t i = s1_len; i < new_size; i++)
// 	{
// 		s1[i] = s2[i - s1_len];
// 	}
// }

// void ustr_replace(unique_string_t s, unique_string_t old_s, unique_string_t new_s)
// {
// 	size_t index = ustr_index_of(s, old_s);
// 	if (index == NOT_FOUND) return;

// 	size_t new_s_len = ustr_len(new_s);
// 	size_t old_s_len = ustr_len(old_s);
// 	size_t new_size = ustr_len(s) - old_s_len + new_s_len + 1;
// 	s = realloc(s, new_size * sizeof(char_t));

// 	for (size_t i = index; i < index + new_s_len; i++)
// 	{
// 		s[i] = new_s[i - index];
// 	}

// 	for (size_t i = new_s_len + index; i < new_size; i++)
// 	{
// 		s[i] = s[i - (new_s_len - old_s_len)];
// 	}
// }

// void ustr_append(unique_string_t s, char_t c)
// {
// 	__ustr_extend__(s, 1);
// 	s[ustr_len(s) - 1] = c;
// }

// void ustr_insert(unique_string_t s, char_t c, size_t i)
// {
// 	__ustr_extend__(s, 1);
// 	__ustr_shift_right__(s, i);
// 	s[i] = c;
// }

// uint8_t ustr_cmp(unique_string_t s1, unique_string_t s2)
// {
// 	size_t s1_len = ustr_len(s1);
// 	size_t s2_len = ustr_len(s2);
// 	if (s1_len > s2_len) return GRATER;
// 	if (s1_len < s2_len) return LESS;
// 	for (size_t i = 0; i < s1_len; i++)
// 	{
// 		if (s1[i] != s2[i]) return NOT_EQUAL;
// 	}
// 	return EQUAL;
// }

// char_t ustr_char_at(unique_string_t s, size_t i)
// {
// 	if (i >= ustr_len(s)) return __ENDING_CODE__;
// 	return s[i];
// }

// bool ustr_starts_with(unique_string_t main_str, unique_string_t sub_str)
// {
// 	size_t s2_len = ustr_len(sub_str);
// 	if (s2_len > ustr_len(main_str)) return false;
// 	for (size_t i = 0; i < s2_len; i++)
// 	{
// 		if (main_str[i] != sub_str[i]) return false;
// 	}

// 	return true;
// }

// bool ustr_ends_with(unique_string_t main_str, unique_string_t sub_str)
// {
// 	size_t s2_len = ustr_len(sub_str);
// 	size_t s1_len = ustr_len(main_str);
// 	if (s2_len > s1_len) return false;
// 	for (size_t i = s1_len - 1; i > s1_len - s2_len - 1; i--)
// 	{
// 		if (main_str[i] != sub_str[i - s1_len + s2_len]) return false;
// 	}

// 	return true;
// }

// bool ustr_includes(unique_string_t main_str, unique_string_t sub_str)
// {
// 	size_t s1_len = ustr_len(main_str);
// 	size_t s2_len = ustr_len(sub_str);
// 	bool next;

// 	if (s2_len > s1_len) return false;

// 	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
// 	{
// 		next = false;
// 		for (size_t j = i; j < s2_len + i && !next; j++)
// 		{
// 			if (main_str[j] != sub_str[j - i]) next = true;
// 		}
// 		if (!next)
// 			return true;
// 	}

// 	return false;
// }

// bool ustr_is_int(unique_string_t s)
// {
// 	if (!(chr_is_digit(s[0]) || s[0] == '-')) return false;

// 	size_t l = ustr_len(s);
// 	for (size_t i = 1; i < l; i++)
// 	{
// 		if(!chr_is_digit(s[i])) return false;
// 	}

// 	return true;
// }

// bool ustr_is_number(unique_string_t s)
// {
// 	bool dp = false;
// 	if (!(chr_is_digit(s[0]) || s[0] == '-'))
// 	{
// 		if (s[0] == '.') dp = true;
// 		else
// 			return false;
// 	}

// 	size_t l = ustr_len(s);
// 	for (size_t i = 1; i < l; i++)
// 	{
// 		if(!chr_is_digit(s[i])) {
// 			if(s[i] == '.' && !dp) dp = true;
// 			else
// 				return false;
// 		}
// 	}

// 	return true;
// }

// bool ustr_is_alpha(unique_string_t s)
// {
// 	size_t l = ustr_len(s);
// 	for (size_t i = 0; i < l; i++)
// 	{
// 		if (!chr_is_alpha(s[i])) return false;
// 	}
// 	return true;
// }

// bool ustr_is_alnum(unique_string_t s)
// {
// 	size_t l = ustr_len(s);
// 	for (size_t i = 0; i < l; i++)
// 	{
// 		if (!chr_is_alnum(s[i])) return false;
// 	}
// 	return true;
// }

// bool ustr_is_identifier(unique_string_t s)
// {
// 	if (!chr_is_alpha(s[0])) return false;

// 	size_t l = ustr_len(s);
// 	for (size_t i = 1; i < l; i++)
// 	{
// 		if(!(chr_is_alnum(s[i]) || s[i] == '_')) return false;
// 	}

// 	return true;
// }

// bool ustr_is_lower(unique_string_t s)
// {
// 	size_t l = ustr_len(s);
// 	for (size_t i = 0; i < l; i++)
// 	{
// 		if (!chr_is_lower(s[i])) return false;
// 	}
// 	return true;
// }

// bool ustr_is_upper(unique_string_t s)
// {
// 	size_t l = ustr_len(s);
// 	for (size_t i = 0; i < l; i++)
// 	{
// 		if (!chr_is_upper(s[i])) return false;
// 	}
// 	return true;
// }

// bool ustr_equals(unique_string_t s1, unique_string_t s2)
// {
// 	return ustr_cmp(s1, s2) == EQUAL;
// }

// size_t ustr_index_of(unique_string_t main_str, unique_string_t sub_str)
// {
// 	size_t s1_len = ustr_len(main_str);
// 	size_t s2_len = ustr_len(sub_str);
// 	bool next;

// 	if (s2_len > s1_len) return NOT_FOUND;

// 	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
// 	{
// 		next = false;
// 		for (size_t j = i; j < s2_len + i && !next; j++)
// 		{
// 			if (main_str[j] != sub_str[j - i]) next = true;
// 		}
// 		if (!next)
// 			return i;
// 	}

// 	return NOT_FOUND;
// }

// size_t ustr_last_index_of(unique_string_t main_str, unique_string_t sub_str)
// {
// 	size_t s1_len = ustr_len(main_str);
// 	size_t s2_len = ustr_len(sub_str);
// 	bool next;

// 	if (s2_len > s1_len) return NOT_FOUND;

// 	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
// 	{
// 		next = false;
// 		for (size_t j = i; j < s2_len + i && !next; j++)
// 		{
// 			if (main_str[j] != sub_str[j - i]) next = true;
// 		}
// 		if (!next)
// 			return i;
// 	}

// 	return NOT_FOUND;
// }

// size_t ustr_len(unique_string_t s)
// {
// 	size_t i = 0;
// 	for (; s[i] != __ENDING_CODE__; i++);
// 	return i;
// }

// void __ustr_copy__(char_ptr_t destination, char_ptr_t source)
// {
// 	size_t l = ustr_len(source);
// 	for (size_t i = 0; i < l + 1; i++)
// 		destination[i] = source[i];
// }

// void __ustr_shift_right__(unique_string_t s, size_t i)
// {
// 	size_t l = ustr_len(s);
// 	for (; l > i; l--)
// 	{
// 		s[l] = s[l - 1];
// 	}
// }

#endif