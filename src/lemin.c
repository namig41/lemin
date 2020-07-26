
#include "lemin.h"

int main(int argc, char* argv[])
{
    t_nodes		*nodes;
    t_options 	*options;

	add_option(&options);
	parse_file(argv[1], &nodes);
	suurballe(nodes, options);
	options = choose_ways(options);
	print_lems(options->paths);
	clean_memory(&options, &nodes);

    return (0);
}
