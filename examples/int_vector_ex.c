#include "../utils/utils.h"

int main(int argc, char **argv) 
{
	int_vector_t vector;	// declate a vector variable
	vector = int_vec_new_vector(10);	// initialize the vector with a length of 10

	// filling the vector with values from 0 to 10

	for (int_t i = 0; i < len(vector); i++) {
		int_vec_set(vector, i, i);
	}

	printf("%s", to_string(vector));
}