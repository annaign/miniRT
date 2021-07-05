/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pshagwel <pshagwel@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 23:34:41 by pshagwel          #+#    #+#             */
/*   Updated: 2020/09/01 23:34:42 by pshagwel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** open, close, read, write, malloc, free, perror, strerror, exit
*/

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <math.h>
# include "mlx.h"
# include "libft.h"
# include "get_next_line.h"
# include "scene.h"
# include "errors.h"
# include "parse.h"

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# define EPSILON 0.00001

# define KEY_ESC 65307
# define KEY_CAMERA_L 108
# define KEY_CAMERA_R 114
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_ZOOM_IN 105
# define KEY_ZOOM_OUT 111
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_W 119

# define COLOR_MIN 0
# define COLOR_MAX 255
# define RGB 3
# define BPP 24

typedef struct		s_ray
{
	int				x;
	int				y;
	t_vector		origin;
	t_vector		direction;
	t_color			color;
	double			dist;
	t_vector		normal;
	t_vector		point;
}					t_ray;

void				init_scene(t_scene *scene);
int					check_num(char *str);
int					check_num_d(char *str);
int					check_line(char *line, char ch, int sum);

int					create_trgb(t_color color);
int					keys_hook(int key, t_scene *scene);
int					mouse_hook(int btn, int x, int y, t_scene *scene);
int					exit_hook(t_scene *scene);
int					camera_right(t_scene *scene);
int					camera_left(t_scene *scene);
int					camera_position_left(t_scene *scene);
int					camera_position_right(t_scene *scene);
int					camera_position_up(t_scene *scene);
int					camera_position_down(t_scene *scene);
int					camera_position_zoom_in(t_scene *scene);
int					camera_position_zoom_out(t_scene *scene);

void				rotate_camera(t_scene *scene, t_camera *camera,
					double x, double y);

t_vector			vector_add(t_vector v1, t_vector v2);
t_vector			vector_sub(t_vector v1, t_vector v2);
t_vector			vector_scale(double k, t_vector v);
double				vector_dot_product(t_vector v1, t_vector v2);
t_vector			vector_cross_product(t_vector v1, t_vector v2);
double				vector_length(t_vector v);
void				vector_normalize(t_vector *v);
t_vector			matrix_vector_product(t_matrix m, t_vector v);
int					vector_zero(t_vector vector);

void				show_scene(t_scene *scene);
int					bmp_header_file(t_scene *scene, int fd);
int					bmp_header_img(t_scene *scene, int fd);
int					bmp_scene(t_scene *scene, int fd);

int					intersect_sp(t_sphere *sp, t_ray *ray);
int					intersect_pl(t_plane *pl, t_ray *ray);
int					intersect_sq(t_square *sq, t_ray *ray);
int					intersect_tr(t_triangle *tr, t_ray *ray);
int					intersect_cy(t_cylinder *cy, t_ray *ray);

int					intersect_sphere(t_sphere *sphere, t_ray *ray);
int					intersect_plane(t_plane *plane, t_ray ray, double *dist);
int					intersect_square(t_square *sphere, t_ray ray, double *dist);
int					intersect_triangle(t_triangle *triangle, t_ray ray,
					double *dist);
int					intersect_cylinder(t_cylinder *cylinder, t_ray *ray,
					double *dist);

void				nearest_intersect(t_scene *scene, t_ray *ray);
int					shadow_intersect(t_scene *scene, t_ray *ray);

void				calc_lightning(t_scene *scene, t_ray *ray, t_vector normal,
					t_vector point);

t_vector			camera_ray(t_scene *scene, double x, double y);
t_vector			calc_matrix_vx(t_scene *scene, t_vector camera);

void				nearest_intersect(t_scene *scene, t_ray *ray);

t_color				color_ambient(t_scene *scene, t_color ray);
void				color_mix(t_color *color_base, t_color color);

void				memory_clean(t_scene *scene);
void				clear_arr(char **arr);
void				clear_rt_line(t_scene *scene);

#endif
