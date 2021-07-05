/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/11 17:20:06 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/11 17:20:08 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	print_err_msg(int err)
{
	ft_putstr_fd("Error\n", 2);
	if (err == ERR_ARGS)
		ft_putstr_fd("miniRT takes one or two arguments.\n", 2);
	else if (err == ERR_ARG_1)
		ft_putstr_fd("Wrong file extension. Should be '.rt'.\n", 2);
	else if (err == ERR_ARG_2)
		ft_putstr_fd("Wrong second argument. It can be only '--save'.\n", 2);
	else if (err == ERR_MLX_INIT)
		ft_putstr_fd("Mlx init error.\n", 2);
	else if (err == ERR_GNL)
		ft_putstr_fd("GNL reading error.\n", 2);
	else if (err == ERR_SCENE_RT)
		ft_putstr_fd("Scene error.\n", 2);
	else if (err == ERR_MEMORY)
		ft_putstr_fd("Memory error.\n", 2);
	else
		ft_putstr_fd("Unknown error.\n", 2);
}

void		exit_with_error(t_scene *scene, int err)
{
	memory_clean(scene);
	print_err_msg(err);
	exit(EXIT_FAILURE);
}

void		exit_with_error_msg(t_scene *scene, int err, char *line, char *msg)
{
	print_err_msg(err);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\nWrong line: ", 2);
	ft_putstr_fd(line, 2);
	ft_putstr_fd("\n", 2);
	memory_clean(scene);
	exit(EXIT_FAILURE);
}

void		exit_with_errno(t_scene *scene)
{
	memory_clean(scene);
	perror("Error\nerrno");
	exit(EXIT_FAILURE);
}
