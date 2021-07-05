/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/10 18:47:23 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/10 18:47:25 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

# include "scene.h"

# define ERR_ARGS 1
# define ERR_ARG_1 2
# define ERR_ARG_2 3
# define ERR_MLX_INIT 4
# define ERR_GNL 5
# define ERR_SCENE_RT 6
# define ERR_MEMORY 7

void				exit_with_error(t_scene *scene, int err);
void				exit_with_error_msg(t_scene *scene, int err, char *line,
					char *msg);
void				exit_with_errno(t_scene *scene);

#endif
