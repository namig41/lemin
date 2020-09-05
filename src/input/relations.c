/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:48 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/09/05 18:23:03 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			relations_back(t_nodes **nodes, t_nodes *node,
								t_relations *relation)
{
	t_relations *head;

	if (!node->relations)
	{
		node->relations = relation;
		return ;
	}
	head = node->relations;
	while (head)
	{
		if (ft_strequ(head->to->name, relation->to->name))
			print_error(nodes);
		if (!head->next)
		{
			head->next = relation;
			return ;
		}
		head = head->next;
	}
}
