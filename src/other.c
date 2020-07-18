#include "lemin.h"
#include <stdio.h>

void 	node_init(t_nodes *node, t_title name)
{
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

void 		print_nodes(t_nodes *head)
{
    while (head)
    {
        printf("name: %s\tis_start: %d\tis_finish: %d\tx=%d y=%d\tfirst_node: %s\n", head->name, head->is_start, head->is_finish, head->point.x, head->point.y, head->start->name);
        head = head->next;
    }
}

void 		print_relations(t_relations *head)
{
    while (head)
    {
        printf("to_name: %s\tfirst_node: %s\n", head->to->name, head->start->to->name);
        head = head->next;
    }
}
