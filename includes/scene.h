/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 15:15:32 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 15:15:33 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "objects.h"

typedef struct		s_rt
{
	char			*line;
	char			**arr;
}					t_rt;

typedef struct		s_img
{
	void			*ptr;
	int				*addr;
	int				bitspixl;
	int				len;
	int				endian;
}					t_img;

typedef struct		s_light
{
	t_vector		point;
	double			ratio;
	t_color			color;
}					t_light;

typedef struct		s_camera
{
	t_vector		point;
	t_vector		vector;
	int				fov;
	double			tan_fov;
}					t_camera;

typedef struct		s_scene
{
	t_rt			rt;
	void			*mlx_ptr;
	void			*win_ptr;
	t_img			img;
	int				r;
	int				r_x;
	int				r_y;
	int				a;
	double			a_ratio;
	t_color			a_color;
	t_list			*c;
	t_list			*l;
	t_list			*sp;
	t_list			*pl;
	t_list			*sq;
	t_list			*cy;
	t_list			*tr;
}					t_scene;

#endif
