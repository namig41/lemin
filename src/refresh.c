//
// Created by Fedya Savchuk on 18/07/2020.
//

#include "lemin.h"

void delete_nodes(t_nodes *nodes) {
	t_nodes *node;
	t_nodes *prev_node;

	node = nodes->start;
	while(node) {
		if (node->need_delete)
		{
			if (prev_node)
				prev_node->next = node->next;
			free(node);
		}
		prev_node = node;
		node = node->next;
	}
}

void delete_relations(t_nodes *nodes) {
	t_nodes *node;
	t_relations *prev_relations;
	t_relations *relations;

	node = nodes->start;
	while(node) {
		relations = node->relations->start;
		prev_relations = NULL;
		while (relations) {
			if (!relations->active)
				relations->active = 1;
			if (relations->need_delete)
			{
				if (prev_relations)
					prev_relations->next = relations->next;
				free(relations);
			}

			prev_relations = relations;
			relations = relations->next;
		}
		node = node->next;
	}
}

void active_links() {

}

// если пути пересикаются - делаем возвращаем граф в исходное состяние с удалением пересикающихся связей и временных ссылок/нодов
void refresh(t_nodes *nodes) {
	while (nodes) {
		nodes->prev = NULL;
		if (!nodes->is_start)
			nodes->weight = 10000;
		else
			nodes->weight = 0;
		nodes = nodes->next;
	}
}
