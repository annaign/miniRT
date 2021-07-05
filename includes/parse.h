/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:33:52 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 14:33:53 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# include "scene.h"

int				parse_color(t_scene *scene, t_color *color, char *line);
int				parse_fov(int *fov, char *line);
int				parse_ratio(double *ratio, char *line);
int				parse_coordinates(t_scene *scene, t_vector *point, char *line);
int				parse_vector(t_scene *scene, t_vector *vector, char *line);

void			parse_triangle (t_scene *scene);
void			parse_cylinder(t_scene *scene);
void			parse_square(t_scene *scene);
void			parse_plane(t_scene *scene);
void			parse_sphere(t_scene *scene);
void			parse_light(t_scene *scene);
void			parse_camera(t_scene *scene);
void			parse_resolution(t_scene *scene);
void			parse_amb_light(t_scene *scene);
void			parse_scene(t_scene *scene, char *file_rt);

#endif
