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


