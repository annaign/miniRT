/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:07:47 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:07:48 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_plane(t_scene *scene)
{
	t_plane	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		scene->rt.arr[4] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_vector(scene, &(obj->vector), scene->rt.arr[2]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[3]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	ft_lstadd_front(&(scene->pl), ft_lstnew(obj));
}

int		intersect_plane(t_plane *plane, t_ray ray, double *dist)
{
	double		denominator;
	t_vector	diff;

	denominator = vector_dot_product(plane->vector, ray.direction);
	if ((fabs(denominator)) > EPSILON)
	{
		diff = vector_sub(plane->point, ray.origin);
		*dist = (vector_dot_product(diff, plane->vector)) / denominator;
		if (*dist > EPSILON)
			return (TRUE);
	}
	return (FALSE);
}
