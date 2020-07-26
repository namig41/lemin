
#include "lemin.h"

void	complete_path(t_options *option, t_nodes *nodes)
{
	int		i;
	int		len;
	t_nodes	*node;

	node = nodes->start;
	while (!node->is_finish)
		node = node->next;
	len = 0;
	while (node)
	{
		len++;
		node = node->prev;
	}
	option->paths->path = (t_nodes**)malloc(sizeof(t_nodes*) * len + 1);
	node = nodes->start;
	while (!node->is_finish)
		node = node->next;
	i = -1;
	while (++i < len)
	{
		option->paths->path[i] = node;
		option->paths->nodes_count = len - 1;
		node = node->prev;
	}
	option->paths->path[i] = NULL;
}

void	add_path(t_paths **paths)
{
	t_paths *path;
	t_paths *start;

	path = (t_paths*)malloc(sizeof(t_paths));
	path->next = NULL;
	if (*paths)
	{
		(*paths)->next = path;
		start = (*paths)->start;
	}
	else
		start = path;
	path->start = start;
	path->nodes_count = 999;
	*paths = path;
}

void	add_option(t_options **options)
{
	t_options	*option;
	t_paths		*paths;
	t_options	*start;

	paths = NULL;
	option = (t_options*)malloc(sizeof(t_options));
	add_path(&paths);
	option->paths = paths;
	if (*options)
	{
		(*options)->next = option;
		start = (*options)->start;
	}
	else
		start = option;
	option->start = start;
	option->next = NULL;
	*options = option;
}

void	clean_option(t_options *option)
{
	int			i;
	t_options	*prev;
	t_paths		*need_del;

	option = option->start;
	while (option)
	{
		if (!option->next)
			break ;
		prev = option;
		option = option->next;
	}
	while (option->paths)
	{
		i = -1;
		while (option->paths->path[++i])
			free(option->paths->path[i]);
		free(option->paths->path);
		need_del = option->paths;
		option->paths = option->paths->next;
		free(need_del);
	}
}

void	suurballe(t_nodes *nodes, t_options *options)
{
	t_nodes		*finish_node;

	finish_node = nodes->start;
	while (!finish_node->is_finish)
		finish_node = finish_node->next;
	while (1)
	{
		bellman_ford(nodes);
		if (finish_node->weight >= 1000)
			break ;
		if (is_cross(nodes))
		{
			add_option(&options);
			refresh(nodes);
			continue ;
		}
		if (options->paths->nodes_count < 999)
			add_path(&options->paths);
		complete_path(options, nodes);
		change_direction(nodes);
		add_in_out(nodes);
		clean_path(nodes);
	}
	refresh(nodes);
}
