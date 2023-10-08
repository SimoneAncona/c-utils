#include "utils.h"

int main(int argc, char **argv)
{
    range_t r = range(0, 10);
    if (range_contains(r, 4))
        printf("4 in [0, 10)\n");

    for (iterator_t i = it(r); i.ptr < it_end(r); it_inc(&i))
    {
        printf("%lld ", it_ptr(int_t, i));
    }
    console_write(any_new(4));
    return 0;
}