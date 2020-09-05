/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:44 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/09/05 18:13:04 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			parse_section_node(char *line, t_nodes **nodes,
									t_title *title, t_uc *f)
{
	char		**w_node;
	t_nodes		*node;

	if (!(w_node = valid_line_node(line)))
		print_error(nodes);
	if (!(node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
		print_error(nodes);
	node_init(nodes, node, w_node, title);
	array_clear(w_node);
	if (valid_node_cmp(*nodes, node))
	{
		ft_memdel((void **)&node->name);
		ft_memdel((void **)&node);
		print_error(nodes);
	}
	if (*title == START)
		nodes_front(nodes, node);
	else if (*title == END)
		nodes_back(nodes, node);
	else
		nodes_insert(nodes, node, *f & F_START);
}
