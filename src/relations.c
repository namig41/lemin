#include "lemin.h"

void 		relations_front(t_relations **list, t_relations *relation)
{
    if (!*list)
    {
        *list = relation;
        return ;
    }
    relation->next = *list;
    *list = relation;
}

void 		relations_second(t_relations **list, t_relations *relation)
{
    if (!*list)
    {
        *list = relation;
        return ;
    }
    relation->next = (*list)->next;
    (*list)->next = relation;
}

void 		relations_back(t_relations **list, t_relations *relation)
{
    t_relations *head;

    if (!*list)
    {
        *list = relation;
        return ;
    }
    head = *list;
    while (head->next)
        head = head->next;
    head->next = relation;
}
