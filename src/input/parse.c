/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:24:05 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/08/07 14:24:05 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			parse_file(t_nodes **nodes)
{
	char		*line;
	t_title		title;
    t_uc        f;

    f = 0;
	title = NODE;
	parse_number_ants();
	while (get_next_line(g_fd, &line) > 0)
	{
		ft_putendl(line);
		if (parse_title(line, &title))
			;
		else
			parse_switch(line, nodes, &title, &f);
		ft_memdel((void **)&line);
	}
	if (!(f & (F_START | F_END)))
		print_error();
}

void			parse_number_ants(void)
{
	char		*line;

	if (get_next_line(g_fd, &line) > 0)
	{
		if (ft_isnumber(line, ft_strlen(line)))
		g_ants = ft_atoi(line);
		ft_memdel((void **)&line);
	}
	if (g_ants <= 0)
		print_error();
}

int				parse_title(char *line, t_title *title)
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

void			parse_switch(char *line, t_nodes **nodes, t_title *title, t_uc *f)
{
	if (*title == TITLE_START)
	{
		parse_section_node(line, nodes, title, f);
		*title = NODE;
		*f |= F_START;
	}
	else if (*title == TITLE_END)
	{
		parse_section_node(line, nodes, title, f);
		*title = NODE;
		*f |= F_END;
	}
	else if (*title == NODE)
		parse_section_node(line, nodes, title, f);
	else if (*title == RELATION)
	   parse_section_relation(line, nodes);
}
