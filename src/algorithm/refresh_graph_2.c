
#include "lemin.h"

void	change_start(t_nodes *nodes, t_relations *start)
{
	t_relations *relations;

	relations = nodes->relations;
	while (relations)
	{
		relations->start = start;
		relations = relations->next;
	}
	nodes->relations = start;
}

void	delete_relations_1(t_relations *relations,
		t_nodes *node, t_relations *prev_relations)
{
	if (relations == relations->start)
		change_start(node, (node)->relations->next);
	if (prev_relations)
		prev_relations->next = relations->next;
}

void	delete_relations(t_nodes **nodes)
{
	t_nodes		*node;
	t_relations	*need_del;
	t_relations	*prev_relations;
	t_relations	*relations;

	node = (*nodes)->start;
	while (node)
	{
		relations = node->relations->start;
		prev_relations = NULL;
		while (relations)
		{
			if (relations->need_delete)
			{
				delete_relations_1(relations, node, prev_relations);
				need_del = relations;
				relations = relations->next;
				free(need_del);
				continue ;
			}
			prev_relations = relations;
			relations = relations->next;
		}
		node = node->next;
	}
}
