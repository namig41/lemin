#include "lemin.h"

void 		relations_front(t_nodes *nodes, t_relations *relation)
{
    t_relations *relations;

    relations = nodes->relations;
    if (!relations)
    {
        nodes->relations = relation;
        return ;
    }
    relation->next = relations;
    relations = relation;
}

void 		relations_second(t_nodes *nodes, t_relations *relation)
{
    t_relations *relations;

    relations = nodes->relations;
    if (!relations)
    {
        nodes->relations = relation;
        return ;
    }
    relation->next = relations->next;
    relations->next = relation;
}

void 		relations_back(t_nodes *nodes, t_relations *relation)
{
    t_relations *relations;
    t_relations *head;

    relations = nodes->relations;
    if (!relations)
    {
        nodes->relations = relation;
        return ;
    }
    head = relations;
    while (head->next)
    {
        if (ft_strequ(head->to->name, relation->to->name))
            print_error(__LINE__);
        head = head->next;
    }
    head->next = relation;
}
