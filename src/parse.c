#include "lemin.h"
#include <fcntl.h>
#include <stdio.h>

t_uc g_f = 0;
t_title g_title;

void 	parse_file(char* file_name, t_nodes **nodes, t_relations **relations)
{
    int fd;
    char *line = NULL;

    fd = open(file_name, O_RDONLY);
    parse_number_ants(fd);
    while (get_next_line(fd, &line) > 0)
    {
        if (parse_title(line))
            ;
        else
            parse_switch(line, nodes, relations);
        ft_memdel((void **)&line);
    }
    if (!(g_f & (F_START | F_END)))
        print_error();
    close(fd);
}

void 	parse_number_ants(int fd)
{
    char *line;

    if (get_next_line(fd, &line) > 0)
    {
        if (parse_title(line))
            print_error();
        g_ants = ft_atoi(line);
        ft_memdel((void **)&line);
    }
    if (g_ants <= 0)
        print_error();
}

int		parse_title(char *line)
{
    if (ft_strequ(line, START))
        g_title = TITLE_START;
    else if (ft_strequ(line, END))
        g_title = TITLE_END;
    else if (*line == COMMENT)
    {
        if (g_title == TITLE_START || g_title == TITLE_END)
            print_error();
        g_title = NODE;
    }
    else if (ft_strchr(line, R_SEP))
    {
        g_title = RELATION;
        return (0);
    }
    else
        return (0);
    return (1);
}

void 	parse_switch(char *line, t_nodes **nodes, t_relations **relations)
{
    if (g_title == TITLE_START)
    {
        parse_section_node(line, nodes);
        g_title = NODE;
        g_f |= F_START;
    }
    else if (g_title == TITLE_END)
    {
        parse_section_node(line, nodes);
        g_title = NODE;
        g_f |= F_END;
    }
    else if (g_title == NODE)
    {
        parse_section_node(line, nodes);
    }
    else if (g_title == RELATION)
    {
       parse_section_relation(line, *nodes, relations);
    }
}

void 	parse_section_node(char *line, t_nodes **nodes)
{
    char *w_node[N_SIZE];
    t_nodes *node;

    parse_line_node(line, w_node);
    if (!(node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
        exit(1);
    node_init(node, g_title);
    if (*w_node[N_NAME] == 'L' || *w_node[N_NAME] == '#')
        print_error();
    node->name = w_node[N_NAME];
    node->point.x = ft_atoi(w_node[N_X]);
    node->point.y = ft_atoi(w_node[N_Y]);
    if (g_title == TITLE_START)
        nodes_front(nodes, node);
    else
        nodes_second(nodes, node);
    node->start = (*nodes);
}

void 	parse_line_node(char *line, char *w_node[])
{
    size_t i;
    size_t count;
    t_vector tmp;

    i = 0;
    count = 0;
    vector_init(&tmp, 1, sizeof(char));
    while (line[i] != '\0')
    {
        if (count >= N_SIZE || (count > 0 && !ft_isdigit(line[i]) && !ft_isescape(line[i])))
            print_error();
        if (ft_isescape(line[i]))
        {
            w_node[count] = ft_strdup((char *)tmp.data);
            vector_clear(&tmp);
            count++;
        }
        else
            vector_push_back_data(&tmp, (void *)(line + i));
        i++;
    }
    if (count < N_SIZE - 1)
    {
        printf("%d\n", __LINE__);
        print_error();
    }
    w_node[count] = ft_strdup((char *)tmp.data);
    vector_destroy(&tmp);
}

void 	parse_section_relation(char *line, t_nodes *nodes, t_relations **relations)
{
    char *w_relation[R_SIZE];
    t_relations *relation;

    parse_line_relation(line, w_relation);
    if (!(relation = (t_relations *)ft_memalloc(sizeof(t_relations))))
        exit(1);
    if (!(relation->to = node_search(nodes, w_relation[R_NODE_2])))
        print_error();
    relation->relation_weight = 0;
    relations_second(relations, relation);
    relation->start = (*relations);
}

void 			parse_line_relation(char *line, char *w_relation[])
{
    size_t i;
    size_t count;
    t_vector tmp;

    i = 0;
    count = 0;
    vector_init(&tmp, 1, sizeof(char));
    while (line[i] != '\0')
    {
        if (count >= R_SIZE || ft_isescape(line[i]))
            print_error();
        if (line[i] == R_SEP)
        {
            w_relation[count] = ft_strdup((char *)tmp.data);
            vector_clear(&tmp);
            count++;
        }
        else
            vector_push_back_data(&tmp, (void *)(line + i));
        i++;
    }
    if (count < R_SIZE - 1)
        print_error();
    w_relation[count] = ft_strdup((char *)tmp.data);
    vector_destroy(&tmp);
}
