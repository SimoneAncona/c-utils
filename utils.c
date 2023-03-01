#include "utils.h"
#include <stdio.h>

// STRING

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

// UNIQUE STRINGS

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

// VECTORS

vector_t vec_new_vector(size_t len)
{
	vector_t v = (vector_t) malloc(sizeof(__vector_struct_t__));
	v->__v__ = (any_ptr_t) malloc(sizeof(any_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = any_null();
	return v;
}

vector_t vec_null_vector()
{
	vector_t v = (vector_t) malloc(sizeof(__vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

int_vector_t int_vec_new_vector(size_t len)
{
	int_vector_t v = (int_vector_t) malloc(sizeof(__int_vector_struct_t__));
	v->__v__ = (int_t*) malloc(sizeof(int_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

int_vector_t int_vec_null_vector()
{
	int_vector_t v = (int_vector_t) malloc(sizeof(__int_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

uint_vector_t uint_vec_new_vector(size_t len)
{
	uint_vector_t v = (uint_vector_t) malloc(sizeof(__uint_vector_struct_t__));
	v->__v__ = (uint_t*) malloc(sizeof(uint_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

uint_vector_t uint_vec_null_vector()
{
	uint_vector_t v = (uint_vector_t) malloc(sizeof(__uint_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

byte_vector_t byte_vec_new_vector(size_t len)
{
	byte_vector_t v = (byte_vector_t) malloc(sizeof(__byte_vector_struct_t__));
	v->__v__ = (uint8_t*) malloc(sizeof(uint8_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

byte_vector_t byte_vec_null_vector()
{
	byte_vector_t v = (byte_vector_t) malloc(sizeof(__byte_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

float_vector_t float_vec_new_vector(size_t len)
{
	float_vector_t v = (float_vector_t) malloc(sizeof(__float_vector_struct_t__));
	v->__v__ = (float*) malloc(sizeof(float) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

float_vector_t float_vec_null_vector()
{
	float_vector_t v = (float_vector_t) malloc(sizeof(__float_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

double_vector_t double_vec_new_vector(size_t len)
{
	double_vector_t v = (double_vector_t) malloc(sizeof(__double_vector_struct_t__));
	v->__v__ = (double*) malloc(sizeof(double) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = 0;
	return v;
}

double_vector_t double_vec_null_vector()
{
	double_vector_t v = (double_vector_t) malloc(sizeof(__double_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

boolean_vector_t bool_vec_new_vector(size_t len)
{
	boolean_vector_t v = (boolean_vector_t) malloc(sizeof(__boolean_vector_struct_t__));
	v->__v__ = (bool*) malloc(sizeof(bool) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = false;
	return v;
}

boolean_vector_t bool_vec_null_vector()
{
	boolean_vector_t v = (boolean_vector_t) malloc(sizeof(__boolean_vector_struct_t__));
	v->__v__ = NULL;
	v->__len__ = 0;
	v->__max_len__ = 0;
	return v;
}

string_vector_t str_vec_new_vector(size_t len)
{
	string_vector_t v = (string_vector_t) malloc(sizeof(__string_vector_struct_t__));
	v->__v__ = (string_ptr_t) malloc(sizeof(string_t) * len);
	v->__len__ = len;
	v->__max_len__ = len;
	for (size_t i = 0; i < len; i++)
		v->__v__[i] = str_null_string();
	return v;
}

string_vector_t str_vec_null_vector()
{
	string_vector_t v = (string_vector_t) malloc(sizeof(__string_vector_struct_t__));
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
	v->__v__ = (any_ptr_t) realloc(v->__v__, sizeof(any_t) * v->__max_len__);
}

void __int_vec_res__(int_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (int_t*) realloc(v->__v__, sizeof(int_t) * v->__max_len__);
}

void __uint_vec_res__(uint_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (uint_t*) realloc(v->__v__, sizeof(uint_t) * v->__max_len__);
}

void __byte_vec_res__(byte_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (uint8_t*) realloc(v->__v__, sizeof(uint8_t) * v->__max_len__);
}

void __float_vec_res__(float_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (float*) realloc(v->__v__, sizeof(float) * v->__max_len__);
}

void __double_vec_res__(double_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (double*) realloc(v->__v__, sizeof(double) * v->__max_len__);
}

void __bool_vec_res__(boolean_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (bool*) realloc(v->__v__, sizeof(bool) * v->__max_len__);
}

void __str_vec_res__(string_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (string_ptr_t) realloc(v->__v__, sizeof(string_t) * v->__max_len__);
}

void __ustr_vec_res__(ustring_vector_t v)
{
	v->__max_len__ += __VEC_BLOCK_SIZE__;
	v->__v__ = (unique_string_ptr_t) realloc(v->__v__, sizeof(unique_string_t) * v->__max_len__);
}

void vec_append(vector_t v, any_t e) { __vec_append__(v, e); }
void int_vec_append(int_vector_t v, int_t e) { __vec_append__(v, e); }
void uint_vec_append(uint_vector_t v, uint_t e) { __vec_append__(v, e); }
void byte_vec_append(byte_vector_t v, uint8_t e) { __vec_append__(v, e); }
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
void vec_set(vector_t v, size_t i, any_t e) { __vec_set__(v, i, e); }
void int_vec_set(int_vector_t v, size_t i, int_t e) { __vec_set__(v, i, e); }
void uint_vec_set(uint_vector_t v, size_t i, uint_t e) { __vec_set__(v, i, e); }
void byte_vec_set(byte_vector_t v, size_t i, uint8_t e) { __vec_set__(v, i, e); }
void float_vec_set(float_vector_t v, size_t i, float e) { __vec_set__(v, i, e); }
void double_vec_set(double_vector_t v, size_t i, double e) { __vec_set__(v, i, e); }
void bool_vec_set(boolean_vector_t v, size_t i, bool e) { __vec_set__(v, i, e); }
void str_vec_set(string_vector_t v, size_t i, string_t e) { __vec_set__(v, i, e); }
void ustr_vec_set(ustring_vector_t v, size_t i, unique_string_t e) { __vec_set__(v, i, e); }

// ANY

any_t __any_int__(int_t n)
{
	any_t a = __any_alloc__();
	int_t *p = (int_t*) malloc(sizeof(int_t));
	*p = n;
	a->__t__ = INTEGER;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_uint__(uint_t n)
{
	any_t a = __any_alloc__();
	uint_t *p = (uint_t*) malloc(sizeof(uint_t));
	*p = n;
	a->__t__ = UNSIGNED_INTEGER;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_byte__(uint8_t b)
{
	any_t a = __any_alloc__();
	uint8_t *p = (uint8_t*) malloc(sizeof(uint8_t));
	*p = b;
	a->__t__ = BYTE;
	a->__value__ = (void*) p;
	
	return a;
}

any_t __any_float__(float f)
{
	any_t a = __any_alloc__();
	float *p = (float*) malloc(sizeof(float));
	*p = f;
	a->__t__ = FLOAT;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_double__(double d)
{
	any_t a = __any_alloc__();
	double *p = (double*) malloc(sizeof(double));
	*p = d;
	a->__t__ = DOUBLE;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_boolean__(bool d)
{
	any_t a = __any_alloc__();
	bool *p = (bool*) malloc(sizeof(bool));
	*p = d;
	a->__t__ = BOOLEAN;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_char__(char_t c)
{
	any_t a = __any_alloc__();
	char_t *p = (char_t*) malloc(sizeof(char_t));
	*p = c;
	a->__t__ = CHAR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_string__(string_t s)
{
	any_t a = __any_alloc__();
	string_t *p = (string_t*) malloc(sizeof(string_t));
	*p = s;
	a->__t__ = STRING;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_ustring__(unique_string_t u)
{
	any_t a = __any_alloc__();
	unique_string_t *p = (unique_string_t*) malloc(sizeof(unique_string_t));
	*p = u;
	a->__t__ = STRING;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_vector__(vector_t v)
{
	any_t a = __any_alloc__();
	vector_t *p = (vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_int_vector__(int_vector_t v)
{
	any_t a = __any_alloc__();
	int_vector_t *p = (int_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = INTEGER_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_uint_vector__(uint_vector_t v)
{
	any_t a = __any_alloc__();
	uint_vector_t *p = (uint_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = UNSIGNED_INTEGER_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_byte_vector__(byte_vector_t v)
{
	any_t a = __any_alloc__();
	byte_vector_t *p = (byte_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = BYTE_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_float_vector__(float_vector_t v)
{
	any_t a = __any_alloc__();
	float_vector_t *p = (float_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = FLOAT_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_double_vector__(double_vector_t v)
{
	any_t a = __any_alloc__();
	double_vector_t *p = (double_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = DOUBLE_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_boolean_vector__(boolean_vector_t v)
{
	any_t a = __any_alloc__();
	boolean_vector_t *p = (boolean_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = BOOLEAN_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_string_vector__(string_vector_t v)
{
	any_t a = __any_alloc__();
	string_vector_t *p = (string_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = STRING_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_ustring_vector__(ustring_vector_t v)
{
	any_t a = __any_alloc__();
	ustring_vector_t *p = (ustring_vector_t*) malloc(sizeof(unique_string_t));
	*p = v;
	a->__t__ = STRING_VECTOR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_int_ptr__(int_t *r) 
{
	any_t a = __any_alloc__();
	int_t **p = (int_t**) malloc(sizeof(int_t*));
	*p = r;
	a->__t__ = INTEGER_PTR;
	a->__value__ = (void*) p;

	return a;
}	

any_t __any_uint_ptr__(uint_t *r) 
{
	any_t a = __any_alloc__();
	uint_t **p = (uint_t**) malloc(sizeof(uint_t*));
	*p = r;
	a->__t__ = UNSIGNED_INTEGER_PTR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_byte_ptr__(uint8_t *r) 
{
	any_t a = __any_alloc__();
	uint8_t **p = (uint8_t**) malloc(sizeof(uint8_t*));
	*p = r;
	a->__t__ = BYTE_PTR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_float_ptr__(float *r) 
{
	any_t a = __any_alloc__();
	float **p = (float**) malloc(sizeof(float*));
	*p = r;
	a->__t__ = FLOAT_PTR;
	a->__value__ = (void*) p;

	return a;
}	

any_t __any_double_ptr__(double *r)
{
	any_t a = __any_alloc__();
	double **p = (double**) malloc(sizeof(double*));
	*p = r;
	a->__t__ = DOUBLE_PTR;
	a->__value__ = (void*) p;

	return a;
}

any_t __any_boolean_ptr__(bool *r)
{
	any_t a = __any_alloc__();
	bool **p = (bool**) malloc(sizeof(bool*));
	*p = r;
	a->__t__ = STRING_VECTOR;
	a->__value__ = (void*) p;

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
int_t any_get_int(any_t a) { return *((int_t*) (a->__value__)); }
uint_t any_get_uint(any_t a) { return *((uint_t*) (a->__value__)); }
uint8_t any_get_byte(any_t a) { return *((uint8_t*) (a->__value__)); }
float any_get_float(any_t a) { return *((float*) (a->__value__)); }
double any_get_double(any_t a) { return *((double*) (a->__value__)); }
bool any_get_boolean(any_t a) { return *((bool*) (a->__value__)); }
char_t any_get_char(any_t a) { return *((char_t*) (a->__value__)); }
string_t any_get_string(any_t a) { return *((string_t*) (a->__value__)); }
vector_t any_get_vector(any_t a) { return *((vector_t*) (a->__value__)); }
int_vector_t any_get_int_vector(any_t a) { return *((int_vector_t*) (a->__value__)); }
uint_vector_t any_get_uint_vector(any_t a) { return *((uint_vector_t*) (a->__value__)); }
byte_vector_t any_get_byte_vector(any_t a) { return *((byte_vector_t*) (a->__value__)); }
float_vector_t any_get_float_vector(any_t a) { return *((float_vector_t*) (a->__value__)); }
double_vector_t any_get_double_vector(any_t a) { return *((double_vector_t*) (a->__value__)); }
boolean_vector_t any_get_boolean_vector(any_t a) { return *((boolean_vector_t*) (a->__value__)); }
string_vector_t any_get_string_vector(any_t a) { return *((string_vector_t*) (a->__value__)); }
int_t *any_get_int_ptr(any_t a) { return *((int_t**) (a->__value__)); }
uint_t *any_get_uint_ptr(any_t a) { return *((uint_t**) (a->__value__)); }
uint8_t *any_get_byte_ptr(any_t a) { return *((uint8_t**) (a->__value__)); }
float *any_get_float_ptr(any_t a) { return *((float**) (a->__value__)); }
double *any_get_double_ptr(any_t a) { return *((double**) (a->__value__)); }
bool *any_get_boolean_ptr(any_t a) { return *((bool**) (a->__value__)); }
type_t any_typeof(any_t a) { return a->__t__; }

any_t any_null()
{
	any_t a = __any_alloc__();
	a->__t__ = NONE_TYPE;
	a->__value__ = NULL;
	return a;
}

bool __any_is_null__(any_t a)
{
	return a->__t__ == NONE_TYPE && a->__value__ == NULL;
}

// NULL

bool __int_is_null__(int_t n) { return n == 0; }
bool __double_is_null__(double n) { return n == 0; }
bool __ptr_is_null__(void *p) { return p == NULL; }


// IO

int_t console_int_read()
{
	int_t n = 0;
	scanf_s("%d", &n);
	return n;
}

uint_t console_uint_read()
{
	uint_t n = 0;
	scanf_s("%u", &n);
	return n;
}

float console_float_read()
{
	float n = 0;
	scanf_s("%f", &n);
	return n;
}

double console_double_read()
{
	double n = 0;
	scanf_s("%lf", &n);
	return n;
}

string_t console_str_read()
{
	char_t temp_buffer[__TEMP_BUF_SIZE__ + 1] = {0};
	gets_s(temp_buffer, __TEMP_BUF_SIZE__);

	return str_new_string(temp_buffer);
}

// unique_string_t console_ustr_read()
// {
// 	char_t temp_buffer[__TEMP_BUF_SIZE__ + 1] = {0};
// 	scanf_s(__STR_FORMAT__, temp_buffer);
// 	return ustr_new_string(temp_buffer);
// }

void console_write(any_t a)
{
	printf("%s", to_string(a));
}

void console_str_write(string_t s)
{
	printf("%s", s);
}

void console_ustr_write(unique_string_t s)
{
	printf("%s", s);
}

// in 1.1
// JSON library
// REGEX library
// FILE / STREAM library
// RANGE library
// ASSOCIATIVE VECTOR library
// LIST (doubly linked list)