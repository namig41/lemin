#include "lemin.h"
#include <stdio.h>

void shortest_way(t_nodes *nodes)
{
	while (!nodes->is_finish)
		nodes = nodes->next;
	while (nodes) {

		ft_putstr(nodes->name);
		if (nodes->out)
			ft_putstr("(OUT)");
		if (nodes->in)
			ft_putstr("(IN)");
		ft_putendl("");
		if (!nodes->prev)
			break;
		nodes = nodes->prev;
	}

	nodes = nodes->start;
}

// тут может утечка быть из-за копии ссылки на relations
t_nodes *add_out_node(t_nodes *node) {
	t_nodes *copy;

	copy = (t_nodes*)ft_memalloc(sizeof(t_nodes));
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

int is_cross(t_nodes *nodes) {
	t_nodes *node;
	int cross = 0;


	node = nodes->start;
	while (!node->is_finish)
		node = node->next;
	while (node) {

		if (node->out)
		{
			t_nodes *first = node->tmp;
			t_nodes *second = node->prev;

			if (first)
			{
				while (first->relations->next && first->relations->to != second)
					first->relations = first->relations->next;

				first->relations->need_delete = 1;
				first->relations = first->relations->start;
			}


			if (second)
			{
				while (second->relations->next && second->relations->to != first)
					second->relations = second->relations->next;
				second->relations->need_delete = 1;
				second->relations = second->relations->start;
			}

			cross = 1;
		}

		node = node->prev;
	}
	ft_putstr("HEEY");
	return cross;
}

void complete_path(t_options *option, t_nodes *nodes)
{
	t_nodes *node;

	node = nodes->start;
	while (!node->is_finish)
		node = node->next;

	int len = 0;
	while (node) {
		len++;
		node = node->prev;
	}

	option->paths->path = (t_nodes**)malloc(sizeof(t_nodes*) * len + 1);
	node = nodes->start;
	while (!node->is_finish)
		node = node->next;

	ft_putstr("\nPAAATH:    \n");
	int i = 0;
	while (i < len) {
		//ft_putendl(node->name);
		option->paths->path[i] = node;
		option->paths->nodes_count = len - 1; // TODO -start ?
		node = node->prev;
		i++;
	}
	option->paths->path[i] = NULL;
}

void add_path(t_paths **paths)
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

void add_option(t_options **options)
{
	t_options *option;
	t_paths *paths;
	t_options *start;

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

void clean_option(t_options *option)
{
	t_options *prev;

	option = option->start;
	while (option)
	{
		if (!option->next)
			break;
		prev = option;
		option = option->next;
	}

	while (option->paths)
	{
		int i = 0;
		while (option->paths->path[i])
		{
			free(option->paths->path[i]);
			i++;
		}
		free(option->paths->path);
		t_paths *need_del;
		need_del = option->paths;
		option->paths = option->paths->next;
		free(need_del);
	}
}

t_options *choose_option(t_options *options) {

	options = options->start;
	int current = 0;
	int max = 0;
	ft_putstr("HELLfO");
	t_paths *optimal = options->start->paths;
	ft_putstr("HELLfO");
	while (options) {
		int substract = 0;
		current = 0;
		int paths = 1;
		int ants = g_ants;
		options->paths = options->paths->start;
		while (options->paths)
		{
			if (options->paths->nodes_count * paths - substract <= ants)
				current++;
			else
				break;
			ants--;
			if (!options->paths->next)
				break;
			options->paths = options->paths->next;
			paths++;
			substract += options->paths->nodes_count;
		}
		if (current > max)
		{
			max = current;
			optimal = options->paths;
		}

		options->paths = options->paths->start;
		if (!options->next)
			break;
		options = options->next;
	}
	options = options->start;

	optimal = optimal->start;
	ft_putendl("------------OPTIMAL--------------");
	while (optimal)
	{
		int i = 0;
		while (optimal->path[i])
		{
			ft_putendl(optimal->path[i]->name);
			i++;
		}
		ft_putendl("");
		optimal = optimal->next;
	}
	return optimal;
}
//
//void calculate_path_len() {
//
//}


int main(int argc, char* argv[])
{
    t_nodes		*nodes = NULL;
    t_options 	*options;

    options = NULL;
    add_option(&options);

    parse_file(argv[1], &nodes);

    printf("%d\n", g_ants);
    //print_nodes(nodes);

    t_nodes *finish_node;
    finish_node = nodes->start;
    while (!finish_node->is_finish)
		finish_node = finish_node->next;


    while(1)
	{
		ft_putstr("\nITER");

		bellman_ford(nodes);

		//ft_putstr("\nPAAATH:    \n");
		shortest_way(nodes);


		if (finish_node->weight >= 1000)
			break;

		if (is_cross(nodes)) {
			add_option(&options);
			refresh(nodes);
			continue;
		}

		if (options->paths->nodes_count < 999)
			add_path(&options->paths);
		complete_path(options, nodes);
		ft_putstr("\n");

		change_direction(nodes);

		//print_nodes(nodes);
		ft_putstr("------------------");
		add_in_out(nodes);
		//print_nodes(nodes);
		//ft_putstr("------------------");
		clean_path(nodes);
		ft_putendl("");
		//print_nodes(nodes);
	}
	refresh(nodes);

	choose_option(options);

    // free functions
    // free array
    options = options->start;
    while (options)
	{
    	options->paths = options->paths->start;
    	while (options->paths)
		{
//			int i = 0;
//			while (options->paths->path[i])
//			{
//				free(options->paths->path[i]);
//				i++;
//			}
			free(options->paths->path);
    		if (!options->paths->next)
    			break;
    		options->paths = options->paths->next;
		}
		options->paths = options->paths->start;
    	if (!options->next)
    		break;
		options = options->next;
	}

    // free paths
    options = options->start;
    while (options)
	{
		options->paths = options->paths->start;
		while (options->paths)
		{
			t_paths *need_delete;
			need_delete = options->paths;
			free(need_delete);
			options->paths = options->paths->next;
		}
		if (!options->next)
			break;
		options = options->next;
	}

    //free options
    options = options->start;
    while (options)
	{
    	t_options *need_delete;
    	need_delete = options;
    	options = options->next;
    	free(need_delete);
	}

    // free relations
    nodes = nodes->start;
    while (nodes)
	{
    	nodes->relations = nodes->relations->start;
    	while (nodes->relations)
		{
    		t_relations *need_delete;
    		need_delete = nodes->relations;
    		nodes->relations = nodes->relations->next;
    		free(need_delete);
		}
    	if (!nodes->next)
    		break;
    	nodes = nodes->next;
	}

    // free nodes
	nodes = nodes->start;
	while (nodes)
	{
		t_nodes *need_delete;
		need_delete = nodes;
		nodes = nodes->next;

		free(need_delete);
	}


    return (0);
}
