/*
Maps are used to associate a key to a value. In programming, a map is an unordered collection of key-value pairs.
*/

#include "utils.h"

int main(int argc, char **argv)
{
    map_t map = map_new_map();
    map_insert(map, "key1", "value1");
    map_insert(map, "key2", "value2");

    printf("map: %s\n", to_string(map)); // expected output: {"key1": "value1", "key2": "value2"}

    map_remove(map, "key1");
    printf("get 'key1': %s\n", to_string(map_get(map, "key1"))); // expected output: null
    printf("get 'key2': %s\n", to_string(map_get(map, "key2"))); // expected output: "value2"

    if (!map_insert(map, "key2", "value3"))
        printf("key2 already exists\n");

    map_insert(map, "key3", "value3");
    map_insert(map, "name", "Luca");
    map_insert(map, "age", 30);

    printf("map: %s\n", to_string(map));    // expected output: {"key2": "value2", "key3": "value3"}

    // map iterator
    for (iterator_t i = it(map); i.ptr != end(map); it_inc(&i))
    {
        printf("%s: %s\n", to_string(it_get_key(i)), to_string(it_get_value(i)));
        if (any_equals(it_get_key(i), any_new("name")))
            it_get_value(i) = any_new("Simon");
    }
    printf("%s: %s\n", to_string(it_get_key(rit(map))), to_string(it_get_value(rit(map))));

    printf("map: %s\n", to_string(map)); 
}