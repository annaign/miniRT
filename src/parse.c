/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/19 22:59:46 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/19 22:59:48 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_ratio(double *ratio, char *line)
{
	if (check_num_d(line))
		return (1);
	*ratio = ft_atof(line);
	if (*ratio < 0.0 || *ratio > 1.0)
		return (1);
	return (0);
}

int	parse_fov(int *fov, char *line)
{
	if (check_num(line))
		return (1);
	*fov = ft_atoi(line);
	if (*fov < 0 || *fov > 180)
		return (1);
	return (0);
}

int	parse_color(t_scene *scene, t_color *color, char *line)
{
	char	**arr;

	if (!(check_line(line, ',', 2)))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	if (!(arr = ft_split(line, ',')))
		exit_with_errno(scene);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3] || \
		check_num(arr[0]) || check_num(arr[1]) || check_num(arr[2]))
	{
		clear_arr(arr);
		return (1);
	}
	color->r = ft_atoi(arr[0]);
	color->g = ft_atoi(arr[1]);
	color->b = ft_atoi(arr[2]);
	clear_arr(arr);
	if (color->r < COLOR_MIN || color->r > COLOR_MAX || color->g < COLOR_MIN ||
		color->g > COLOR_MAX || color->b < COLOR_MIN || color->b > COLOR_MAX)
		return (1);
	return (0);
}

int	parse_coordinates(t_scene *scene, t_vector *point, char *line)
{
	char	**arr;

	if (!(check_line(line, ',', 2)))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	if (!(arr = ft_split(line, ',')))
		exit_with_errno(scene);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3] || \
		check_num_d(arr[0]) || check_num_d(arr[1]) || check_num_d(arr[2]))
	{
		clear_arr(arr);
		return (1);
	}
	point->x = ft_atof(arr[0]);
	point->y = ft_atof(arr[1]);
	point->z = ft_atof(arr[2]);
	clear_arr(arr);
	return (0);
}

int	parse_vector(t_scene *scene, t_vector *vector, char *line)
{
	char	**arr;

	if (!(check_line(line, ',', 2)))
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
							"Wrong argument.");
	if (!(arr = ft_split(line, ',')))
		exit_with_errno(scene);
	if (!arr[0] || !arr[1] || !arr[2] || arr[3] || \
		check_num_d(arr[0]) || check_num_d(arr[1]) || check_num_d(arr[2]))
	{
		clear_arr(arr);
		return (1);
	}
	vector->x = ft_atof(arr[0]);
	vector->y = ft_atof(arr[1]);
	vector->z = ft_atof(arr[2]);
	clear_arr(arr);
	if ((vector->x < -1 || vector->x > 1) || \
		(vector->y < -1 || vector->y > 1) || \
		(vector->z < -1 || vector->z > 1))
		return (1);
	return (0);
}
