
#include "lemin.h"
#include <fcntl.h>

int main(int argc, char *argv[])
{
    t_nodes		*nodes;
    t_options 	*options;
	char *line;

	g_fd = open(argv[1], O_RDONLY);
	//add_option(&options);
	parse_file(&nodes);
	//suurballe(nodes, options);
	//options = choose_ways(options);
	//print_lems(options->paths);
	//clean_memory(&options, &nodes);

    return (0);
}
