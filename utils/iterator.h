/**
 * @file iterator.h
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

/**
 * Create an iterator
 * @param x an iterable object
 * @return an iterator
 * @since v1.1
*/
#define it(x) _Generic((x),\
    string_t: __string_it__,\
    vector_t: __vector_it__,\
    map_t: __map_it__,\
    range_t: __range_it__\
) (x)

/**
 * Create a reverse iterator
 * @param x an iterable object
 * @return a reverse iterator
 * @since v1.1
*/
#define rit(x) _Generic((x),\
    string_t: __string_rit__,\
    vector_t: __vector_rit__,\
    map_t: __map_rit__,\
    range_t: __range_rit__\
) (x)

/**
 * Get the first element of an iterable
 * @param x the iterable
 * @return a pointer to the first element of the iterable
 * @since v1.1
*/
#define it_begin(x) it(x).ptr

/**
 * Get the last element of an iterable
 * @param x the iterable
 * @return a pointer to the last element of the iterable
 * @since v1.1
*/
#define it_end(x) rit(x).ptr

/**
 * Get a key from a map iterator
 * @param i a map iterator
 * @return the map key
 * @since v1.1
*/
#define it_key(i) (any_t)/*cannot change keys*/((map_t)i.ptr)->__k__

/**
 * Get the value from a map iterator
 * @param i a map iterator
 * @return the map value
 * @since v1.1
*/
#define it_value(i) ((map_t)i.ptr)->__v__

/**
 * Get the element pointed by an iterator
 * @param t the type of the element
 * @param i an iterator
 * @return the elemet reference
 * @since v1.1
*/
#define it_el(t, i) *((t)i.ptr)

/**
 * Get the pointer of the iterator
 * @param t the type of the element
 * @param i an iterator
 * @return the pointer of the iterator
 * @since v1.1
*/
#define it_ptr(t, i) (t)i.ptr

/**
 * Increment an iterator
 * @param it the iterator
 * @since v1.1
*/
void it_inc(iterator_t *);

/**
 * Decrement an iterator
 * @param it the iterator
 * @since v1.1
*/
void it_dec(iterator_t *);

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

iterator_t __range_it__(range_t r)
{
    iterator_t it;
    it.ptr = (void*) (uint_t)r.__start__;
    it.__size__ = 1;
    it.__type__ = RANGE;

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

iterator_t __range_rit__(range_t r)
{
    iterator_t it;
    it.ptr = (void*) (uint_t)r.__end__;
    it.__size__ = 1;
    it.__type__ = RANGE;

    return it;
}

void it_inc(iterator_ptr_t it)
{
    switch (it->__type__)
    {
    case STRING:
    case VECTOR:
    case RANGE:
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
    case RANGE:
        it->ptr = (void*) ((uint_t)it->ptr - it->__size__);
        break;
    }
}

#endif