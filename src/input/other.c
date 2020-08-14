/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:17:40 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:17:41 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"
#include <stdio.h>

void			print_nodes(t_nodes *head)
{
	t_relations *r;

	while (head)
	{
		printf("\nNode: %s%s%s\nRelations: ", head->name, (head->out) ? "(OUT)" : "", (head->in) ? "(IN)" : "");
		r = head->relations;
		if (head->tmp != NULL)
		{
			printf("%s", head->tmp->name);
			if (head->tmp->in)
				printf("(IN)-");
			if (head->tmp->out)
				printf("(OUT)-");
		}
		while (r)
		{
			if (r->active)
				printf("%s%s%s%c", r->to->name,
					(r->to->out) ? "(OUT)" : "", (r->to->in) ? "(IN)" : "",
					(r->next && r->next->active) ? '-' : '\n');
			r = r->next;
		}
		head = head->next;
	}
}

