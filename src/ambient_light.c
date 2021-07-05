/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:35:42 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:35:44 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_amb_light(t_scene *scene)
{
	if (scene->a == 1)
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Ambient lightning can only be declared once in the scene.");
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || scene->rt.arr[3])
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Wrong argument.");
	if (parse_ratio(&(scene->a_ratio), scene->rt.arr[1]) || \
		parse_color(scene, &(scene->a_color), scene->rt.arr[2]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Wrong argument.");
	scene->a = 1;
}
