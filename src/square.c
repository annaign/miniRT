/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:05:34 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:05:36 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_square(t_scene *scene)
{
	t_square	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		!scene->rt.arr[4] || scene->rt.arr[5] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_vector(scene, &(obj->vector), scene->rt.arr[2]) || \
		check_num_d(scene->rt.arr[3]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[4]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	obj->side = ft_atof(scene->rt.arr[3]);
	ft_lstadd_front(&(scene->sq), ft_lstnew(obj));
}

static void	calc_sq(t_square *square, t_vector *dx, t_vector *dy)
{
	*dx = (t_vector){1, 0, 0};
	*dy = vector_cross_product(square->vector, *dx);
	if (vector_zero(*dy))
	{
		*dx = (t_vector){0, 1, 0};
		*dy = vector_cross_product(square->vector, *dx);
	}
	vector_normalize(dx);
	vector_normalize(dy);
}

int			intersect_square(t_square *square, t_ray ray, double *dist)
{
	t_vector	dx;
	t_vector	dy;
	t_vector	point;
	double		t;

	t = *dist;
	if (intersect_plane((t_plane *)square, ray, dist) && \
		*dist > EPSILON && *dist < ray.dist)
	{
		calc_sq(square, &dx, &dy);
		point = vector_add(ray.origin, \
				vector_scale(*dist + EPSILON, ray.direction));
		if (fabs(vector_dot_product(dx, vector_sub(point, square->point))) <= \
			square->side &&
			fabs(vector_dot_product(dy, vector_sub(point, square->point))) <= \
			square->side)
			return (TRUE);
	}
	*dist = t;
	return (FALSE);
}
