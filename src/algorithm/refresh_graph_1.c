/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refresh_graph_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:18:00 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:18:02 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	delete_nodes(t_nodes **nodes)
{
	t_nodes	*node;
	t_nodes *del;
	t_nodes	*prev_node;

	node = (*nodes)->start;
	while (node)
	{
		if (node->need_delete)
		{
			prev_node->next = node->next;
			del = node;
			node = node->next;
			free(del);
			continue ;
		}
		prev_node = node;
		node = node->next;
	}
}

void	del_and_activate_links(t_nodes *nodes)
{
	t_nodes		*node;
	t_relations	*relations;

	node = nodes->start;
	while (node)
	{
		node->in = 0;
		node->out = 0;
		node->tmp = NULL;
		relations = node->relations->start;
		while (relations)
		{
			if (!relations->active)
				relations->active = 1;
			relations = relations->next;
		}
		node = node->next;
	}
}

void	clean_path(t_nodes *nodes)
{
	t_nodes *node;

	node = nodes;
	while (node)
	{
		node->prev = NULL;
		node->weight = 10000;
		if (node->is_start)
			node->weight = 0;
		node = node->next;
	}
}

void	refresh(t_nodes *nodes)
{
	delete_nodes(&nodes);
	delete_relations(&nodes);
	del_and_activate_links(nodes);
	clean_path(nodes);
}
