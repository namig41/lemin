/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:33 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:17:34 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void		nodes_front(t_nodes **list, t_nodes *node)
{
	node->next = *list;
	*list = node;
}

void		nodes_insert(t_nodes **list, t_nodes *node, size_t num)
{
	size_t	i;
	t_nodes	*head;

	i = 0;
	if (!*list || !num)
	{
		nodes_front(list, node);
		return ;
	}
	head = *list;
	while (i < num - 1)
	{
		head = head->next;
		i++;
	}
	node->next = head->next;
	head->next = node;
}

void		nodes_back(t_nodes **list, t_nodes *node)
{
	t_nodes	*head;

	if (!*list)
	{
		*list = node;
		return ;
	}
	head = *list;
	while (head->next)
		head = head->next;
	head->next = node;
}

void		node_init(t_nodes **nodes, t_nodes *node, char *w_node[], t_title *title)
{
	if (*w_node[N_NAME] == 'L' || *w_node[N_NAME] == '#')
	{
		ft_memdel((void **)&node);
		array_clear(w_node);
		print_error(nodes);
	}
	node->name = ft_strdup(w_node[N_NAME]);
	node->point.x = ft_atoi(w_node[N_X]);
	node->point.y = ft_atoi(w_node[N_Y]);
	if (*title == TITLE_START)
	{
		node->is_start = 1;
		node->weight = 0;
	}
	else if (*title == TITLE_END)
	{
		node->is_finish = 1;
		node->weight = INT_MAX;
	}
	else if (*title == NODE)
	{
		node->weight = INT_MAX;
	}
}

t_nodes		*node_search(t_nodes *head, char *name)
{
	while (head)
	{
		if (ft_strequ(head->name, name))
			return (head);
		head = head->next;
	}
	return (NULL);
}
