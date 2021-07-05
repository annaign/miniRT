/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:32:51 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/11 17:32:52 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int		create_trgb(t_color color)
{
	int t;

	t = 0;
	color.r = (color.r < COLOR_MIN) ? COLOR_MIN : color.r;
	color.r = (color.r > COLOR_MAX) ? COLOR_MAX : color.r;
	color.g = (color.g < COLOR_MIN) ? COLOR_MIN : color.g;
	color.g = (color.g > COLOR_MAX) ? COLOR_MAX : color.g;
	color.b = (color.b < COLOR_MIN) ? COLOR_MIN : color.b;
	color.b = (color.b > COLOR_MAX) ? COLOR_MAX : color.b;
	return (t << 24 | (int)color.r << 16 | (int)color.g << 8 | (int)color.b);
}

t_color	color_ambient(t_scene *scene, t_color ray)
{
	t_color	color;

	color.r = scene->a_ratio * scene->a_color.r * ray.r / 255;
	color.g = scene->a_ratio * scene->a_color.g * ray.g / 255;
	color.b = scene->a_ratio * scene->a_color.b * ray.b / 255;
	return (color);
}

void	color_mix(t_color *color_base, t_color color)
{
	color_base->r += color.r;
	color_base->g += color.g;
	color_base->b += color.b;
}
