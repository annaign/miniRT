/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 00:41:54 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 00:41:55 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		init_scene(t_scene *scene)
{
	scene->rt.line = NULL;
	scene->rt.arr = NULL;
	scene->win_ptr = NULL;
	scene->img.ptr = NULL;
	scene->r = 0;
	scene->r_x = 0;
	scene->r_y = 0;
	scene->a = 0;
	scene->c = NULL;
	scene->l = NULL;
	scene->sp = NULL;
	scene->pl = NULL;
	scene->sq = NULL;
	scene->cy = NULL;
	scene->tr = NULL;
}

static void	parse_line(t_scene *scene)
{
	if (ft_strcmp(scene->rt.arr[0], "R") == 0)
		parse_resolution(scene);
	else if (ft_strcmp(scene->rt.arr[0], "A") == 0)
		parse_amb_light(scene);
	else if (ft_strcmp(scene->rt.arr[0], "c") == 0)
		parse_camera(scene);
	else if (ft_strcmp(scene->rt.arr[0], "l") == 0)
		parse_light(scene);
	else if (ft_strcmp(scene->rt.arr[0], "sp") == 0)
		parse_sphere(scene);
	else if (ft_strcmp(scene->rt.arr[0], "pl") == 0)
		parse_plane(scene);
	else if (ft_strcmp(scene->rt.arr[0], "sq") == 0)
		parse_square(scene);
	else if (ft_strcmp(scene->rt.arr[0], "cy") == 0)
		parse_cylinder(scene);
	else if (ft_strcmp(scene->rt.arr[0], "tr") == 0)
		parse_triangle(scene);
	else
		exit_with_error_msg(scene, ERR_SCENE_RT, scene->rt.line,
		"Wrong type identifier.");
}

static void	check_scene_rt(t_scene *scene, char *file_rt)
{
	int	len;

	len = ft_strlen(file_rt);
	if (len <= 3 || (ft_strncmp(file_rt + (len - 3), ".rt", 3)) != 0)
		exit_with_error(scene, ERR_ARG_1);
}

static void	read_scene_rt(t_scene *scene, char *file_rt)
{
	int			fd;
	int			gnl;

	if ((fd = open(file_rt, O_RDONLY)) == -1)
		exit_with_errno(scene);
	while ((gnl = get_next_line(fd, &scene->rt.line)) >= 0)
	{
		if (!(scene->rt.arr = ft_split(scene->rt.line, ' ')))
			exit_with_errno(scene);
		if (!(scene->rt.arr[0]) && gnl == 0)
			break ;
		if (scene->rt.arr[0])
			parse_line(scene);
		clear_arr(scene->rt.arr);
		scene->rt.arr = NULL;
		clear_rt_line(scene);
		if (gnl == 0)
			break ;
	}
	if (gnl == -1)
		exit_with_error(scene, ERR_GNL);
	if (close(fd) == -1)
		exit_with_errno(scene);
}

void		parse_scene(t_scene *scene, char *file_rt)
{
	check_scene_rt(scene, file_rt);
	read_scene_rt(scene, file_rt);
	scene->img.ptr = mlx_new_image(scene->mlx_ptr, scene->r_x, scene->r_y);
	scene->img.addr = (int *)mlx_get_data_addr(scene->img.ptr,
					&(scene->img.bitspixl), &(scene->img.len),
					&(scene->img.endian));
}
