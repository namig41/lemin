#include "lemin.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
    t_nodes		*nodes = NULL;

    parse_file(argv[1], &nodes);

    printf("%d\n", g_ants);
    print_nodes(nodes);

    return (0);
}
