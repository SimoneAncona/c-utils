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

#ifndef _RANGE_H_
#define _RANGE_H_

/**
 * Create a range from a start and an end
 * @param x the start of the range (inclusive)
 * @param y the end of the range (exclusive)
 * @since v1.1
*/
#define range(x, y) {x, y}

/**
 * Check if a number is in a range
 * @param r the range
 * @param v the number to check
 * @return true if the number is in the range, false otherwise
*/
#define range_contains(r, v) r.__start__ <= v && v < r.__end__

#endif