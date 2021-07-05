/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 23:37:09 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/01 23:37:10 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	render_pixel(t_scene *scene, t_ray *ray, int x, int y)
{
	t_matrix	matrix;
	t_camera	*camera;

	camera = (t_camera *)scene->c->content;
	ray->origin = camera->point;
	ray->direction = camera_ray(scene, x, y);
	matrix.vx = calc_matrix_vx(scene, camera->vector);
	matrix.vy = vector_cross_product(matrix.vx, camera->vector);
	matrix.vz = vector_scale(-1, camera->vector);
	vector_normalize(&matrix.vx);
	vector_normalize(&matrix.vy);
	vector_normalize(&matrix.vz);
	ray->direction = matrix_vector_product(matrix, ray->direction);
	vector_normalize(&ray->direction);
	ray->dist = __DBL_MAX__;
	ray->point = (t_vector){0, 0, 0};
	ray->normal = (t_vector){255, 255, 255};
	nearest_intersect(scene, ray);
	vector_normalize(&ray->normal);
	calc_lightning(scene, ray, ray->normal, ray->point);
}

static void	render_scene(t_scene *s)
{
	int			x;
	int			y;
	t_ray		ray;

	x = -1;
	while (++x < s->r_x)
	{
		y = -1;
		while (++y < s->r_y)
		{
			ray.color = (t_color){0, 0, 0};
			if (s->c)
				render_pixel(s, &ray, x, y);
			s->img.addr[x + y * s->img.len / 4] = create_trgb(ray.color);
		}
	}
}

void		show_scene(t_scene *scene)
{
	render_scene(scene);
	mlx_clear_window(scene->mlx_ptr, scene->win_ptr);
	mlx_put_image_to_window(scene->mlx_ptr, scene->win_ptr, \
							scene->img.ptr, 0, 0);
}

void		save_scene(t_scene *scene, char *file)
{
	int	fd;

	ft_putstr_fd("Converning scene to .bmp...\n", 1);
	render_scene(scene);
	if ((fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0744)) == -1)
		exit_with_errno(scene);
	if ((bmp_header_file(scene, fd)) || (bmp_header_img(scene, fd)) || \
		(bmp_scene(scene, fd)))
		exit_with_errno(scene);
	close(fd);
	memory_clean(scene);
	ft_putstr_fd("Saved in file ", 1);
	ft_putstr_fd(file, 1);
	ft_putstr_fd("\n", 1);
}

int			main(int argc, char *argv[])
{
	t_scene	s;

	init_scene(&s);
	if (argc < 2 || argc > 3)
		exit_with_error(&s, ERR_ARGS);
	if (!(s.mlx_ptr = mlx_init()))
		exit_with_error(&s, ERR_MLX_INIT);
	parse_scene(&s, argv[1]);
	if (argc == 2)
	{
		s.win_ptr = mlx_new_window(s.mlx_ptr, s.r_x, s.r_y, "miniRT");
		mlx_hook(s.win_ptr, 17, 1L << 17, exit_hook, &s);
		mlx_key_hook(s.win_ptr, keys_hook, &s);
		mlx_mouse_hook(s.win_ptr, mouse_hook, &s);
		show_scene(&s);
		mlx_loop(s.mlx_ptr);
	}
	else
	{
		if (ft_strncmp(argv[2], "--save", 7) != 0)
			exit_with_error(&s, ERR_ARG_2);
		save_scene(&s, "scene.bmp");
	}
	return (0);
}
