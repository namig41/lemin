/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_relations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:58 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 14:20:00 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void 			parse_section_relation(char *line, t_nodes **nodes)
{
	char		**w_relation;
	t_nodes 	*n_from;
	t_nodes 	*n_to;
	t_relations *r_from;
	t_relations *r_to;

	parse_line_relation(line, &w_relation);
	 if (!(r_from = (t_relations *)ft_memalloc(sizeof(t_relations))))
		 exit(1);
	if (!(r_to = (t_relations *)ft_memalloc(sizeof(t_relations))))
		exit(1);
	if (!(n_from = node_search(*nodes, w_relation[R_FROM])))
		print_error();
	if (!(n_to = node_search(*nodes, w_relation[R_TO])))
		print_error();
	r_from->active = 1;
	r_from->relation_weight = 1;
	r_to->active = 1;
	r_to->relation_weight = 1;
	r_from->to = n_from;
	r_to->to = n_to;
	relations_back(n_from, r_to);
	relations_back(n_to, r_from);
	r_to->start = n_from->relations;
	r_from->start = n_to->relations;
}

void 			parse_line_relation(char *line, char **w_relation[])
{
	*w_relation = ft_strsplit(line, R_SEP);
	if (word_count(*w_relation) != R_SIZE)
		print_error();
}