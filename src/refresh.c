//
// Created by Fedya Savchuk on 18/07/2020.
//

#include "lemin.h"

void delete_nodes(t_nodes **nodes) {
	t_nodes *node;
	t_nodes *prev_node;

	node = (*nodes)->start;
	while(node) {
		if (node->need_delete)
		{
			prev_node->next = node->next;
			t_nodes *del = node;
			node = node->next;
			free(del);
			continue;
		}
		prev_node = node;
		node = node->next;
	}
}

void change_start(t_nodes *nodes, t_relations *start)
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

void delete_relations(t_nodes **nodes) {
	t_nodes *node;
	t_relations *prev_relations;
	t_relations *relations;

	node = (*nodes)->start;
	while(node) {
		relations = node->relations->start;
		prev_relations = NULL;
		while (relations) {
			if (relations->need_delete)
			{
				if (relations == relations->start)
					change_start(node, (node)->relations->next);

				if (prev_relations)
					prev_relations->next = relations->next;

				t_relations *need_del;
				need_del = relations;
				if (!relations->next)
					relations->next = NULL;
				relations = relations->next;
				free(need_del);
				continue;
			}
			prev_relations = relations;
			relations = relations->next;
		}
		node = node->next;
	}

}

void activate_links(t_nodes *nodes)
{
	t_nodes *node;
	t_relations *relations;

	node = nodes->start;
	while (node)
	{

		relations = node->relations->start;
		while (relations)
		{
			if (!relations->active)
				relations->active = 1;
			relations = relations->next;
		}
		node = node->next;
	}
}

void delete_tmp_links(t_nodes *nodes)
{
	t_nodes *node;

	node = nodes->start;
	while (node)
	{
		node->in = 0;
		node->out = 0;
		node->tmp = NULL;
		node = node->next;
	}
}

void clean_path(t_nodes *nodes)
{
	t_nodes *node;

	node = nodes;
	while (node)
	{
		node->prev = NULL;
		node->weight = 10000;
		if (node->is_start)
			node->weight = 0;
		node = node->next;
	}
}

// если пути пересикаются - делаем возвращаем граф в исходное состяние с удалением пересикающихся связей и временных ссылок/нодов
void refresh(t_nodes *nodes) {

	delete_nodes(&nodes);

	delete_relations(&nodes);

	delete_tmp_links(nodes);

	activate_links(nodes);

	clean_path(nodes);
}
