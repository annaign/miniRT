/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:02:31 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:02:32 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_cylinder(t_scene *scene)
{
	t_cylinder	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		!scene->rt.arr[4] || !scene->rt.arr[5] || scene->rt.arr[6] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_vector(scene, &(obj->vector), scene->rt.arr[2]) || \
		check_num_d(scene->rt.arr[3]) || check_num_d(scene->rt.arr[4]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[5]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	obj->diameter = ft_atof(scene->rt.arr[3]);
	obj->height = ft_atof(scene->rt.arr[4]);
	ft_lstadd_front(&(scene->cy), ft_lstnew(obj));
}

int		intersect_cylinder_pipe(t_cylinder *cyl, t_ray ray, double *dist)
{
	double		a;
	double		b;
	double		c;
	double		t;
	t_vector	oc;

	t = 0;
	oc = vector_sub(ray.origin, cyl->point);
	a = 1 - pow(vector_dot_product(ray.direction, cyl->vector), 2);
	b = 2 * (vector_dot_product(ray.direction, oc) -
			vector_dot_product(ray.direction, cyl->vector) *
			vector_dot_product(oc, cyl->vector));
	c = vector_dot_product(oc, oc) -
		pow(vector_dot_product(oc, cyl->vector), 2) - pow(cyl->diameter / 2, 2);
	cyl->discr = pow(b, 2) - 4 * a * c;
	if (cyl->discr < EPSILON)
		return (FALSE);
	cyl->x1 = (-b + sqrt(cyl->discr)) / (2 * a);
	cyl->x2 = (-b - sqrt(cyl->discr)) / (2 * a);
	if (cyl->x1 > cyl->x2)
		t = cyl->x2;
	if (t < EPSILON || t > ray.dist)
		return (FALSE);
	*dist = t;
	return (TRUE);
}

int		intersect_cylinder_cap_1(t_cylinder *cyl, t_ray *ray, double *dist)
{
	t_plane		pl;
	t_vector	point;

	pl.vector = cyl->vector;
	pl.color = cyl->color;
	pl.point = vector_add(cyl->point, vector_scale(cyl->height, cyl->vector));
	if (intersect_plane(&pl, *ray, dist) && \
		*dist > EPSILON && *dist < ray->dist)
	{
		point = vector_add(ray->origin, vector_scale(*dist, ray->direction));
		if (vector_length(vector_sub(point, pl.point)) < (cyl->diameter / 2))
		{
			ray->point = vector_add(ray->origin, \
						vector_scale(ray->dist, ray->direction));
			ray->normal = cyl->vector;
			if (vector_dot_product(cyl->vector, ray->direction) > 0)
				ray->normal = vector_scale(-1, ray->normal);
			vector_normalize(&ray->normal);
			return (TRUE);
		}
	}
	return (FALSE);
}

int		intersect_cylinder_cap_2(t_cylinder *cyl, t_ray *ray, double *dist)
{
	t_vector	point;

	if (intersect_plane((t_plane *)cyl, *ray, dist) && \
		*dist > EPSILON && *dist < ray->dist)
	{
		point = vector_add(ray->origin, vector_scale(*dist, ray->direction));
		if (vector_length(vector_sub(point, cyl->point)) < (cyl->diameter / 2))
		{
			ray->point = vector_add(ray->origin, \
						vector_scale(ray->dist, ray->direction));
			ray->normal = cyl->vector;
			if (vector_dot_product(cyl->vector, ray->direction) > 0)
				ray->normal = vector_scale(-1, ray->normal);
			return (TRUE);
		}
	}
	return (FALSE);
}

int		intersect_cylinder(t_cylinder *cyl, t_ray *ray, double *dist)
{
	double		t;
	double		m;
	t_vector	point;

	t = *dist;
	if (intersect_cylinder_pipe(cyl, *ray, dist))
	{
		point = vector_add(ray->origin, vector_scale(*dist, ray->direction));
		m = vector_dot_product(cyl->vector, vector_sub(point, cyl->point));
		if (m > 0 && m < cyl->height)
		{
			ray->point = point;
			ray->normal = vector_sub(point, \
						vector_add(cyl->point, vector_scale(m, cyl->vector)));
			return (TRUE);
		}
	}
	*dist = t;
	if (intersect_cylinder_cap_1(cyl, ray, dist))
		return (TRUE);
	*dist = t;
	if (intersect_cylinder_cap_2(cyl, ray, dist))
		return (TRUE);
	*dist = t;
	return (FALSE);
}
