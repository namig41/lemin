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

void	print_optimal_ways(t_paths *optimal)
{
	int i;

	ft_putendl("------------OPTIMAL--------------");
	while (optimal)
	{
		i = 0;
		while (optimal->path[i])
		{
			ft_putendl(optimal->path[i]->name);
			i++;
		}
		ft_putendl("");
		optimal = optimal->next;
	}
}

void		iter_way(t_options *options, int *substract, int *current)
{
	int paths;
	int ants;

	paths = 1;
	ants = g_ants;
	options->paths = options->paths->start;
	while (options->paths)
	{
		if (options->paths->nodes_count * paths - *substract <= ants)
			current++;
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

t_options	*choose_ways(t_options *options)
{
	int		current;
	int		substract;
	t_paths	*optimal;
	int		max;

	options = options->start;
	max = 0;
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

	options = options->start;
	optimal = optimal->start;
	while (options->paths != optimal)
		options = options->next;
	print_optimal_ways(optimal);
	return (options);
}
