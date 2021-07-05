/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:14:12 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:14:13 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_camera(t_scene *scene)
{
	t_camera	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		scene->rt.arr[4] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_vector(scene, &(obj->vector), scene->rt.arr[2]) || \
		parse_fov(&(obj->fov), scene->rt.arr[3]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	obj->tan_fov = tan(((double)obj->fov / 2.0) * M_PI / 180.0);
	ft_lstadd_front(&(scene->c), ft_lstnew(obj));
}

t_vector	camera_ray(t_scene *scene, double x, double y)
{
	t_vector	dir;
	double		scale;
	double		width;
	double		height;
	double		image_aspect_ratio;

	width = (double)scene->r_x;
	height = (double)scene->r_y;
	image_aspect_ratio = width / height;
	scale = ((t_camera *)scene->c->content)->tan_fov;
	dir.x = (2 * (x + 0.5) / width - 1) * image_aspect_ratio * scale;
	dir.y = (1 - 2 * (y + 0.5) / height) * scale;
	dir.z = -1.0;
	vector_normalize(&dir);
	return (dir);
}

t_vector	calc_matrix_vx(t_scene *scene, t_vector camera)
{
	t_vector vx;

	vx.z = 0;
	if (!camera.x && !camera.y)
	{
		vx.y = 0;
		if (camera.z > 0)
			vx.x = -1.0;
		else if (camera.z < 0)
			vx.x = 1.0;
		else if (!camera.z)
			exit_with_error(scene, ERR_SCENE_RT);
	}
	else
	{
		vx.x = camera.y;
		vx.y = -1.0 * camera.x;
	}
	return (vx);
}

void		rotate_camera(t_scene *scene, t_camera *camera, double x, double y)
{
	t_vector	vector;
	t_matrix	matrix;

	vector = camera_ray(scene, x, y);
	matrix.vx = calc_matrix_vx(scene, camera->vector);
	matrix.vy = vector_cross_product(matrix.vx, camera->vector);
	matrix.vz = vector_scale(-1, camera->vector);
	vector_normalize(&matrix.vx);
	vector_normalize(&matrix.vy);
	vector_normalize(&matrix.vz);
	vector = matrix_vector_product(matrix, vector);
	vector_normalize(&vector);
	camera->vector = vector;
}
