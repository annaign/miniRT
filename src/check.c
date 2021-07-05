/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:03:53 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/19 23:03:56 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		if (!ft_isdigit(str[i++]))
			return (1);
	return (0);
}

int	check_num_d(char *str)
{
	int	i;
	int	dot;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	dot = 0;
	while (str[i] != '\0' && dot < 2)
	{
		if (str[i] == '.')
		{
			dot++;
			i++;
			continue;
		}
		if (!ft_isdigit(str[i++]))
			return (1);
	}
	if (dot > 1)
		return (1);
	return (0);
}

int	check_line(char *line, char ch, int sum)
{
	int	comma;
	int	i;

	comma = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ch)
			comma++;
		i++;
	}
	if (comma == sum)
		return (TRUE);
	return (FALSE);
}
