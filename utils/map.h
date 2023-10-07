/**
 * @file map.h
 * @author Ancona Simone
 * @brief The map type definition
 * @version 1.1 (utils 1.1)
 * @date 2023-10-07
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once

#ifndef _MAP_H_
#define _MAP_H_

#include "type.h"
#include "any.h"

#define __map_null_check__(m) m->__k__ == NULL;

map_t map_new_map(); // since v1.1
map_t map_null_map();      // since v1.1
void map_insert(map_t, any_t, any_t);
any_t map_get(map_t, any_t);
void map_set(map_t, any_t, any_t);
bool map_remove(map_t, any_t);
size_t map_len(map_t);

map_t map_new_map()
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

void map_insert(map_t m, any_t k, any_t v)
{
    if (m == NULL) return;
    if (m->__k__ == NULL)
    {
        m->__k__ = k;
        m->__v__ = v;
        m->__next__ = NULL;
        return;
    }
    m->__next__ = malloc(sizeof(__map_struct_t__));
    m = m->__next__;
    m->__k__ = k;
    m->__v__ = v;
    m->__next__ = NULL;
}

any_t map_get(map_t m, any_t k)
{
    for (; m->__next__ != NULL; m = m->__next__)
    {
        if (any_equals(m->__k__, k))
            return m->__v__;
    }
    return any_null();
}

void map_set(map_t m, any_t k, any_t v)
{
    for (; m->__next__ != NULL; m = m->__next__)
    {
        if (any_equals(m->__k__, k))
        {
            m->__v__ = v;
            return;
        }
    }
}

bool map_remove(map_t m, any_t k)
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

#endif