/*
Vectors are used to store a different number of elements
*/

#include "utils.h"

int main(int argc, char **argv)
{
   number_t num1 = str_to_num("234453545.34259239432959234554994000453");
   number_t num2 = int_to_num(2348923);
   printf("Number1: %s\n", to_string(num1));
   printf("Number2: %s\n", to_string(num2));
   printf("PI: %s\n", to_string(get_PI()));
}