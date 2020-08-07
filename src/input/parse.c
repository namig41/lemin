#include "lemin.h"
#include <fcntl.h>
#include <stdio.h>

t_uc g_f = 0;

void 		parse_file(t_nodes **nodes)
{
    char 	*line;
    t_title	title;

    title = NODE;
    parse_number_ants();
    while (get_next_line(g_fd, &line) > 0)
    {
        //ft_putendl(line);
        if (parse_title(line, &title))
            ;
        else
            parse_switch(line, nodes, &title);
        ft_memdel((void **)&line);
    }
    if (!(g_f & (F_START | F_END)))
        print_error();
}

void 	parse_number_ants(void)
{
    char *line;

    if (get_next_line(g_fd, &line) > 0)
    {
        if (ft_isnumber(line, ft_strlen(line)))
        g_ants = ft_atoi(line);
        ft_memdel((void **)&line);
    }
    if (g_ants <= 0)
        print_error();
}

int		parse_title(char *line, t_title *title)
{
    if (ft_strequ(line, START))
        *title = TITLE_START;
    else if (ft_strequ(line, END))
        *title = TITLE_END;
    else if (*line == COMMENT)
    {
        if (*title == TITLE_START || *title == TITLE_END)
            print_error();
        *title = NODE;
    }
    else if (ft_strchr(line, R_SEP))
    {
        *title = RELATION;
        return (0);
    }
    else
        return (0);
    return (1);
}

void 			parse_switch(char *line, t_nodes **nodes, t_title *title)
{
    if (*title == TITLE_START)
    {
        parse_section_node(line, nodes, title);
        *title = NODE;
        g_f |= F_START;
    }
    else if (*title == TITLE_END)
    {
        parse_section_node(line, nodes, title);
        *title = NODE;
        g_f |= F_END;
    }
    else if (*title == NODE)
    {
        parse_section_node(line, nodes, title);
    }
    else if (*title == RELATION)
    {
       parse_section_relation(line, nodes);
    }
}

inline static int ft_isprints(char c)
{
    return ( c != ' ' && ft_isprint(c));
}

void 			parse_section_node(char *line, t_nodes **nodes, t_title *title)
{
    char 		*w_node[N_SIZE];
    t_nodes 	*node;

    parse_line_node(line, w_node);
    if (!(node = (t_nodes *)ft_memalloc(sizeof(t_nodes))))
        exit(1);
    node_init(node, w_node, title);
    if (*title == TITLE_START)
        nodes_front(nodes, node);
    else if (*title == TITLE_END)
        nodes_back(nodes, node);
    else
        nodes_insert(nodes, node, g_f & F_START);
    node->start = (*nodes);
}

void 			parse_line_node(char *line, char *w_node[])
{
    char 		prev_c;
    size_t		i;
    size_t 		count;
    t_vector	tmp;

    i = 0;
    count = 0;
    prev_c = line[0];
    tmp.data = NULL;
    vector_init(&tmp, 1, sizeof(char));
    while (line[i] != '\0')
    {
        if (ft_isprints(line[i]))
            vector_push_back_data(&tmp, (void *)(line + i));
        if ((ft_isprints(prev_c) && ft_isescape(line[i])) || (tmp.size > 0 && line[i + 1] == '\0'))
        {
            if (count > 0 && !ft_isnumber((const char *)tmp.data, tmp.size))
                print_error();
            w_node[count] = ft_strdup((char *)tmp.data);
            vector_clear(&tmp);
            count++;
        }
        prev_c = line[i];
        i++;
    }
    if (count != N_SIZE)
        print_error();
    vector_destroy(&tmp);
}

void 			parse_section_relation(char *line, t_nodes **nodes)
{
    char		*w_relation[R_SIZE];
    t_nodes 	*n_from;
    t_nodes 	*n_to;
    t_relations *r_from;
    t_relations *r_to;

    parse_line_relation(line, w_relation);
    exit(1);
    if (!(r_from = (t_relations *)ft_memalloc(sizeof(t_relations))))
        exit(1);
    if (!(r_to = (t_relations *)ft_memalloc(sizeof(t_relations))))
        exit(1);
    if (!(n_from = node_search(*nodes, w_relation[R_FROM])))
        print_error();
    if (!(n_to = node_search(*nodes, w_relation[R_TO])))
        print_error();
    r_from->active = 1;
    r_from->relation_weight = 1;
    r_to->active = 1;
    r_to->relation_weight = 1;
    r_from->to = n_from;
    r_to->to = n_to;
    relations_back(n_from, r_to);
    relations_back(n_to, r_from);
    r_to->start = n_from->relations;
    r_from->start = n_to->relations;
}

void 			parse_line_relation(char *line, char *w_relation[])
{
    t_uc		flag;
    size_t		i;
    size_t 		count;
    t_vector	tmp;

    i = 0;
    flag = 0;
    count = 0;
    tmp.data = NULL;
    vector_init(&tmp, 1, sizeof(char));
    while (line[i] != '\0')
    {

        if (ft_isprints(line[i]))
        {
            if (flag)
                print_error();
            vector_push_back_data(&tmp, (void *)(line + i));
        }
        if (tmp.size > 0 && ft_isescape(line[i]))
            flag = 1;
        if (line[i] == R_SEP || line[i + 1] == '\0')
        {
            w_relation[count] = ft_strdup(tmp.data);
            vector_clear(&tmp);
            flag = 0;
            count++;
        }
        i++;
    }
    if (count != R_SIZE)
        print_error();
    vector_destroy(&tmp);
}
