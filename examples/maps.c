/*
Maps are used to associate a key to a value. In programming, a map is an unordered collection of key-value pairs.
*/

#include "utils.h"

int main(int argc, char *argv[])
{
    map_t map = map_new_map();
    map_insert(map, "key1", "value1");
    map_insert(map, "key2", "value2");

    printf("%s\n", to_string(map)); // expected output: {"key1": "value1", "key2": "value2"}

    map_remove(map, "key1");
    printf("%s\n", to_string(map_get(map, "key1")));   // expected output: null
    printf("%s\n", to_string(map_get(map, "key2")));   // expected output: "value2"

    for (iterator_t i = it(map); i.ptr != end(map); it_inc(&i))
    {
        printf("%s: %s\n", ((map_t)i.ptr)->__k__, ((map_t)i.ptr)->__v__);
    }
}