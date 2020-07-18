#include "lemin.h"
#include <stdio.h>


int main(int argc, char* argv[])
{
    t_nodes		*nodes = NULL;
    t_relations	*relations = NULL;

    parse_file(argv[1], &nodes, &relations);

    printf("Number ants: %d\n", g_ants);
    print_nodes(nodes);
    print_relations(relations);

    return (0);
}
