/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:05:45 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/19 23:05:47 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	camera_position_up(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.y += 1.0;
		show_scene(scene);
	}
	return (0);
}

int	camera_position_down(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.y -= 1.0;
		show_scene(scene);
	}
	return (0);
}

int	camera_position_zoom_in(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.z += 1.0;
		show_scene(scene);
	}
	return (0);
}

int	camera_position_zoom_out(t_scene *scene)
{
	if (scene->c)
	{
		((t_camera *)scene->c->content)->point.z -= 1.0;
		show_scene(scene);
	}
	return (0);
}
