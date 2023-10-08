/*
Maps are used to associate a key to a value. In programming, a map is an unordered collection of key-value pairs.
*/

#include "utils.h"

int main(int argc, char **argv)
{
   number_t n1 = int_to_num(2342354345);
   number_t n2 = str_to_num("+34534509834590395903485903809824882349023889042903498409");
   printf("%s\n", num_to_string(n1));
   printf("%s\n", num_to_string(n2));
}