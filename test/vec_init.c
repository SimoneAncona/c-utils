#include "../utils/utils.h"

int main(int argc, char **argv)
{
    vector_t v = vec_new_vector(10);
    printf("%s", to_string(v));
    return 0;
}