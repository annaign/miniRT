/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 23:54:45 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/19 23:54:47 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	calc_triangle(t_triangle *obj)
{
	obj->e1 = vector_sub(obj->point_2, obj->point);
	obj->e2 = vector_sub(obj->point_3, obj->point);
	obj->vector = vector_cross_product(obj->e1, obj->e2);
	vector_normalize(&obj->vector);
}

void		parse_triangle(t_scene *scene)
{
	t_triangle	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		!scene->rt.arr[4] || scene->rt.arr[5] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_coordinates(scene, &(obj->point_2), scene->rt.arr[2]) || \
		parse_coordinates(scene, &(obj->point_3), scene->rt.arr[3]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[4]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	calc_triangle(obj);
	ft_lstadd_front(&(scene->tr), ft_lstnew(obj));
}

int			intersect_triangle(t_triangle *triangle, t_ray ray, double *dist)
{
	t_matrix	vec;
	double		det;
	double		u;
	double		v;
	double		t;

	vec.vx = vector_cross_product(ray.direction, triangle->e2);
	det = vector_dot_product(triangle->e1, vec.vx);
	if (det < EPSILON && det > -EPSILON)
		return (FALSE);
	vec.vy = vector_sub(ray.origin, triangle->point);
	u = vector_dot_product(vec.vy, vec.vx) * (1.0 / det);
	if (u < 0.0 || u > 1.0)
		return (FALSE);
	vec.vz = vector_cross_product(vec.vy, triangle->e1);
	v = vector_dot_product(ray.direction, vec.vz) * (1.0 / det);
	if (v < 0.0 || u + v > 1.0)
		return (FALSE);
	t = vector_dot_product(triangle->e2, vec.vz) * (1.0 / det);
	if (t > EPSILON)
	{
		*dist = t;
		return (TRUE);
	}
	return (FALSE);
}
