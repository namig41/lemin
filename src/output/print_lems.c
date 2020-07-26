
#include "lemin.h"

void	print(int lem_num, char *name)
{
	ft_putstr("L");
	ft_putnbr(lem_num);
	ft_putstr("-");
	ft_putstr(name);
	ft_putstr(" ");
}

void	print_shortest_way(t_nodes *nodes)
{
	while (!nodes->is_finish)
		nodes = nodes->next;
	while (nodes)
	{
		ft_putstr(nodes->name);
		if (nodes->out)
			ft_putstr("(OUT)");
		if (nodes->in)
			ft_putstr("(IN)");
		ft_putendl("");
		if (!nodes->prev)
			break ;
		nodes = nodes->prev;
	}
	nodes = nodes->start;
}

int		search_steps(t_paths *ways, int paths, int substract, int *i)
{
	int j;
	int is_empty;

	j = 0;
	is_empty = 1;
	while (++j <= ways->nodes_count)
	{
		if (ways->path[j]->lem_num > 0 && j < ways->nodes_count)
		{
			ways->path[j - 1]->lem_num = ways->path[j]->lem_num;
			print(ways->path[j - 1]->lem_num, ways->path[j - 1]->name);
			is_empty = 0;
			ways->path[j]->lem_num = 0;
		}
		else if (j == ways->nodes_count &&
		ways->nodes_count * paths - substract <= g_ants - *i && *i <= g_ants)
		{
			ways->path[j - 1]->lem_num = *i;
			print(ways->path[j - 1]->lem_num, ways->path[j - 1]->name);
			is_empty = 0;
			*i = *i + 1;
		}
	}
	return (is_empty);
}

void	print_lems(t_paths *ways)
{
	int i;
	int paths;
	int is_empty;
	int substract;

	i = 1;
	is_empty = 0;
	while (!is_empty)
	{
		paths = 1;
		ways = ways->start;
		is_empty = 1;
		substract = ways->nodes_count;
		while (ways)
		{
			if (search_steps(ways, paths, substract, &i) == 0)
				is_empty = 0;
			paths++;
			substract += ways->nodes_count;
			if (!ways->next)
				break ;
			ways = ways->next;
		}
		ft_putendl("");
	}
}
