/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:11:53 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:11:54 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void			parse_light(t_scene *scene)
{
	t_light	*obj;

	obj = malloc(sizeof(*obj));
	if (!obj)
		exit_with_error(scene, ERR_MEMORY);
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || !scene->rt.arr[3] || \
		scene->rt.arr[4] || \
		parse_coordinates(scene, &(obj->point), scene->rt.arr[1]) || \
		parse_ratio(&(obj->ratio), scene->rt.arr[2]) || \
		parse_color(scene, &(obj->color), scene->rt.arr[3]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	ft_lstadd_front(&(scene->l), ft_lstnew(obj));
}

static t_color	spot_light(t_light *l, t_ray *ray, double diffusion)
{
	t_color		color;
	double		specular;
	double		k;

	specular = pow(fmax(diffusion, 0.0), 50);
	if (diffusion < 0)
		k = 0;
	else
		k = l->ratio;
	color.r = k * l->color.r * (ray->color.r * diffusion / 255 + specular);
	color.g = k * l->color.g * (ray->color.g * diffusion / 255 + specular);
	color.b = k * l->color.b * (ray->color.b * diffusion / 255 + specular);
	return (color);
}

static double	create_shadow(t_ray *shadow, t_ray *ray, t_light *l, t_vector p)
{
	double		dist_max;

	shadow->point = (t_vector){0, 0, 0};
	shadow->normal = (t_vector){255, 255, 255};
	vector_normalize(&shadow->normal);
	shadow->origin = ray->point;
	shadow->direction = vector_sub(l->point, p);
	dist_max = vector_length(shadow->direction);
	vector_normalize(&shadow->direction);
	shadow->dist = dist_max;
	return (dist_max);
}

void			calc_lightning(t_scene *s, t_ray *ray, t_vector n, t_vector p)
{
	t_list		*l;
	t_ray		shadow;
	t_color		aux_color;
	t_color		color;
	double		dist_max;

	l = s->l;
	color = (t_color){0, 0, 0};
	while (l)
	{
		dist_max = create_shadow(&shadow, ray, (t_light *)l->content, p);
		aux_color = color_ambient(s, ray->color);
		if (!(shadow_intersect(s, &shadow) && \
			shadow.dist > EPSILON && shadow.dist < dist_max))
			color_mix(&aux_color, (spot_light((t_light *)l->content, ray, \
			vector_dot_product(shadow.direction, n))));
		color_mix(&color, aux_color);
		l = l->next;
	}
	if (!s->l)
		color = color_ambient(s, ray->color);
	ray->color.r = color.r;
	ray->color.g = color.g;
	ray->color.b = color.b;
}
