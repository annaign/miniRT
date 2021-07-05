/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_calc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 22:41:55 by pshagwel          #+#    #+#             */
/*   Updated: 2020/10/16 22:41:56 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	nearest_intersect2(t_scene *scene, t_ray *ray)
{
	t_list		*obj;

	obj = scene->sq;
	while (obj)
	{
		intersect_sq((t_square *)obj->content, ray);
		obj = obj->next;
	}
	obj = scene->tr;
	while (obj)
	{
		intersect_tr((t_triangle *)obj->content, ray);
		obj = obj->next;
	}
	obj = scene->cy;
	while (obj)
	{
		intersect_cy((t_cylinder *)obj->content, ray);
		obj = obj->next;
	}
}

void		nearest_intersect(t_scene *scene, t_ray *ray)
{
	t_list		*obj;

	obj = scene->sp;
	while (obj)
	{
		intersect_sp((t_sphere *)obj->content, ray);
		obj = obj->next;
	}
	obj = scene->pl;
	while (obj)
	{
		intersect_pl((t_plane *)obj->content, ray);
		obj = obj->next;
	}
	nearest_intersect2(scene, ray);
}

static int	shadow_intersect2(t_scene *scene, t_ray *ray)
{
	t_list		*obj;

	obj = scene->sq;
	while (obj)
	{
		if (intersect_sq((t_square *)obj->content, ray))
			return (TRUE);
		obj = obj->next;
	}
	obj = scene->tr;
	while (obj)
	{
		if (intersect_tr((t_triangle *)obj->content, ray))
			return (TRUE);
		obj = obj->next;
	}
	obj = scene->cy;
	while (obj)
	{
		if (intersect_cy((t_cylinder *)obj->content, ray))
			return (TRUE);
		obj = obj->next;
	}
	return (FALSE);
}

int			shadow_intersect(t_scene *scene, t_ray *ray)
{
	t_list		*obj;

	obj = scene->sp;
	while (obj)
	{
		if (intersect_sp((t_sphere *)obj->content, ray))
			return (TRUE);
		obj = obj->next;
	}
	while (obj)
	{
		if (intersect_pl((t_plane *)obj->content, ray))
			return (TRUE);
		obj = obj->next;
	}
	return (shadow_intersect2(scene, ray));
}
