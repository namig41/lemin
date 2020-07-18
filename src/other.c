#include "lemin.h"
#include <stdio.h>


void 		print_nodes(t_nodes *head)
{
    t_relations *r;

    while (head)
    {
        printf("name: %s\tis_start: %d\tis_finish: %d\tx=%d y=%d\tfirst_node: %s\n", head->name, head->is_start, head->is_finish, head->point.x, head->point.y, head->start->name);
        r = head->relations;
        while (r)
        {
            printf("to_name: %s\tfirst_node: %s\n", r->to->name, r->start->to->name);
            r = r->next;
        }
        head = head->next;
    }
}
