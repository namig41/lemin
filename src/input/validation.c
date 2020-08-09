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

char			**valid_line_node(char *line)
{
	char		**w_node;

	w_node = ft_strsplit(line, N_SEP);
	if (word_count(w_node) != N_SIZE ||
		!ft_isnumber(w_node[N_X], ft_strlen(w_node[N_X])) ||
		!ft_isnumber(w_node[N_Y], ft_strlen(w_node[N_Y])))
		return (NULL);
	return (w_node);
}

char			**valid_line_relation(char *line, t_nodes *nodes)
{
	char		**w_relation;

	w_relation = ft_strsplit(line, R_SEP);
	if (word_count(w_relation) != R_SIZE ||
		ft_strequ(w_relation[R_FROM], w_relation[R_TO]) ||
		!node_search(nodes, w_relation[R_FROM]) ||
		!node_search(nodes, w_relation[R_TO]))
		return (NULL);
	return (w_relation);
}

int				valid_start_end(t_nodes *nodes)
{
	if (!nodes->relations)
		return (1);
	while (nodes->next)
		nodes = nodes->next;
	if (!nodes->relations)
		return (1);
	return (0);
}

int				valid_node_cmp(t_nodes *head, t_nodes *node)
{
	while (head)
	{
		if (ft_strequ(head->name, node->name) ||
			(head->point.x == node->point.x &&
			head->point.y == node->point.y))
			return (1);
		head = head->next;
	}
	return (0);
}
