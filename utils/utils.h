/**
 * @file utils.h
 * @name Utils Cross-platform Library Collection
 * @author Ancona Simone
 * @brief This library is a collection of multiple libraries designed
 * to improve and enrich the C language.
 * @version 1.0
 * @date 2022-09-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _UTILS_H_
#define _UTILS_H_

#define UTILS_VERSION "1.1"
#define UTILS_VERSION_MAJOR 1
#define UTILS_VERSION_MINOR 1
#define UTILS_VERSION_1_1

#include "char.h"
#include "null.h"
#include "iterator.h"
#include "range.h"
#include "any.h"
#include "vector.h"
#include "number.h"
#include "map.h"
#include "unique_string.h"
#include "string.h"
#include "common.h"
#include "io.h"
#include "type.h"

void __any_destroy__(any_t a)
{
    switch (a->__t__)
    {
    case VECTOR:
        vector_t v = (vector_t)a->__value__;
        vec_destroy(v);
        break;
    case INTEGER_VECTOR:
        int_vector_t iv = (int_vector_t)a->__value__;
        vec_destroy(iv);
        break;
    case UNSIGNED_INTEGER_VECTOR:
        uint_vector_t uiv = (uint_vector_t)a->__value__;
        vec_destroy(uiv);
        break;
    case FLOAT_VECTOR:
        float_vector_t fv = (float_vector_t)a->__value__;
        vec_destroy(fv);
        break;
    case DOUBLE_VECTOR:
        double_vector_t dv = (double_vector_t)a->__value__;
        vec_destroy(dv);
        break;
    case BYTE_VECTOR:
        byte_vector_t bv = (byte_vector_t)a->__value__;
        vec_destroy(bv);
        break;
    case BOOLEAN_VECTOR:
        boolean_vector_t bv2 = (boolean_vector_t)a->__value__;
        vec_destroy(bv2);
        break;
    case STRING_VECTOR:
        string_vector_t sv = (string_vector_t)a->__value__;
        vec_destroy(sv);
        break;
    case STRING:
        string_t str = (string_t)a->__value__;
        str_destroy(str);
        break;
    case MAP:
        map_t m = (map_t)a->__value__;
        map_destroy(m);
        break;
    default:
        free(a);
    }
}

#endif // _UTILS_H_