
#include "lemin.h"

void	free_paths(t_options **options)
{
	t_paths		*delete_paths;
	t_options	*delete_options;

	*options = (*options)->start;
	while ((*options))
	{
		(*options)->paths = (*options)->paths->start;
		while ((*options)->paths)
		{
			free((*options)->paths->path);
			delete_paths = (*options)->paths;
			free(delete_paths);
			(*options)->paths = (*options)->paths->next;
		}
		delete_options = *options;
		*options = (*options)->next;
		free(delete_options);
	}
}

void	free_nodes(t_nodes **nodes)
{
	t_nodes		*delete_node;
	t_relations	*delete_relation;

	*nodes = (*nodes)->start;
	while (*nodes)
	{
		(*nodes)->relations = (*nodes)->relations->start;
		while ((*nodes)->relations)
		{
			delete_relation = (*nodes)->relations;
			(*nodes)->relations = (*nodes)->relations->next;
			free(delete_relation);
		}
		delete_node = *nodes;
		*nodes = (*nodes)->next;
		free(delete_node);
	}
}

void	clean_memory(t_options **options, t_nodes **nodes)
{
	free_paths(options);
	free_nodes(nodes);
}
