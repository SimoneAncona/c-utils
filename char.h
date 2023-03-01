/**
 * @file char.h
 * @author Ancona Simone
 * @version 1.0 (utils 1.0)
 * @date 2022-09-13
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef _CHAR_H_
#define _CHAR_H_
#include "type.h"

// #ifndef WCHAR
#define chr_to_lower(x) tolower(x) // since v1.0
#define chr_to_upper(x) toupper(x) // since v1.0
#define chr_is_alnum(x) isalnum(x) // since v1.0
#define chr_is_alpha(x) isalpha(x) // since v1.0
#define chr_is_digit(x) isdigit(x) // since v1.0
#define chr_is_lower(x) islower(x) // since v1.0
#define chr_is_upper(x) isupper(x) // since v1.0
// #else
// 	#define chr_to_lower(x) towlower(x);
// 	#define chr_to_upper(x) towupper(x);
// 	#define chr_is_alnum(x) iswalnum(x);
// 	#define chr_is_alpha(x) iswalpha(x);
// 	#define chr_is_digit(x) iswdigit(x);
// 	#define chr_is_lower(x) iswlower(x);
// 	#define chr_is_upper(x) iswupper(x);
// #endif

#endif