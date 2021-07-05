/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/22 20:58:23 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/22 20:58:24 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	bmp_header_file(t_scene *scene, int fd)
{
	unsigned char	header[14];
	int				file_size;
	int				padding;

	ft_bzero((void *)header, 14);
	padding = (4 - ((scene->r_x * RGB) % 4)) % 4;
	file_size = 54 + (scene->r_x * RGB + padding) * scene->r_y;
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(file_size);
	header[3] = (unsigned char)(file_size >> 8);
	header[4] = (unsigned char)(file_size >> 16);
	header[5] = (unsigned char)(file_size >> 24);
	header[10] = (unsigned char)(14 + 40);
	if ((write(fd, header, 14)) == -1)
		return (1);
	return (0);
}

int	bmp_header_img(t_scene *scene, int fd)
{
	unsigned char	header[40];

	ft_bzero((void *)header, 40);
	header[0] = (unsigned char)(40);
	header[4] = (unsigned char)(scene->r_x);
	header[5] = (unsigned char)(scene->r_x >> 8);
	header[6] = (unsigned char)(scene->r_x >> 16);
	header[7] = (unsigned char)(scene->r_x >> 24);
	header[8] = (unsigned char)(scene->r_y);
	header[9] = (unsigned char)(scene->r_y >> 8);
	header[10] = (unsigned char)(scene->r_y >> 16);
	header[11] = (unsigned char)(scene->r_y >> 24);
	header[12] = (unsigned char)(1);
	header[14] = (unsigned char)(BPP);
	if ((write(fd, header, 40)) == -1)
		return (1);
	return (0);
}

int	bmp_scene(t_scene *scene, int fd)
{
	int				padding;
	int				w;
	int				h;
	unsigned char	extra_bytes[3];

	extra_bytes[0] = 0;
	extra_bytes[1] = 0;
	extra_bytes[2] = 0;
	padding = (4 - ((scene->r_x * RGB) % 4)) % 4;
	h = scene->r_y;
	while (h-- > 0)
	{
		w = 0;
		while (w < scene->r_x)
		{
			if ((write(fd, &scene->img.addr[h * scene->r_x + w], RGB)) == -1)
				return (1);
			w++;
		}
		if (padding > 0)
			if ((write(fd, &extra_bytes, padding)) == -1)
				return (1);
	}
	return (0);
}
