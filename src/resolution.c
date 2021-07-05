/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolution.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:33:01 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:33:03 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_screen_size(t_scene *scene)
{
	int	sizex;
	int	sizey;
	int	ret;

	ret = mlx_get_screen_size(scene->mlx_ptr, &sizex, &sizey);
	if (scene->r_x > sizex)
		scene->r_x = sizex;
	if (scene->r_y > sizey)
		scene->r_y = sizey;
	if (scene->r_x <= 0 || scene->r_y <= 0)
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
						"Wrong argument (screen size).");
	return (ret);
}

void		parse_resolution(t_scene *scene)
{
	if (scene->r == 1)
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Resolution can only be declared once in the scene.");
	if (!scene->rt.arr[1] || !scene->rt.arr[2] || scene->rt.arr[3] || \
		check_num(scene->rt.arr[1]) || check_num(scene->rt.arr[2]))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Wrong argument.");
	scene->r_x = ft_atoi(scene->rt.arr[1]);
	scene->r_y = ft_atoi(scene->rt.arr[2]);
	scene->r = 1;
	check_screen_size(scene);
}
