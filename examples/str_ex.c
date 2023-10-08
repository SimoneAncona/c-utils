#include "../utils/utils.h"
#include <stdio.h>

int main(int argc, char **argv) 
{
	string_t str = str_new_string("Hello, World!");	// declare and init a new string
	printf("%zu\n", len(str));	// output: 13
	string_t from_num = str_from_int(10245);

	printf("%s\n", str_substr(str, 7, len(str)));

	printf("%s\n", str_concat(str, from_num));	// output: Hello, World!10245
}