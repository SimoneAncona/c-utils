/**
 * @file map.h
 * @author Ancona Simone
 * @brief The map type definition
 * @version 1.1 (utils 1.1)
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "type.h"
#include "any.h"

#define __map_null_check__(m) m->__k__ == NULL;

/**
 * Create a new map
 * @return the new map
 * @since v1.1
*/
map_t map();

map_t map_null_map();

/**
 * Insert a new key-value pair into the map
 * @param m the map
 * @param k the key
 * @param v the value
 * @return true if successful
 * @since v1.1
*/
#define map_insert(m, k, v) __map_insert__(m, any_new(k), any_new(v))

/**
 * Get the value associated with the key
 * @param m the map
 * @param k the key
 * @return the value associated with the key or null
 * @since v1.1
*/
#define map_get(m, k) __map_get__(m, any_new(k))

/**
 * Set the value associated with the key
 * @param m the map
 * @param k the key
 * @param v the new value
 * @return the old value associated with the key or null
 * @since v1.1
*/
#define map_set(m, k, v) __map_set__(m, any_new(k), any_new(v))

/**
 * Remove the key-value pair from the map
 * @param m the map
 * @param k the key
 * @return true if successful
 * @since v1.1
*/
#define map_remove(m, k) __map_remove__(m, any_new(k))

/**
 * Destroy the map
 * @param m the map
*/
#define map_destroy(m) __map_destroy__(m); free(m); m = NULL

bool __map_insert__(map_t, any_t, any_t); 
any_t __map_get__(map_t, any_t);          
any_t __map_set__(map_t, any_t, any_t);    
bool __map_remove__(map_t, any_t);        
size_t map_len(map_t);                    
void __map_destroy__(map_t);              

map_t map()
{
    return map_null_map();
}

map_t map_null_map()
{
    map_t map = (map_t)malloc(sizeof(__map_struct_t__));
    map->__k__ = NULL;
    map->__v__ = NULL;
    return map;
}

size_t map_len(map_t m)
{
    size_t len;
    for (len = 0; m->__next__ != NULL; m = m->__next__, len++)
        ;
    return len;
}

bool __map_insert__(map_t m, any_t k, any_t v)
{
    if (m == NULL)
        return false;
    if (m->__k__ == NULL)
    {
        m->__k__ = k;
        m->__v__ = v;
        m->__next__ = NULL;
        return true;
    }
    if (m->__next__ == NULL)
    {
        if (any_equals(m->__k__, k))
            return false;
        m->__next__ = malloc(sizeof(__map_struct_t__));
        m = m->__next__;
        m->__k__ = k;
        m->__v__ = v;
        m->__next__ = NULL;
        return true;
    }
    for (; m->__next__ != NULL; m = m->__next__)
    {
        if (any_equals(m->__k__, k))
            return false;
    }
    m->__next__ = malloc(sizeof(__map_struct_t__));
    m = m->__next__;
    m->__k__ = k;
    m->__v__ = v;
    m->__next__ = NULL;
    return true;
}

any_t __map_get__(map_t m, any_t k)
{
    if (m == NULL)
        return NULL;
    if (m->__next__ == NULL)
    {
        if (any_equals(m->__k__, k))
            return m->__v__;
        return any_null();
    }
    for (; m->__next__ != NULL; m = m->__next__)
    {
        if (any_equals(m->__k__, k))
            return m->__v__;
    }
    return any_null();
}

any_t __map_set__(map_t m, any_t k, any_t v)
{
    any_t old_v;
    for (; m->__next__ != NULL; m = m->__next__)
    {
        if (any_equals(m->__k__, k))
        {
            old_v = m->__v__;
            m->__v__ = v;
            return old_v;
        }
    }
    return NULL;
}

bool __map_remove__(map_t m, any_t k)
{
    if (m == NULL)
        return false;
    if (any_equals(m->__k__, k))
    {
        if (m->__next__ != NULL)
        {
            m->__k__ = ((map_t)m->__next__)->__k__;
            m->__v__ = ((map_t)m->__next__)->__v__;
            m->__next__ = ((map_t)m->__next__)->__next__;
            return true;
        }
        m->__k__ = NULL;
        m->__v__ = NULL;
        m->__next__ = NULL;
        return true;
    }
    map_t temp = m->__next__;
    for (; temp != NULL && !any_equals(temp->__k__, k); m = temp, temp = temp->__next__)
        ;
    if (temp == NULL)
        return false;
    m->__next__ = temp->__next__;
    return true;
}

void __map_destroy__(map_t m)
{
    map_t next;
    for (; m->__next__ != NULL; m = next)
    {
        next = m->__next__;
        any_destroy(m->__k__);
        any_destroy(m->__v__);
        free(m);
    }
}

#endif