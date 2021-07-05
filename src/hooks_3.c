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

int	camera_vector(t_scene *scene, int key)
{
	t_camera	*camera;

	if (scene->c)
	{
		camera = (t_camera *)scene->c->content;
		if (key == KEY_A)
			rotate_camera(scene, camera, 0, scene->r_y / 2.0);
		else if (key == KEY_S)
			rotate_camera(scene, camera, scene->r_x / 2.0, scene->r_y);
		else if (key == KEY_D)
			rotate_camera(scene, camera, scene->r_x, scene->r_y / 2);
		else if (key == KEY_W)
			rotate_camera(scene, camera, scene->r_x / 2.0, 0);
		else
			return (0);
		show_scene(scene);
	}
	return (0);
}

int	keys_hook(int key, t_scene *scene)
{
	if (key == KEY_ESC)
		exit_hook(scene);
	else if (key == KEY_CAMERA_R)
		camera_right(scene);
	else if (key == KEY_CAMERA_L)
		camera_left(scene);
	else if (key == KEY_LEFT)
		camera_position_left(scene);
	else if (key == KEY_RIGHT)
		camera_position_right(scene);
	else if (key == KEY_UP)
		camera_position_up(scene);
	else if (key == KEY_DOWN)
		camera_position_down(scene);
	else if (key == KEY_ZOOM_IN)
		camera_position_zoom_in(scene);
	else if (key == KEY_ZOOM_OUT)
		camera_position_zoom_out(scene);
	else
		camera_vector(scene, key);
	return (0);
}

int	mouse_hook(int btn, int x, int y, t_scene *scene)
{
	t_camera	*camera;

	if (btn == 1)
	{
		if (scene->c)
		{
			camera = (t_camera *)scene->c->content;
			rotate_camera(scene, camera, x, y);
			show_scene(scene);
		}
	}
	return (0);
}
