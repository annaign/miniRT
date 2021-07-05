/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:05:45 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/19 23:05:47 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** TODO: Add the code below in exit_hook() after merge 17 & 19 pull requests
** https://github.com/42Paris/minilibx-linux
**
** // mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
** scene->win_ptr = NULL;
** mlx_destroy_display(scene->mlx_ptr);
** scene->img.ptr = NULL;
*/

#include "minirt.h"

int	exit_hook(t_scene *scene)
{
	mlx_destroy_window(scene->mlx_ptr, scene->win_ptr);
	memory_clean(scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	camera_right(t_scene *scene)
{
	t_list	*first;

	first = scene->c;
	if (first && first->next)
	{
		scene->c = first->next;
		first->next = NULL;
		ft_lstadd_back(&scene->c, first);
		show_scene(scene);
	}
	return (0);
}

int	camera_left(t_scene *scene)
{
	t_list	*last;
	t_list	*before_last;

	last = ft_lstlast(scene->c);
	if (scene->c && scene->c->next && last)
	{
		before_last = scene->c;
		while (before_last->next != last)
			before_last = before_last->next;
		before_last->next = NULL;
		ft_lstadd_front(&scene->c, last);
		show_scene(scene);
	}
	return (0);
}

int	camera_position_left(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.x -= 1.0;
		show_scene(scene);
	}
	return (0);
}

int	camera_position_right(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.x += 1.0;
		show_scene(scene);
	}
	return (0);
}
