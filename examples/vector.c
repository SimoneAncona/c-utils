/*
Vectors are used to store a different number of elements
*/

#include "utils.h"

int main(int argc, char **argv) 
{
	vector_t vec = vec_new_vector(10);
	vec_set(vec, 0, 20);
}