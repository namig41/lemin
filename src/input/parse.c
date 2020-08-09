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
    t_uc        f;
	char		*line;
	t_title		title;

    f = 0;
	title = NODE;
	parse_ants();
	while (get_next_line(g_fd, &line) > 0)
	{
		f &= ~F_COMMENT;
		if (parse_title(line, *nodes, &title, &f))
		{
			if (f & F_DD)
				print_error();
			f |= F_DD;
		}
		else
		{
			parse_switch(line, nodes, &title, &f);
			f &= ~F_DD;
		}
		ft_memdel((void **)&line);
	}
	if (!(f & F_START) || !(f & F_END) || !(f & F_REL) || (f & F_COMMENT))
		print_error();
	if (valid_start_end(*nodes))
		print_error();
}

void			parse_ants(void)
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

int				parse_title(char *line, t_nodes *nodes, t_title *title, t_uc *f)
{
	if (ft_strequ(line, START))
		*title = TITLE_START;
	else if (ft_strequ(line, END))
		*title = TITLE_END;
	else if (*line == COMMENT)
	{
		if (line[1] == COMMENT || valid_line_node(line + 1) ||
								valid_line_relation(line + 1, nodes))
			print_error();
		*f |= F_COMMENT;
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
		if (*f & F_START)
			print_error();
		parse_section_node(line, nodes, title, f);
		*title = NODE;
		*f |= F_START;
	}
	else if (*title == TITLE_END)
	{
		if (*f & F_END)
			print_error();
		parse_section_node(line, nodes, title, f);
		*title = NODE;
		*f |= F_END;
	}
	else if (*title == NODE)
		parse_section_node(line, nodes, title, f);
	else if (*title == RELATION)
	{
		parse_section_relation(line, nodes);
		*f |= F_REL;
	}
}
