/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 21:44:33 by pshagwel          #+#    #+#             */
/*   Updated: 2020/10/16 21:44:36 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	intersect_sp(t_sphere *sp, t_ray *ray)
{
	if (intersect_sphere(sp, ray))
	{
		ray->point = vector_add(ray->origin,
					vector_scale(ray->dist, ray->direction));
		ray->normal = vector_sub(ray->point, sp->point);
		vector_normalize(&ray->normal);
		ray->color = sp->color;
		return (TRUE);
	}
	return (FALSE);
}

int	intersect_pl(t_plane *pl, t_ray *ray)
{
	double	dist;

	dist = ray->dist;
	if (intersect_plane(pl, *ray, &dist) && dist > EPSILON && dist < ray->dist)
	{
		ray->dist = dist;
		ray->point = vector_add(ray->origin,
					vector_scale(ray->dist, ray->direction));
		ray->normal = pl->vector;
		if (vector_dot_product(pl->vector, ray->direction) > 0)
			ray->normal = vector_scale(-1, ray->normal);
		vector_normalize(&ray->normal);
		ray->color = pl->color;
		return (TRUE);
	}
	return (FALSE);
}

int	intersect_sq(t_square *sq, t_ray *ray)
{
	double	dist;

	dist = ray->dist;
	if (intersect_square(sq, *ray, &dist) && dist > EPSILON && dist < ray->dist)
	{
		ray->dist = dist;
		ray->point = vector_add(ray->origin,
					vector_scale(ray->dist, ray->direction));
		ray->normal = sq->vector;
		if (vector_dot_product(sq->vector, ray->direction) > 0)
			ray->normal = vector_scale(-1, ray->normal);
		vector_normalize(&ray->normal);
		ray->color = sq->color;
		return (TRUE);
	}
	return (FALSE);
}

int	intersect_tr(t_triangle *tr, t_ray *ray)
{
	double	dist;

	dist = ray->dist;
	if (intersect_triangle(tr, *ray, &dist) && \
		dist > EPSILON && dist < ray->dist)
	{
		ray->dist = dist;
		ray->point = vector_add(ray->origin, \
					vector_scale(ray->dist, ray->direction));
		ray->normal = tr->vector;
		if (vector_dot_product(tr->vector, ray->direction) > 0)
			ray->normal = vector_scale(-1, ray->normal);
		vector_normalize(&ray->normal);
		ray->color = tr->color;
		return (TRUE);
	}
	return (FALSE);
}

int	intersect_cy(t_cylinder *cy, t_ray *ray)
{
	double	dist;

	dist = ray->dist;
	if (intersect_cylinder(cy, ray, &dist) && \
		dist > EPSILON && dist < ray->dist)
	{
		ray->dist = dist;
		vector_normalize(&ray->normal);
		ray->color = cy->color;
		return (TRUE);
	}
	return (FALSE);
}
