/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 14:24:05 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/09/05 18:28:38 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void			parse_file(t_nodes **nodes)
{
	char		*line;
	t_title		title;
	t_uc		f;

	f = 0;
	title = NODE;
	parse_ants(nodes);
	while (get_next_line(STDIN_FILENO, &line) > 0)
	{
		ft_putendl(line);
		if (parse_title(line, nodes, &title))
			;
		else
			parse_switch(line, nodes, &title, &f);
		ft_memdel((void **)&line);
	}
	if (!(f & F_START) || !(f & F_END) || !(f & F_REL))
		print_error(nodes);
	if (valid_start_end(*nodes))
		print_error(nodes);
	ft_putendl("");
}

void			parse_ants(t_nodes **nodes)
{
	char		*line;

	g_ants = -1;
	if (get_next_line(STDIN_FILENO, &line) > 0)
	{
		ft_putendl(line);
		if (ft_strlen(line) && ft_isnumber(line, ft_strlen(line)))
			g_ants = ft_atoi(line);
		ft_memdel((void **)&line);
	}
	if (g_ants < 0)
		print_error(nodes);
}

int				parse_title(char *line, t_nodes **nodes, t_title *title)
{
	char **tmp;

	if (ft_strequ(line, T_START))
		*title = START;
	else if (ft_strequ(line, T_END))
		*title = END;
	else if (*line == T_COMMENT)
	{
		if ((line[1] != 'L' && (tmp = valid_line_node(line + 1))) ||
			(tmp = valid_line_relation(line + 1, *nodes)))
		{
			array_clear(tmp);
			print_error(nodes);
		}
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

void			parse_switch(char *line, t_nodes **nodes,
								t_title *title, t_uc *f)
{
	if (*title == START)
	{
		if (*f & F_START)
			print_error(nodes);
		parse_section_node(line, nodes, title, f);
		*title = NODE;
		*f |= F_START;
	}
	else if (*title == END)
	{
		if (*f & F_END)
			print_error(nodes);
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
