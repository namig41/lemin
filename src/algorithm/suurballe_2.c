/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suurballe_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:18:10 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:18:12 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_nodes	*add_out_node(t_nodes *node)
{
	t_nodes *copy;
	t_nodes *finish;

	copy = (t_nodes*)ft_memalloc(sizeof(t_nodes));
	copy->is_finish = 0;
	copy->start = node->start;
	copy->name = node->name;
	copy->next = NULL;
	copy->weight = 100000;
	copy->in = 0;
	copy->out = 1;
	copy->lem_num = 0;
	copy->relations = node->relations->start;
	while (copy->relations->to != node->prev)
		copy->relations = copy->relations->next;
	copy->relations->active = 0;
	copy->relations = node->relations->start;
	copy->need_delete = 1;
	copy->tmp = node;
	finish = node;
	while (finish->next)
		finish = finish->next;
	finish->next = copy;
	return (copy);
}

void	change_direction(t_nodes *nodes)
{
	t_nodes *need_delete;

	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;
	while (nodes->prev)
	{
		need_delete = nodes;
		nodes = nodes->prev;
		nodes->relations = nodes->relations->start;
		while (nodes->relations->to != need_delete)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;
	}
	nodes = nodes->start;
}

void	add_in_out(t_nodes *nodes)
{
	t_nodes *prev;
	t_nodes *tmp_node;

	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;
	while (!nodes->prev->is_start)
	{
		prev = nodes->prev;
		prev->in = 1;
		while (nodes->relations->to != prev)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;
		tmp_node = add_out_node(prev);
		nodes->tmp = tmp_node;
		nodes = prev;
	}
	nodes->tmp = nodes->prev;
	nodes = nodes->start;
}

void	mark_delete(t_nodes *first, t_nodes *second)
{
	while (first->relations->next && first->relations->to != second)
		first->relations = first->relations->next;
	first->relations->need_delete = 1;
	first->relations = first->relations->start;
}

int		is_cross(t_nodes *nodes)
{
	int		cross;
	t_nodes	*node;
	t_nodes	*first;
	t_nodes	*second;

	cross = 0;
	node = nodes->start;
	while (!node->is_finish)
		node = node->next;
	while (node)
	{
		if (node->out)
		{
			first = node->tmp;
			second = node->prev;
			if (first)
				mark_delete(first, second);
			if (second)
				mark_delete(second, first);
			cross = 1;
		}
		node = node->prev;
	}
	return (cross);
}
