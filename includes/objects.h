/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 14:34:08 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 14:34:09 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTS_H
# define OBJECTS_H

typedef struct		s_color
{
	double			r;
	double			g;
	double			b;
}					t_color;

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct		s_matrix
{
	t_vector		vx;
	t_vector		vy;
	t_vector		vz;
}					t_matrix;

typedef struct		s_sphere
{
	t_vector		point;
	double			diameter;
	t_color			color;
}					t_sphere;

typedef struct		s_plane
{
	t_vector		point;
	t_vector		vector;
	t_color			color;
}					t_plane;

typedef struct		s_square
{
	t_vector		point;
	t_vector		vector;
	double			side;
	t_color			color;
}					t_square;

typedef struct		s_cylinder
{
	t_vector		point;
	t_vector		vector;
	double			diameter;
	double			height;
	t_color			color;
	double			discr;
	double			x1;
	double			x2;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vector		point;
	t_vector		point_2;
	t_vector		point_3;
	t_color			color;
	t_vector		vector;
	t_vector		e1;
	t_vector		e2;
}					t_triangle;

#endif
