#include "type.h"

#pragma once

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

int_t console_int_read()
{
	int_t n = 0;
	scanf_s("%d", &n);
	return n;
}

uint_t console_uint_read()
{
	uint_t n = 0;
	scanf_s("%u", &n);
	return n;
}

float console_float_read()
{
	float n = 0;
	scanf_s("%f", &n);
	return n;
}

double console_double_read()
{
	double n = 0;
	scanf_s("%lf", &n);
	return n;
}

string_t console_str_read()
{
	char_t temp_buffer[__TEMP_BUF_SIZE__ + 1] = {0};
	gets_s(temp_buffer, __TEMP_BUF_SIZE__);

	return str_new_string(temp_buffer);
}

// unique_string_t console_ustr_read()
// {
// 	char_t temp_buffer[__TEMP_BUF_SIZE__ + 1] = {0};
// 	scanf_s(__STR_FORMAT__, temp_buffer);
// 	return ustr_new_string(temp_buffer);
// }

void console_write(any_t a)
{
	printf("%s", to_string(a));
}

void console_str_write(string_t s)
{
	printf("%s", s);
}

void console_ustr_write(unique_string_t s)
{
	printf("%s", s);
}
