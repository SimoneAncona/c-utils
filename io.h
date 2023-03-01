#include "type.h"

#define __TEMP_BUF_SIZE__ 2048
#define __STR_FORMAT__ "%2048s"

// any_t console_read();	// since v1.1
int_t console_int_read();	// since v1.0
uint_t console_uint_read();	// since v1.0
float console_float_read();	// since v1.0
double console_double_read();	// since v1.0
string_t console_str_read();	// since v1.0
// unique_string_t console_ustr_read();	// since v1.2
void console_write(any_t);	// since v1.0
void console_str_write(string_t);	// since v1.0
// void console_ustr_write(unique_string_t);	// since v1.2