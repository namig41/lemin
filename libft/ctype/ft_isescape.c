/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isescape.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcarmelo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 19:25:12 by lcarmelo          #+#    #+#             */
/*   Updated: 2020/03/16 11:08:11 by lcarmelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_isescape(int c)
{
	return (c == '\n' || c == '\t' || c == '\v' ||
			c == '\f' || c == '\b' || c == ' ');
}