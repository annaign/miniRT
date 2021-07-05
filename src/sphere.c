/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:09:45 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:09:46 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		parse_sphere(t_scene *scene)
{
	t_sphere	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		scene->rt.arr[4] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		check_num_d(scene->rt.arr[2]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[3]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	obj->diameter = ft_atof(scene->rt.arr[2]);
	ft_lstadd_front(&(scene->sp), ft_lstnew(obj));
}

static void	swap_double(double *dist, double *t1)
{
	double		temp;

	temp = *dist;
	*dist = *t1;
	*t1 = temp;
}

int			intersect_sphere(t_sphere *sphere, t_ray *ray)
{
	t_vector	l;
	double		tca;
	double		d2;
	double		t1;
	double		dist;

	l = vector_sub(sphere->point, ray->origin);
	tca = vector_dot_product(l, ray->direction);
	d2 = vector_dot_product(l, l) - pow(tca, 2);
	if (d2 > pow(sphere->diameter / 2, 2))
		return (FALSE);
	dist = tca - sqrt(pow(sphere->diameter / 2, 2) - d2);
	t1 = tca + sqrt(pow(sphere->diameter / 2, 2) - d2);
	if (dist > t1)
		swap_double(&dist, &t1);
	if (dist < 0.0)
		dist = t1;
	if (dist < 0.0 || dist < EPSILON || dist > ray->dist)
		return (FALSE);
	ray->dist = dist;
	return (TRUE);
}
