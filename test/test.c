/*
Vectors are used to store a different number of elements
*/

#include "utils.h"

int main(int argc, char **argv)
{
   vector_t vec = vector(10);
   vec_set(vec, 0, 20);
   vec_set(vec, 1, "Hello");

   printf("%s\n", to_string(vec));

   for (iterator_t i = it(vec); i.ptr < it_end(vec); it_inc(&i))
   {
      printf("%s\n", to_string(it_el(any_ptr_t, i)));
      if (it_el(any_ptr_t, i) != NULL)
         it_el(any_ptr_t, i) = any_new(234);
   }

   //  printf("%s\n", to_string(vec));

   double_vector_t dvec = double_vector(0);
   for (size_t i = 0; i < 2'00; i++) 
   {
      double_vec_append(dvec, i % 2 ? -i : i * 2);
   }

   vec_sort(dvec, true);
   printf("%s\n", to_string(dvec));
}