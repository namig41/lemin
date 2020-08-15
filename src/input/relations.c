/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   relations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:48 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:17:49 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			relations_back(t_nodes **nodes, t_nodes *node,
								t_relations *relation)
{
	t_relations *relations;
	t_relations *head;

	relations = node->relations;
	if (!relations)
	{
		node->relations = relation;
		return ;
	}
	head = relations;
	while (head->next)
	{
		if (ft_strequ(head->to->name, relation->to->name))
			print_error(nodes);
		head = head->next;
	}
	head->next = relation;
}
