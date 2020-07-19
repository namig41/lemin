#include "lemin.h"
#include <stdio.h>

void shortest_way(t_nodes *nodes)
{
	while (!nodes->is_finish) {
		nodes = nodes->next;
	}
	while (nodes) {
		ft_putstr(nodes->name);
		if (!nodes->prev)
			break;
		nodes = nodes->prev;
	}

	nodes = nodes->start;
}

// тут может утечка быть из-за копии ссылки на relations
t_nodes *add_out_node(t_nodes *node) {
	t_nodes *copy;

	copy = (t_nodes*)malloc(sizeof(t_nodes));
	copy->is_finish = 0;
	copy->start = node->start;
	copy->name = node->name;
	copy->next = NULL;
	copy->weight = 100000;
	copy->in = 0;
	copy->out = 1;

	// дизейблим связь на предыдущий элемент (вместо нее будет связь tmp с узла in)
	copy->relations = node->relations->start;
	while(copy->relations->to != node->prev)
		copy->relations = copy->relations->next;
	copy->relations->active = 0;
	copy->relations = node->relations->start;

	copy->need_delete = 1;
	copy->tmp = node;
	t_nodes *finish = node;
	while (finish->next)
		finish = finish->next;
	finish->next = copy;


	return copy;
}

void change_direction(t_nodes *nodes) {
	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;
	while(nodes->prev) {
		t_nodes *need_delete;
		need_delete = nodes;
		nodes = nodes->prev;
		nodes->relations = nodes->relations->start;
		while (nodes->relations->to != need_delete)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;
	}
	nodes = nodes->start;
}

void add_in_out(t_nodes *nodes) {
	nodes = nodes->start;
	while (!nodes->is_finish)
		nodes = nodes->next;

	t_nodes *prev;
	t_nodes *tmp_node; // out node
	while (!nodes->prev->is_start)
	{
		prev = nodes->prev; // like a D node
		prev->in = 1;		// теперь это in node
		while(nodes->relations->to != prev)
			nodes->relations = nodes->relations->next;
		nodes->relations->active = 0;
		nodes->relations = nodes->relations->start;

		tmp_node = add_out_node(prev);
		nodes->tmp = tmp_node;

		nodes = prev;
	}
	nodes->tmp = nodes->prev;
	nodes = nodes->start;
}

int main(int argc, char* argv[])
{
    t_nodes		*nodes = NULL;

    parse_file(argv[1], &nodes);

    printf("%d\n", g_ants);
    print_nodes(nodes);

	bellman_ford(nodes);
	shortest_way(nodes);

	change_direction(nodes);
	add_in_out(nodes);
	refresh(nodes);

	bellman_ford(nodes);
	shortest_way(nodes);
    return (0);
}
