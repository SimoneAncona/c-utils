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

#define if_null_to_string(x) if (x == NULL) return str_new_string("null")

string_t __str_pool_ref__(char_ptr_t);	// since v1.0
// string_t str_new_string(char_ptr_t);	// since v1.0
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

__str_ref_info_t__ *__str_pool__ = NULL;
size_t __str_pool_size__ = __INITAL_STR_POOL_SIZE___;

#define __str_pool_check_for_init__() if (__str_pool__ == NULL) { __str_pool_alloc__(); }
#define __str_pool_alloc__() __str_pool__ = (__str_ref_info_t__*) malloc(sizeof(__str_ref_info_t__) * __INITAL_STR_POOL_SIZE___); for(size_t i = 0; i < __INITAL_STR_POOL_SIZE___; i++) {__str_pool__[i].str = NULL; __str_pool__[i].refs = 0;} __str_pool__[__NULL_STRING_POOL_INDEX__].str = __str_null_string__()
#define __str_pool_extend__() __str_pool__ = (__str_ref_info_t__*) realloc(__str_pool__, sizeof(__str_ref_info_t__) * (__str_pool_size__ + __STR_POOL_BLOCK_SIZE___)); __str_pool_size__ += __STR_POOL_BLOCK_SIZE___

string_t __str_pool_ref__(char_ptr_t s)
{
	for (size_t i = 0; i < __str_pool_size__; i++)
	{
		if ((__str_pool__[i].str != NULL) && (str_cmp(s, __str_pool__[i].str) == EQUAL))
		{
			free((void*) s);
			__str_pool__[i].refs++;
			return __str_pool__[i].str;
		}
	}

	__str_pool_append__(s);
	return s;
}

string_t __str_null_string__()
{
	char_ptr_t null_str = (char_ptr_t) malloc(sizeof(char_t));
	null_str[0] = __ENDING_CODE__;
	return (string_t) null_str;
}

string_t str_null_string()
{
	__str_pool_check_for_init__();
	return __str_pool__[__NULL_STRING_POOL_INDEX__].str;
}

string_t str_new_string(char_ptr_t s)
{
	__str_pool_check_for_init__();
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * (str_len(s) + 1));
	__str_copy__(str, s);
	return __str_pool_ref__(str);
}

string_t str_lower_case(string_t s)
{
	__str_pool_check_for_init__();
	size_t s_len = str_len(s) + 1;		// + 1, the terminator char
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * s_len);
	for (size_t i = 0; i < s_len; i++)
		str[i] = chr_to_lower(s[i]);
	return __str_pool_ref__(str);
}

string_t str_upper_case(string_t s)
{
	__str_pool_check_for_init__();
	size_t s_len = str_len(s) + 1;		// + 1, the terminator char
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * s_len);
	for (size_t i = 0; i < s_len; i++)
		str[i] = chr_to_upper(s[i]);
	return __str_pool_ref__(str);
}

string_t str_substr(string_t s, size_t start, size_t end)
{
	size_t s_len = str_len(s);
	if (end <= start || end > s_len || start > s_len) return str_null_string();
	__str_pool_check_for_init__();
	size_t st_len = end - start;
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * (st_len + 1));
	for (size_t i = 0; i < st_len; i++)
		str[i] = s[i + start];
	str[st_len] = __ENDING_CODE__;
	return __str_pool_ref__(str);
}

string_t str_replace(string_t s, string_t old_s, string_t new_s)
{
	size_t index = str_index_of(s, old_s);
	if (index == NOT_FOUND) return s;

	__str_pool_check_for_init__();
	size_t new_s_len = str_len(new_s);
	size_t old_s_len = str_len(old_s);
	size_t new_size = str_len(s) - old_s_len + new_s_len + 1;
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * new_size);
	for (size_t i = 0; i < index; i++)
	{
		str[i] = s[i];
	}

	for (size_t i = index; i < index + new_s_len; i++)
	{
		str[i] = new_s[i - index];
	}

	for (size_t i = new_s_len + index; i < new_size; i++)
	{
		str[i] = s[i - (new_s_len - old_s_len)];
	}

	return __str_pool_ref__(str);
}

string_t str_concat(string_t s1, string_t s2)
{
	__str_pool_check_for_init__();
	size_t s1_len = str_len(s1);
	size_t s2_len = str_len(s2);
	size_t new_size = s1_len + s2_len + 1;
	char_ptr_t str = (char_ptr_t) malloc(sizeof(char_t) * new_size);
	
	for (size_t i = 0; i < s1_len; i++)
	{
		str[i] = s1[i];
	}

	for (size_t i = s1_len; i < new_size; i++)
	{
		str[i] = s2[i - s1_len];
	}

	return __str_pool_ref__(str);
}

string_t str_from_char(char_t c)
{
	__str_pool_check_for_init__();
	char_ptr_t s = (char_ptr_t) malloc(sizeof(char_t) * 2);
	s[0] = c; s[1] = __ENDING_CODE__;
	return __str_pool_ref__(s);
}

string_t str_from_int(int_t n)
{
	__str_pool_check_for_init__();
	if (n == 0) return str_new_string("0");
	string_t str = str_null_string();
	string_t nstr = str_null_string();
	int8_t d;
	string_t c;
	int_t nn = n;

	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
	{
		d = nn % 10;
		d = d < 0 ? -d : d;
		if (d < 10)
			c = str_from_char('0' + d);
		else
			c = str_from_char('a' + d - 10);
		nstr = str_concat(c, str);
		str_destroy(c);
		str_destroy(str);
		str = nstr;

		nn = nn / 10;
	}

	if (n < 0)
	{
		nstr = str_concat("-", str);
		str_destroy(str);
	}
 
	return nstr;
}

string_t str_from_int_base(int_t n, uint8_t base)
{
	__str_pool_check_for_init__();
	if (n == 0) return str_new_string("0");
	if (base > 32) return str_null_string();
	string_t str = str_null_string();
	string_t nstr = str_null_string();
	int8_t d;
	string_t c;
	int_t nn = n;

	while ((n > 0 && nn > 0) || (n < 0 && nn < 0))
	{
		d = nn % base;
		d = d < 0 ? -d : d;
		if (d < 10)
			c = str_from_char('0' + d);
		else
			c = str_from_char('a' + d - 10);
		nstr = str_concat(c, str);
		str_destroy(c);
		str_destroy(str);
		str = nstr;

		nn = nn / base;
	}

	if (n < 0)
	{
		nstr = str_concat("-", str);
		str_destroy(str);
	}
 
	return nstr;
}

string_t str_from_uint(uint_t n)
{
	__str_pool_check_for_init__();
	if (n == 0) return str_new_string("0");
	string_t str = str_null_string();
	string_t nstr = str_null_string();
	int8_t d;
	string_t c;

	while (n > 0)
	{
		d = n % 10;
		if (d < 10)
			c = str_from_char('0' + d);
		else
			c = str_from_char('a' + d - 10);
		nstr = str_concat(c, str);
		str_destroy(c);
		str_destroy(str);
		str = nstr;

		n = n / 10;
	}
 
	return nstr;
}

string_t str_from_uint_base(uint_t n, uint8_t base)
{
	__str_pool_check_for_init__();
	if (n == 0) return str_new_string("0");
	if (base > 32) return str_null_string();
	string_t str = str_null_string();
	string_t nstr = str_null_string();
	int8_t d;
	string_t c;

	while (n > 0)
	{
		d = n % base;
		if (d < 10)
			c = str_from_char('0' + d);
		else
			c = str_from_char('a' + d - 10);
		nstr = str_concat(c, str);
		str_destroy(c);
		str_destroy(str);
		str = nstr;

		n = n / base;
	}
 
	return nstr;
}

string_t str_from_float(float f)
{
	__str_pool_check_for_init__();
	bool is_neg = f < 0;

    float f1 = is_neg ? -f : f;
    char_ptr_t s = malloc(sizeof(char_t) * FLT_DIG + 2);
    size_t dp = 0;
    size_t i;
    
    while (f1 > 1)
    {
        dp++;
        f1 /= 10;    
    }
    
    for(i = 0; i < FLT_DIG + 1; i++)
    {
        if (i == dp)
        {
            s[i] = '.';
            continue;
        }
        f1 *= 10;
        s[i] = ((uint8_t) f1) + '0';
        f1 = f1 - (uint8_t) f1;
    }

    s[i] = 0;

	string_t st = __str_pool_ref__(s);
	string_t ns = s;
	string_t ch = str_from_char('-');
	if(is_neg)
	{
		ns = str_concat(ch, st);
		str_destroy(st);
	}
	str_destroy(ch);
	return ns;
}

string_t str_from_double(double d)
{
	__str_pool_check_for_init__();
	bool is_neg = d < 0;

    double d1 = is_neg ? -d: d;
    char_ptr_t s = malloc(sizeof(char_t) * DBL_DIG + 2);
    size_t dp = 0;
    size_t i;
    
    while (d1 > 1)
    {
        dp++;
        d1 /= 10;    
    }
    
    for(i = 0; i < DBL_DIG + 1; i++)
    {
        if (i == dp)
        {
            s[i] = '.';
            continue;
        }
        d1 *= 10;
        s[i] = ((uint8_t) d1) + '0';
        d1 = d1 - (uint8_t) d1;
    }

    s[i] = 0;

	string_t st = __str_pool_ref__(s);
	string_t ns = s;
	string_t ch = str_from_char('-');
	if(is_neg)
	{
		ns = str_concat(ch, st);
		str_destroy(st);
	}
	str_destroy(ch);
	return ns;
}

string_t str_from_boolean(bool b)
{
	if (b) return str_new_string("true");
	return str_new_string("false");
}

string_t __str_to_string__(string_t s)
{
	string_t p = str_from_char('"');
	string_t str = s;
	string_t ns;
	ns = str_concat(p, str);
	str = ns;
	ns = str_concat(str, p);
	str_destroy(str);
	str_destroy(p);
	return ns;
}

// string_t __ustr_to_string__(unique_string_t s)
// {
// 	return str_new_string(s);
// }

string_t vec_to_string(vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		ns = str_concat(s, any_to_string(__vec_get__(v, i)));
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	ns = str_concat(s, any_to_string(__vec_get__(v, i)));
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t int_vec_to_string(int_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t n;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		n = str_from_int(int_vec_get(v, i));
		ns = str_concat(s, n);
		str_destroy(n);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	n = str_from_int(__vec_get__(v, i));
	ns = str_concat(s, n);
	str_destroy(n);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t uint_vec_to_string(uint_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t n;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		n = str_from_uint(__vec_get__(v, i));
		ns = str_concat(s, n);
		str_destroy(n);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	n = str_from_uint(__vec_get__(v, i));
	ns = str_concat(s, n);
	str_destroy(n);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t byte_vec_to_string(byte_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t n;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		n = str_from_uint(__vec_get__(v, i));
		ns = str_concat(s, n);
		str_destroy(n);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	n = str_from_uint(__vec_get__(v, i));
	ns = str_concat(s, n);
	str_destroy(n);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t float_vec_to_string(float_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t n;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		n = str_from_float(__vec_get__(v, i));
		ns = str_concat(s, n);
		str_destroy(n);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	n = str_from_float(__vec_get__(v, i));
	ns = str_concat(s, n);
	str_destroy(n);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t double_vec_to_string(double_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t db;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		db = str_from_double(__vec_get__(v, i));
		ns = str_concat(s, db);
		str_destroy(db);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	db = str_from_double(__vec_get__(v, i));
	ns = str_concat(s, db);
	str_destroy(db);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t bool_vec_to_string(boolean_vector_t v)
{
	if_null_to_string(v);
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t trs = str_new_string("true");
	string_t fls = str_new_string("false");
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		if (__vec_get__(v, i))
			ns = str_concat(s, trs);
		else
			ns = str_concat(s, fls);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	if (__vec_get__(v, i))
		ns = str_concat(s, trs);
	else
		ns = str_concat(s, fls);
	str_destroy(trs);
	str_destroy(fls);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t str_vec_to_string(string_vector_t v)
{
	if_null_to_string(v);
	if (v == NULL) return str_new_string("null");
	if (vec_len(v) == 0) return str_new_string("[]");
	string_t s = str_new_string("[");
	string_t ns = s;
	string_t d = str_new_string(", ");
	string_t end = str_new_string("]");
	string_t str;
	size_t i;
	for (i = 0; i < vec_len(v) - 1; i++)
	{
		str = __str_to_string__(__vec_get__(v, i));
		ns = str_concat(s, str);
		str_destroy(str);
		str_destroy(s);
		s = ns;
		ns = str_concat(s, d);
		str_destroy(s);
		s = ns;
	}
	str = __str_to_string__(__vec_get__(v, i));
	ns = str_concat(s, str);
	str_destroy(str);
	str_destroy(s);
	s = ns;
	ns = str_concat(s, end);
	str_destroy(s);
	str_destroy(d);
	str_destroy(end);
	return ns;
}

string_t map_to_string(map_t m)
{
	if_null_to_string(m);
	if (m->__k__ == NULL) return str_new_string("{}");
	string_t s = str_new_string("{");
	if (m->__next__ == NULL) {
		s = str_concat(s, any_to_string(m->__k__));
		s = str_concat(s, ": ");
		s = str_concat(s, any_to_string(m->__v__));
		s = str_concat(s, "}");
		return s;
	}
	if (((map_t)m->__next__)->__next__ == NULL)
	{
		s = str_concat(s, any_to_string(m->__k__));
		s = str_concat(s, ": ");
		s = str_concat(s, any_to_string(m->__v__));
		s = str_concat(s, ", ");
		s = str_concat(s, any_to_string(((map_t)m->__next__)->__k__));
		s = str_concat(s, ": ");
		s = str_concat(s, any_to_string(((map_t)m->__next__)->__v__));
		s = str_concat(s, "}");
		return s;
	}
	for (; m->__next__ != NULL && ((map_t)m->__next__)->__next__ != NULL; m = m->__next__) 
	{
		s = str_concat(s, any_to_string(m->__k__));
		s = str_concat(s, ": ");
		s = str_concat(s, any_to_string(m->__v__));
		s = str_concat(s, ",");
	}
	m = m->__next__;
	if (m != NULL)
	{
		s = str_concat(s, any_to_string(m->__k__));
		s = str_concat(s, ": ");
		s = str_concat(s, any_to_string(m->__v__));
	}
	s = str_concat(s, "}");
	return s;
}

// string_t ustr_vec_to_string(ustring_vector_t v)
// {
// 	string_t s = str_new_string("[");
// 	string_t ns = s;
// 	string_t d = str_new_string(", ");
// 	string_t end = str_new_string("]");
// 	string_t str;
// 	size_t i;
// 	for (i = 0; i < vec_len(v) - 1; i++)
// 	{
// 		str = __ustr_to_string__(__vec_get__(v, i));
// 		ns = str_concat(s, str);
// 		str_destroy(str);
// 		str_destroy(s);
// 		s = ns;
// 		ns = str_concat(s, d);
// 		str_destroy(s);
// 		s = ns;
// 	}
// 	str = __str_to_string__(__vec_get__(v, i));
// 	ns = str_concat(s, str);
// 	str_destroy(str);
// 	str_destroy(s);
// 	s = ns;
// 	ns = str_concat(s, end);
// 	str_destroy(s);
// 	str_destroy(d);
// 	str_destroy(end);
// 	return ns;
// }

string_t any_to_string(any_t a)
{
	if_null_to_string(a);
	switch (any_typeof(a))
	{
	case INTEGER:
		return str_from_int(any_get_int(a));
	case UNSIGNED_INTEGER:
		return str_from_uint(any_get_uint(a));
	case FLOAT:
		return str_from_float(any_get_float(a));
	case DOUBLE:
		return str_from_int(any_get_int(a));
	case BOOLEAN:
		return str_from_boolean(any_get_boolean(a));
	case NUMBER:
		break;
	case STRING:
		return __str_to_string__(any_get_string(a));
	case VECTOR:
		return vec_to_string(any_get_vector(a));
	case LIST:
		break;
	case INTEGER_VECTOR:
		return int_vec_to_string(any_get_int_vector(a));
	case UNSIGNED_INTEGER_VECTOR:
		return uint_vec_to_string(any_get_uint_vector(a));
	case FLOAT_VECTOR:
		return float_vec_to_string(any_get_float_vector(a));
	case DOUBLE_VECTOR:
		return double_vec_to_string(any_get_double_vector(a));
	case BOOLEAN_VECTOR:
		return bool_vec_to_string(any_get_boolean_vector(a));
	case NUMBER_VECTOR:
		break;
	case BYTE:
		return str_from_int(any_get_byte(a));
	case BYTE_VECTOR:
		return byte_vec_to_string(any_get_byte_vector(a));
	case CHAR:
		return str_from_char(any_get_char(a));
	case STRING_VECTOR:
		return str_vec_to_string(any_get_string_vector(a));
	case INTEGER_PTR:
		return str_from_uint((uint_t) any_get_int_ptr(a));
	case UNSIGNED_INTEGER_PTR:
		return str_from_uint((uint_t) any_get_uint_ptr(a));
	case FLOAT_PTR:
		return str_from_uint((uint_t) any_get_float_ptr(a));
	case DOUBLE_PTR:
		return str_from_uint((uint_t) any_get_double_ptr(a));
	case BOOLEAN_PTR:
		return str_from_uint((uint_t) any_get_boolean_ptr(a));
	case MAP:
		return map_to_string(any_get_map(a));
	case NUMBER_PTR:
		break;
	case STRING_PTR:
		break;
	case VECTOR_PTR:
		break;
	case LIST_PTR:
		break;
	case INTEGER_VECTOR_PTR:
		break;
	case UNSIGNED_INTEGER_VECTOR_PTR:
		break;
	case FLOAT_VECTOR_PTR:
		break;
	case DOUBLE_VECTOR_PTR:
		break;
	case BOOLEAN_VECTOR_PTR:
		break;
	case NUMBER_VECTOR_PTR:
		break;
	case BYTE_PTR:
		return str_from_uint((uint_t) any_get_byte_ptr(a));
	case BYTE_VECTOR_PTR:
	case STRING_VECTOR_PTR:
	case NONE_TYPE:
		return str_new_string("null");
	default:
		break;
	}

	return str_null_string();
}

uint8_t str_cmp(string_t s1, string_t s2)
{
	size_t s1_len = str_len(s1);
	size_t s2_len = str_len(s2);
	if (s1_len > s2_len) return GRATER;
	if (s1_len < s2_len) return LESS;
	for (size_t i = 0; i < s1_len; i++)
	{
		if (s1[i] != s2[i]) return NOT_EQUAL;
	}
	return EQUAL;
}

char_t str_char_at(string_t s, size_t i)
{
	if (i >= str_len(s)) return __ENDING_CODE__;
	return s[i];
}

bool str_starts_with(string_t main_str, string_t sub_str)
{
	size_t s2_len = str_len(sub_str);
	if (s2_len > str_len(main_str)) return false;
	for (size_t i = 0; i < s2_len; i++)
	{
		if (main_str[i] != sub_str[i]) return false;
	}

	return true;
}

bool str_ends_with(string_t main_str, string_t sub_str)
{
	size_t s2_len = str_len(sub_str);
	size_t s1_len = str_len(main_str);
	if (s2_len > s1_len) return false;
	for (size_t i = s1_len - 1; i > s1_len - s2_len - 1; i--)
	{
		if (main_str[i] != sub_str[i - s1_len + s2_len]) return false;
	}

	return true;
}

bool str_includes(string_t main_str, string_t sub_str)
{
	size_t s1_len = str_len(main_str);
	size_t s2_len = str_len(sub_str);
	bool next;

	if (s2_len > s1_len) return false;

	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
	{
		next = false;
		for (size_t j = i; j < s2_len + i && !next; j++)
		{
			if (main_str[j] != sub_str[j - i]) next = true;
		}
		if (!next)
			return true;
	}

	return false;
}

bool str_destroy(string_t s)
{
	for (size_t i = 0; i < __str_pool_size__; i++)
	{
		if (i != __NULL_STRING_POOL_INDEX__ && __str_pool__[i].str == s)
		{
			__str_pool__[i].refs--;
			if (__str_pool__[i].refs == 0)
			{
				free((void*) s);
				__str_pool__[i].str = NULL;
			}
			return true;
		}
	}
	return false;
}

bool str_is_int(string_t s)
{
	if (!(chr_is_digit(s[0]) || s[0] == '-')) return false;

	size_t l = str_len(s);
	for (size_t i = 1; i < l; i++)
	{
		if(!chr_is_digit(s[i])) return false;
	}

	return true;
}

bool str_is_number(string_t s)
{
	bool dp = false;
	if (!(chr_is_digit(s[0]) || s[0] == '-'))
	{
		if (s[0] == '.') dp = true;
		else
			return false;
	}

	size_t l = str_len(s);
	for (size_t i = 1; i < l; i++)
	{
		if(!chr_is_digit(s[i])) {
			if(s[i] == '.' && !dp) dp = true;
			else
				return false;
		}
	}

	return true;
}

bool str_is_alpha(string_t s)
{
	size_t l = str_len(s);
	for (size_t i = 0; i < l; i++)
	{
		if (!chr_is_alpha(s[i])) return false;
	}
	return true;
}

bool str_is_alnum(string_t s)
{
	size_t l = str_len(s);
	for (size_t i = 0; i < l; i++)
	{
		if (!chr_is_alnum(s[i])) return false;
	}
	return true;
}

bool str_is_identifier(string_t s)
{
	if (!chr_is_alpha(s[0])) return false;

	size_t l = str_len(s);
	for (size_t i = 1; i < l; i++)
	{
		if(!(chr_is_alnum(s[i]) || s[i] == '_')) return false;
	}

	return true;
}

bool str_is_lower(string_t s)
{
	size_t l = str_len(s);
	for (size_t i = 0; i < l; i++)
	{
		if (!chr_is_lower(s[i])) return false;
	}
	return true;
}

bool str_is_upper(string_t s)
{
	size_t l = str_len(s);
	for (size_t i = 0; i < l; i++)
	{
		if (!chr_is_upper(s[i])) return false;
	}
	return true;
}

bool __str_is_null__(string_t s)
{
	__str_pool_check_for_init__();
	return __str_pool__[__NULL_STRING_POOL_INDEX__].str == s;
}


size_t str_index_of(string_t main_str, string_t sub_str)
{
	size_t s1_len = str_len(main_str);
	size_t s2_len = str_len(sub_str);
	bool next;

	if (s2_len > s1_len) return NOT_FOUND;

	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
	{
		next = false;
		for (size_t j = i; j < s2_len + i && !next; j++)
		{
			if (main_str[j] != sub_str[j - i]) next = true;
		}
		if (!next)
			return i;
	}

	return NOT_FOUND;
}

size_t str_last_index_of(string_t main_str, string_t sub_str)
{
	size_t s1_len = str_len(main_str);
	size_t s2_len = str_len(sub_str);
	bool next;

	if (s2_len > s1_len) return NOT_FOUND;

	for (size_t i = 0; i < s1_len - s2_len + 1; i++)
	{
		next = false;
		for (size_t j = i; j < s2_len + i && !next; j++)
		{
			if (main_str[j] != sub_str[j - i]) next = true;
		}
		if (!next)
			return i;
	}

	return NOT_FOUND;
}

size_t str_len(string_t s)
{
	size_t i = 0;
	for (; s[i] != __ENDING_CODE__; i++);
	return i;
}

void __str_pool_append__(string_t s)
{
	size_t i = 0;
	for (; i < __str_pool_size__; i++)
	{
		if (__str_pool__[i].str == NULL)
		{
			__str_pool__[i].str = s;
			__str_pool__[i].refs = 1;
			return;
		}
	}

	__str_pool_extend__();
	__str_pool_append__(s);
}

void __str_copy__(char_ptr_t destination, char_ptr_t source)
{
	size_t l = str_len(source);
	for (size_t i = 0; i < l + 1; i++)
		destination[i] = source[i];
}

#endif