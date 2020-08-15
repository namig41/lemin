/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:18:40 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:18:43 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int				main(int argc, char *argv[])
{
	t_nodes		*nodes;
	t_options	*options;

	nodes = NULL;
	options = NULL;
	g_fd = open(argv[1], O_RDONLY);
	add_option(&options);
	parse_file(&nodes);
	suurballe(nodes, options);
	options = choose_ways(options);
	if (options->paths->nodes_count != 0)
		print_lems(options->paths);
	else
		ft_putendl("ERROR");
	clean_memory(&options, &nodes);
	return (0);
}
