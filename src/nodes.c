#include "lemin.h"

void 		nodes_front(t_nodes **list, t_nodes *node)
{
	if (!*list)
	{
		*list = node;
		return ;
	}
    node->next = *list;
    *list = node;
}

void 		nodes_insert(t_nodes **list, t_nodes *node, size_t num)
{
    size_t i;
    t_nodes *head;

    i = 0;
    if (!*list || !num)
    {
        *list = node;
        return ;
    }
    head = *list;
    while (i < num - 1)
    {
        head = head->next;
        i++;
    }
    node->next = head->next;
    head->next = node;
}

void 		nodes_second(t_nodes **list, t_nodes *node)
{
    if (!*list)
    {
        *list = node;
        return ;
    }
    node->next = (*list)->next;
    (*list)->next = node;
}

void 		nodes_back(t_nodes **list, t_nodes *node)
{
	t_nodes *head;

	if (!*list)
	{
		*list = node;
		return ;
	}
	head = *list;
	while (head->next)
		head = head->next;
	head->next = node;
}

void 	node_init(t_nodes *node, char *w_node[], t_title name)
{
    if (*w_node[N_NAME] == 'L' || *w_node[N_NAME] == '#')
        print_error();
    node->name = w_node[N_NAME];
    node->point.x = ft_atoi(w_node[N_X]);
    node->point.y = ft_atoi(w_node[N_Y]);
    if (name == TITLE_START)
    {
        node->is_start = 1;
        node->weight = 0;
    }
    else if (name == TITLE_END)
    {
       node->is_finish = 1;
       node->weight = INT_MAX;
    }
    else if (name == NODE)
    {
       node->weight = INT_MAX;
    }
}

t_nodes 	*node_search(t_nodes *head, char *name)
{
    while (head)
    {
        if (ft_strequ(head->name, name))
            return (head);
        head = head->next;
    }
    return (NULL);
}
