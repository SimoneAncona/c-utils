/**
 * @file number.h
 * @author Ancona Simone
 * @brief Arbitrary precision number library.
 * @version 1.1 (utils 1.1)
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#ifndef _NUM_H_
#define _NUM_H_

#include "type.h"
#define _PERIOD_ (byte_t)-1

#define _POSITIVE_ (byte_t)0
#define _NEGATIVE_ (byte_t)1

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

extern byte_vector_t byte_vec_new_vector(size_t);
extern void byte_vec_append(byte_vector_t v, byte_t e);

#define __is_not_valid_number__(num) (num == NULL || num->__len__ <= 1)
number_t num_new(void);
number_t num_sum(number_t, number_t);
number_t num_diff(number_t, number_t);
number_t num_opposite(number_t);
byte_t num_compare(number_t, number_t);
bool num_is_zero(number_t);
double num_to_double(number_t);
int_t num_to_int(number_t);
number_t int_to_num(int_t);
number_t str_to_num(string_t);

number_t num_new()
{
    number_t n = byte_vec_new_vector(2);
    return n;
}

bool num_is_zero(number_t n)
{
    if (__is_not_valid_number__(n)) return false;
    for (size_t i = 1; i < n->__len__; i++)
    {
        if (n->__v__[i] != 0 && n->__v__[i] != _PERIOD_) return false;
    }
    return true;
}

number_t num_sum(number_t n1, number_t n2)
{
    if (__is_not_valid_number__(n1)) return NULL;
    if (__is_not_valid_number__(n2)) return NULL;
    number_t n = num_new();
    if (n2->__v__[0] == n1->__v__[0])
    {
        n->__v__[0] = n1->__v__[0];
        byte_t s, r, c = 0;
        size_t i;
        for (i = 1; i < n1->__len__ && i < n2->__len__; i++)
        {
            s = n1->__v__[i] + n2->__v__[i] + c;
            r = s % 10;
            c = (s - r) / 10;
            n->__v__[i] = r;
            byte_vec_append(n, 0);
        }
        size_t ad = n1->__len__ > n2->__len__ ? n1->__len__ : n2->__len__;
        number_t g = n1->__len__ > n2->__len__ ? n1 : n2;
        for (; i < ad; i++) 
        {
            s = g->__v__[i] + c;
            r = s % 10;
            c = (s - r) / 10;
            n->__v__[i] = r;
            byte_vec_append(n, 0);
        }
    }
    return n;
}

number_t int_to_num(int_t n)
{
    number_t r = num_new();
    r->__v__[0] = n < 0 ? _NEGATIVE_ : _POSITIVE_;
    if (n < 0) n = -n;
    for (size_t i = 1; n > 0; i++) {
        r->__v__[i] = n % 10;
        n = n / 10;
        byte_vec_append(r, 0);
    }
    return r;
}


number_t str_to_num(string_t s)
{
    number_t n = num_new();
    size_t i = 0;
    size_t j = 1;
    bool is_negative = false;
    if (s[0] == '-')
    {
        i++;
        is_negative = true;
    } 
    else if (s[0] == '+') i++;
    for (; i < str_len(s); i++, j++) 
    {
        if (!chr_is_digit(s[i])) return n;
        n->__v__[i] = s[i] - '0';
        byte_vec_append(n, 0);
    }

    return n;
} 

#endif