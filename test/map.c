#include "../utils/utils.h"

int main(int argc, char **argv)
{
    map_t map = map_new_map();
    map_insert(map, "nome", "pippo");
    map_insert(map, "cognome", "pluto");
    map_insert(map, 0, "ciao");
    printf("%s\n", to_string(map_get(map, "nome")));
    printf("%s\n", to_string(map_get(map, 8)));
    printf("%s\n", to_string(map));
}