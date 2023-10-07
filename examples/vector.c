/*
Vectors are used to store a different number of elements
*/

#include "utils.h"

int main(int argc, char **argv) 
{
	vector_t vec = vec_new_vector(10);
	vec_set(vec, 0, 20);
    vec_set(vec, 1, "Hello");

    printf("%s\n", to_string(vec));

    for (iterator_t i = it(vec); i.ptr < end(vec); it_inc(&i))
    {
        printf("%s\n", to_string(it_get_el(i)));
        if (it_get_el(i) != NULL)
            it_get_el(i) = any_new(234);
    }

    printf("%s\n", to_string(vec));
}