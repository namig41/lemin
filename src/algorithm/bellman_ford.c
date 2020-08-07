/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bellman_ford.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:54 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:17:55 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		get_len(t_nodes *node)
{
	int		len;
	t_nodes	*tmp;

	len = 0;
	tmp = node->start;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

void	compare_relations_cost(t_relations *relations, t_nodes *node)
{
	while (relations)
	{
		if (relations->active && relations->to->weight
		> node->weight + relations->relation_weight)
		{
			relations->to->weight = node->weight + relations->relation_weight;
			relations->to->prev = node;
		}
		relations = relations->next;
	}
}

void	compare_tmp_links_cost(t_nodes *node)
{
	if (node->tmp->weight > node->weight - 1)
	{
		node->tmp->weight = node->weight - 1;
		node->tmp->prev = node;
	}
}

void	search_min_wights(t_nodes *node)
{
	t_relations	*relations;

	while (1)
	{
		relations = node->relations->start;
		if (node->weight >= 1000 || !relations)
		{
			if (!node->next)
				break ;
		}
		else if (node->in)
			compare_tmp_links_cost(node);
		else
			compare_relations_cost(relations, node);
		if (!node->next)
			break ;
		node = node->next;
	}
}

void	bellman_ford(t_nodes *nodes)
{
	int	i;
	int	v_count;

	i = 0;
	v_count = get_len(nodes);
	while (i < v_count - 1)
	{
		nodes = nodes->start;
		search_min_wights(nodes);
		i++;
	}
}
