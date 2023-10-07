#include "../utils/utils.h"

int main(int argc, char **argv)
{
    map_t map = map_new_map();
    map_insert(map, any_new("nome"), any_new("pippo"));
    map_insert(map, any_new("cognome"), any_new("pluto"));
    printf("%s\n", to_string(map_get(map, any_new("nome"))));
    printf("%s\n", to_string(map));
}