/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 17:57:58 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/20 17:57:59 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double		vector_length(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

void		vector_normalize(t_vector *v)
{
	double length;

	length = vector_length(*v);
	v->x /= length;
	v->y /= length;
	v->z /= length;
}

t_vector	matrix_vector_product(t_matrix m, t_vector v)
{
	t_vector	mv;

	mv.x = v.x * m.vx.x + v.y * m.vy.x + v.z * m.vz.x;
	mv.y = v.x * m.vx.y + v.y * m.vy.y + v.z * m.vz.y;
	mv.z = v.x * m.vx.z + v.y * m.vy.z + v.z * m.vz.z;
	return (mv);
}

int			vector_zero(t_vector vector)
{
	if (vector.x == 0 && vector.y == 0 && vector.z == 0)
		return (TRUE);
	return (FALSE);
}
