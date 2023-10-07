/**
 * @file map.h
 * @author Ancona Simone
 * @brief This library implements iterators for vectors and maps.
 * @version 1.1 (utils 1.1)
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#ifndef _ITERATOR_H_
#define _ITERATOR_H_

#include "type.h"

extern size_t str_len(string_t);

#define it(x) _Generic((x),\
    string_t: __string_it__,\
    vector_t: __vector_it__,\
    map_t: __map_it__\
) (x)

#define rit(x) _Generic((x),\
    string_t: __string_rit__,\
    vector_t: __vector_rit__,\
    map_t: __map_rit__\
) (x)

#define begin(x) it(x).ptr
#define end(x) rit(x).ptr

#define it_get_key(i) ((map_t)i.ptr)->__k__
#define it_get_value(i) ((map_t)i.ptr)->__v__

#define it_get_el(i) *((any_ptr_t)i.ptr)

iterator_t __string_it__(string_t s)
{
    iterator_t it;
    it.ptr = (void*)s;
    it.__size__ = sizeof(s);
    it.__type__ = STRING;

    return it;
}

iterator_t __vector_it__(vector_t v)
{
    iterator_t it;
    it.ptr = (void*)v->__v__;
    it.__size__ = sizeof(any_ptr_t);
    it.__type__ = VECTOR;

    return it;
}

iterator_t __map_it__(map_t m)
{
    iterator_t it;
    it.ptr = (void*)m;
    it.__size__ = 0;
    it.__type__ = MAP;

    return it;
}

iterator_t __string_rit__(string_t s)
{
    iterator_t it;
    it.ptr = (void*) (s + str_len(s));
    it.__size__ = sizeof(s);
    it.__type__ = STRING;

    return it;
}

iterator_t __vector_rit__(vector_t v)
{
    iterator_t it;
    it.ptr = (void*) (v->__v__ + v->__len__);
    it.__size__ = sizeof(any_ptr_t);
    it.__type__ = VECTOR;

    return it;
}

iterator_t __map_rit__(map_t m)
{
    iterator_t it;
    map_t t = m;
    for (; t->__next__ != NULL; t = (map_t)t->__next__);
    it.ptr = (void*) t;
    it.__size__ = 0;
    it.__type__ = MAP;

    return it;
}

void it_inc(iterator_ptr_t it)
{
    switch (it->__type__)
    {
    case STRING:
    case VECTOR:
        it->ptr = (void*) ((uint_t)it->ptr + it->__size__);
        break;
    case MAP:
        it->ptr = (void*)((map_t)it->ptr)->__next__; 
        break;
    }
}

void it_dec(iterator_ptr_t it)
{
    switch (it->__type__)
    {
    case STRING:
    case VECTOR:
        it->ptr = (void*) ((uint_t)it->ptr - it->__size__);
        break;
    }
}

#endif