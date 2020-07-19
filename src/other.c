#include "lemin.h"
#include <stdio.h>


void 		print_nodes(t_nodes *head)
{
    t_relations *r;

    while (head)
    {
        printf("%s %d %d\n", head->name, head->point.x, head->point.y);
        r = head->relations;
        while (r)
        {
            printf("%s%c", r->to->name, (r->next) ? '-' : '\n');
            r = r->next;
        }
        head = head->next;
    }
}
