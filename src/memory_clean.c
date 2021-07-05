/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_clean.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 00:32:24 by pshagwel          #+#    #+#             */
/*   Updated: 2020/10/17 00:32:25 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_arr(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			free(arr[i++]);
		free(arr);
		arr = NULL;
	}
}

void	clear_rt_line(t_scene *scene)
{
	free(scene->rt.line);
	scene->rt.line = NULL;
}

void	memory_clean(t_scene *scene)
{
	ft_lstclear(&(scene->c), free);
	ft_lstclear(&(scene->l), free);
	ft_lstclear(&(scene->sp), free);
	ft_lstclear(&(scene->pl), free);
	ft_lstclear(&(scene->sq), free);
	ft_lstclear(&(scene->cy), free);
	ft_lstclear(&(scene->tr), free);
	clear_arr(scene->rt.arr);
	clear_rt_line(scene);
}
