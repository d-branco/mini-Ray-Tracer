/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:10:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:22:03 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "libft/libft.h"
# include "minilibx-linux/mlx.h"
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

# ifndef DEBUG
#  define DEBUG FALSE
# endif

//# define WIDTH (1920 / 2)
//# define HEIGHT (1080 - 40)
//# define HEIGHT (1080 - 40 - 30)
//# define WIDTH				960
//# define HEIGHT				1010
# define WIDTH 960
# define HEIGHT 1010

# define TRUE				1
# define FALSE				0

# define PI					3.14159265358979323846264338328
# define TAU				6.28318530717958647692528676656

// Margin Of Error
# define MOE				0.000042

typedef struct s_rgb
{
	float					r;
	float					g;
	float					b;
}							t_rgb;

typedef struct s_vector
{
	float					x;
	float					y;
	float					z;
}							t_vector;

typedef struct s_point
{
	float					x;
	float					y;
	float					z;
}							t_point;

typedef struct s_scene
{
	int						file_fd;
	float					a_ratio;
	struct s_rgb			a_rgb;
	struct s_point			c_coord;
	struct s_vector			c_ori;
	float					c_fov;
	struct s_point			l_coo;
	float					l_bri;
	struct s_rgb			l_rgb;
	struct s_lst_obj		*lst_obj;
	void					*mlx;
	void					*mlx_win;
	void					*mlx_img;
	void					*mlx_addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
	int						map[WIDTH][HEIGHT];
}							t_scene;

enum	e_obj
{
	e_SPHERE,
	e_PLANE,
	e_CYlINDER
};

typedef struct s_lst_obj
{
	int						id;
	struct s_point			center;
	float					diameter;
	struct s_rgb			rgb_rng;
	struct s_vector			vec_uni;
	float					height;
	struct s_lst_obj		*next;
}							t_lst_obj;

typedef struct s_canvas
{
	int						x;
	int						y;
}							t_canvas;

typedef struct s_canvasf
{
	float					x;
	float					y;
}							t_canvasf;

//src/init/finalize.c
void		finalize(t_scene *rt);
//src/init/initialize.c
int			initialize_scene(t_scene *rt, char **argv);
//src/init/input_validation.c
int			input_validation(int argc, char **argv);
//src/init/parse_light_cam.c
int			parse_lights_and_camera(char *line, t_scene *rt);
//src/init/parse_objects.c
int			parse_objects(char *line, t_scene *rt);
//src/init/parse_utils.c
int			validate_object_parsing(t_lst_obj *obj);
char		*skip_to_next_word(char *line);
char		*skip_to_after_comma(char *line);
void		parse_float_vector(char *line, t_vector *array);
void		parse_float_point(char *line, t_point *array);
//src/init/parse.c
int			parse_input(t_scene *rt, char **argv);

//src/canvas/looping_loop.c
void		looping_loop(t_scene *rt);
//src/math/addiction.c
t_vector	vec_addiction(t_vector a, t_vector b);
t_vector	vec_subtraction(t_vector a, t_vector b);
//src/math/comparisson.c
int			fl_equal(float a, float b);
//src/math/intersection_sphere.c
int			smll_dst_to_sphere(
				t_scene *rt, t_vector dir, t_lst_obj *sp, float *dst);
//src/math/ray.c
t_vector	get_ray_direction(t_scene *rt, t_canvas coo);
//src/math/scalar_multiplication.c
t_vector	vec_negation(t_vector v);
t_vector	vec_scalar_multiplication(float s, t_vector v);
//src/math/vector_math.c
float		vec_magnitude(t_vector v);
t_vector	vec_normalization(t_vector v);
float		vec_inner_product(t_vector a, t_vector b);
t_vector	vec_cross_product(t_vector a, t_vector b);

//src/mlx/colors.c
void		parse_float_rgb(char *line, t_rgb *array);
void		pixel_put(t_scene *rt, int x, int y, int color);
int			encode_rgb(
				unsigned char red, unsigned char green, unsigned char blue);
void		color_screen(t_scene *rt, int color);
//src/mlx/hooks.c
int			close_win_button(t_scene *rt);
int			key_hook(int keycode, t_scene *rt);
//src/mlx/mlx_init.c
int			mlx_initialize(t_scene *rt);

//src/utils
char		*append_chr(char *str, char c);
float		ft_atof(const char *str);
int			debug_write(char *str);
void		ft_free_n_null(void **ptr);
int			ft_isfloat(const char *str);
int			ft_isspace(char chr);
void		*ft_malloc(int total_size);
int			ft_strcmp(const char *s1, const char *s2);
int			is_float_triplet(char *str);
void		rt_lstadd_back(t_lst_obj **lst, t_lst_obj *new);

#endif
