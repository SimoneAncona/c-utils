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
#define _PERIOD_ (byte_t) - 1

#define _POSITIVE_ (byte_t)0
#define _NEGATIVE_ (byte_t)1

#ifndef EQUAL
#define EQUAL (uint8_t) true
#endif
#ifndef NOT_EQUAL
#define NOT_EQUAL (uint8_t) false
#endif
#ifndef GRATER
#define GRATER (uint8_t)2
#endif
#ifndef LESS
#define LESS (uint8_t)3
#endif

extern byte_vector_t byte_vec_new_vector(size_t);
extern void byte_vec_append(byte_vector_t v, byte_t e);
#define __compare_opp__(b) b == GRATER ? LESS : GRATER

number_t number(void);
number_t num_sum(number_t, number_t);
number_t num_diff(number_t, number_t);
number_t num_opposite(number_t);
byte_t num_compare(number_t, number_t);
bool num_is_zero(number_t);
double num_to_double(number_t);
int_t num_to_int(number_t);
number_t int_to_num(int_t);
number_t float_to_num(float);
number_t double_to_num(double);
number_t str_to_num(string_t);
number_t get_PI();
number_t get_E();
byte_t __compare_byte_buffer__(byte_vector_t, byte_vector_t);
byte_t __compare_normalized_byte_buffer__(byte_vector_t, byte_vector_t);

number_t number()
{
    number_t n = malloc(sizeof(__num_struct_t__));
    n->__e__ = 0;
    n->__n__ = byte_vec_new_vector(0);
    n->__negative__ = false;
    return n;
}

bool num_is_zero(number_t n)
{
    for (size_t i = 0; i < n->__n__->__len__; i++)
        if (n->__n__->__v__[i] != 0)
            return false;
    return true;
}

byte_t num_compare(number_t n1, number_t n2)
{
    if (num_is_zero(n1) && num_is_zero(n2))
        return EQUAL;
    if (n1->__negative__ && !n2->__negative__)
        return LESS;
    if (!n1->__negative__ && n2->__negative__)
        return GRATER;
    byte_t e = n1->__e__ > n2->__e__ ? GRATER : n1->__e__ < n2->__e__ ? LESS
                                                                      : EQUAL;
    if (e != EQUAL)
        return n1->__negative__ ? __compare_opp__(e) : e;
    byte_t v = __compare_byte_buffer__(n1->__n__, n2->__n__);
    if (e == EQUAL)
        return e;
    return n1->__negative__ ? __compare_opp__(v) : v;
}

byte_t __compare_byte_buffer__(byte_vector_t v1, byte_vector_t v2)
{
    byte_t result;
    if (v1->__len__ > v2->__len__)
    {
        v2 = byte_vec_new_vector(v1->__len__);
        vec_copy(v2, v1);
        result = __compare_normalized_byte_buffer__(v1, v2);
        vec_destroy(v2);
        return result;
    }

    if (v1->__len__ < v2->__len__)
    {
        v1 = byte_vec_new_vector(v2->__len__);
        vec_copy(v1, v2);
        result = __compare_normalized_byte_buffer__(v1, v2);
        vec_destroy(v1);
        return result;
    }

    return __compare_normalized_byte_buffer__(v1, v2);
}

byte_t __compare_normalized_byte_buffer__(byte_vector_t v1, byte_vector_t v2)
{
    for (size_t i = 0; i < v1->__len__; i++)
    {
        if (v1->__v__[i] > v2->__v__[i])
            return GRATER;
        if (v1->__v__[i] < v2->__v__[i])
            return LESS;
    }
    return EQUAL;
}

number_t int_to_num(int_t n)
{
    number_t res = number();
    res->__negative__ = n < 0;
    int64_t exp = 0;
    while (n >= 1)
    {
        byte_vec_insert(res->__n__, 0, n % 10);
        n = n / 10;
        exp++;
    }
    res->__e__ = exp;
    return res;
}

number_t str_to_num(string_t str)
{
    size_t slen = str_len(str);
    number_t n = number();
    if (str == NULL || slen == 0) return n;
    size_t skip_zeros = 0;
    size_t period = 0;
    bool real = false;
    size_t i = 0;
    if (str[0] == '+' || str[0] == '-')
    {
        i++;
        n->__negative__ = str[0] == '-';
    }

    for (; i < slen; i++)
    {
        if (!(chr_is_digit(str[i]) || str[i] == '.'))
            return n;
        if (str[i] == '.')
        {
            if (real)
                return n;
            real = true;
            period = i;
            continue;
        }
        if (str[i] != '0')
            break;
        skip_zeros++;
    }

    for (; i < slen; i++)
    {
        if (!(chr_is_digit(str[i]) || str[i] == '.'))
            return n;
        if (str[i] == '.')
        {
            if (real)
                return n;
            real = true;
            period = i;
            continue;
        }
        byte_vec_append(n->__n__, str[i] - '0');
    }
    if (real)
    {
        n->__e__ = period - skip_zeros;
        return n;
    }
    n->__e__ = n->__n__->__len__;
    return n;
}

number_t get_PI()
{
    return str_to_num("3.1415926535897932384626433832795");
}

number_t get_E()
{
    return str_to_num("2.7182818284590452353602874713527");
}

#endif