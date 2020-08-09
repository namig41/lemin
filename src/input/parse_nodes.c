/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:44 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:17:46 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>



void			parse_section_node(char *line, t_nodes **nodes, t_title *title, t_uc *f)
{
	char 		**w_node;
	t_nodes 	*node;

	parse_line_node(line, &w_node);
	if (!(node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
		exit(1);
	node_init(node, w_node, title);
	ft_memdel((void **)&w_node[N_X]);
	ft_memdel((void **)&w_node[N_Y]);
	if (node_cmp(*nodes, node))
		print_error();
	if (*title == TITLE_START)
		nodes_front(nodes, node);
	else if (*title == TITLE_END)
		nodes_back(nodes, node);
	else
		nodes_insert(nodes, node, *f & F_START);
	node->start = (*nodes);
}

void 			parse_line_node(char *line, char **w_node[])
{
	*w_node = ft_strsplit(line, N_SEP);
	if (word_count(*w_node) != N_SIZE ||
		!ft_isnumber((*w_node)[N_X], ft_strlen((*w_node)[N_X]) ||
		!ft_isnumber((*w_node)[N_Y], ft_strlen((*w_node)[N_Y]))))
		print_error();
}

int		node_cmp(t_nodes *head, t_nodes *node)
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
