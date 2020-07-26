
#include "lemin.h"

int main(void)
{
    t_nodes		*nodes;
    t_options 	*options;

	add_option(&options);
	parse_file(&nodes);
	suurballe(nodes, options);
	options = choose_ways(options);
	print_lems(options->paths);
	clean_memory(&options, &nodes);

    return (0);
}
