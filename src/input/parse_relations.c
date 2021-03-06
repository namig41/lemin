/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_relations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:19:58 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/30 13:15:44 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

inline static void	init_relations(t_relations *r_from, t_relations *r_to,
										t_nodes *n_from, t_nodes *n_to)
{
	r_from->active = 1;
	r_from->relation_weight = 1;
	r_to->active = 1;
	r_to->relation_weight = 1;
	r_from->to = n_from;
	r_to->to = n_to;
}

static void			tmp_clean_memory(t_relations *r_from, t_relations *r_to,
									char **w_relation, t_nodes **nodes)
{
	ft_memdel((void **)&r_from);
	ft_memdel((void **)&r_to);
	array_clear(w_relation);
	print_error(nodes);
}

void				parse_section_relation(char *line, t_nodes **nodes)
{
	char		**w_relation;
	t_nodes		*n_from;
	t_nodes		*n_to;
	t_relations *r_from;
	t_relations *r_to;

	r_from = (t_relations *)ft_memalloc(sizeof(t_relations));
	r_to = (t_relations *)ft_memalloc(sizeof(t_relations));
	if (!(w_relation = valid_line_relation(line, *nodes)))
		print_error(nodes);
	if (!(n_from = node_search(*nodes, w_relation[R_FROM])))
		tmp_clean_memory(r_from, r_to, w_relation, nodes);
	if (!(n_to = node_search(*nodes, w_relation[R_TO])))
		tmp_clean_memory(r_from, r_to, w_relation, nodes);
	init_relations(r_from, r_to, n_from, n_to);
	relations_back(nodes, n_from, r_to);
	relations_back(nodes, n_to, r_from);
	r_to->start = n_from->relations;
	r_from->start = n_to->relations;
	array_clear(w_relation);
}
