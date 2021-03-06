/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   choose_ways.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 13:18:29 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 13:18:31 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

static t_options	*search_optimal(t_options *options, t_paths *optimal)
{
	options = options->start;
	optimal = optimal->start;
	while (options->paths != optimal)
		options = options->next;
	return (options);
}

void				iter_way(t_options *options, int *substract, int *current)
{
	int paths;
	int ants;

	paths = 0;
	ants = g_ants;
	options->paths = options->paths->start;
	while (options->paths)
	{
		if (options->paths->nodes_count * paths - *substract <= ants)
			*current += 1;
		else
			break ;
		ants--;
		if (!options->paths->next)
			break ;
		options->paths = options->paths->next;
		paths++;
		*substract += options->paths->nodes_count;
	}
}

t_options			*choose_ways(t_options *options)
{
	int		current;
	int		substract;
	int		max;
	t_paths	*optimal;

	max = 0;
	options = options->start;
	optimal = options->start->paths;
	while (options)
	{
		substract = 0;
		current = 0;
		iter_way(options, &substract, &current);
		if (current > max)
		{
			max = current;
			optimal = options->paths;
		}
		options->paths = options->paths->start;
		if (!options->next)
			break ;
		options = options->next;
	}
	return (search_optimal(options, optimal));
}
