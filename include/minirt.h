/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:10:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/10 19:00:28 by abessa-m         ###   ########.fr       */
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

# define WIDTH				960
# define HEIGHT				1010

# define MAP_RESOLUTION		128
# define POINT_AFTER_POINT	FALSE

# define TRUE				1
# define FALSE				0
# define UNSET				-1

# define PI					3.14159265358979323846264338328f
# define TAU				6.28318530717958647692528676656f
# define EPSILON			0.000042f
# define MAX_FLOAT			340282346638528859811704183484516925440.0f

# define POINT				1
# define VECTOR				0

# define PURPLE				"\033[35m"
# define GRAY				"\033[30m"
# define YELLOW				"\033[93m"
# define BLUE				"\033[36m"
# define RED				"\033[31m"

# define KEY_ESC			65307

# define KEY_LEFT			65361
# define KEY_UP				65362
# define KEY_RIGHT			65363
# define KEY_DOWN			65364

# define KEY_C				99
# define KEY_A				97
# define KEY_L				108

typedef struct s_rgb
{
	float					r;
	float					g;
	float					b;
}							t_rgb;

typedef struct s_tuple
{
	float					x;
	float					y;
	float					z;
	float					w;
}							t_tuple;

typedef struct s_scene
{
	int						file_fd;
	float					a_ratio;
	struct s_rgb			a_rgb;
	struct s_tuple			c_coord;
	struct s_tuple			c_dir;
	float					c_fov;
	struct s_tuple			l_coo;
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
	int						edge;
	int						key_pressed;
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
	struct s_tuple			center;
	float					diameter;
	struct s_rgb			rgb_rng;
	struct s_tuple			vec_uni;
	float					height;
	struct s_tuple			xs_pnt;
	struct s_lst_obj		*next;
}							t_lst_obj;

//intersection list
typedef struct s_lst_xs
{
	float					dst;
	t_lst_obj				*obj;
	struct s_lst_xs			*next;
}							t_lst_xs;

typedef struct s_canvas
{
	float						x;
	float						y;
}							t_cnv;

typedef struct s_ray
{
	t_tuple					origin;
	t_tuple					direction;
}							t_ray;

//src/init/finalize.c
void		finalize(t_scene *rt);
//src/init/initialize.c
int			initialize_scene(t_scene *rt, char **argv);
void		initialize_map(t_scene *rt);
void		debug_print_s_scene(t_scene *rt);
void		print_obj_list(t_lst_obj **head);
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
void		parse_float_vector(char *line, t_tuple *array);
void		parse_float_point(char *line, t_tuple *array);
//src/init/parse.c
int			parse_input(t_scene *rt, char **argv);

//src/canvas/looping_loop.c
int			looping_loop(t_scene *rt);
//src/canvas/color.c
int			pix_smooth16(t_scene *rt, t_cnv *c);
int			get_color(t_scene *rt, t_lst_obj *obj);
int			rgb_merge(int rgb1, int rgb2);

//src/math/addiction.c
t_tuple		vec_addiction(t_tuple a, t_tuple b);
t_tuple		vec_subtraction(t_tuple a, t_tuple b);
t_tuple		pnt_subtr_to_vec(t_tuple a, t_tuple b);
//src/math/comparisson.c
int			fl_equal(float a, float b);
int			tuple_equal(t_tuple a, t_tuple b);
//src/math/intersection_plane.c
int			pl_intersect(
				t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *pl);
int			smll_dst_to_plane(
				t_scene *rt, t_tuple dir, t_lst_obj *pl, float *dst);
//src/math/intersection_sphere.c
int			sp_intersect(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *sp);
int			smll_dst_to_sphere(
				t_scene *rt, t_tuple dir, t_lst_obj *sp, float *dst);
//src/math/intersections.c
int			check_obj_xs(t_scene *rt, t_tuple pnt, t_tuple dir);
t_lst_obj	*get_xs(t_scene *rt, t_cnv coo);
//src/math/rays.c
t_ray		make_ray(t_tuple origin, t_tuple direction);
t_tuple		ray_position(t_ray r, float dst);
t_tuple		get_ray_direction(t_scene *rt, t_cnv coo);
//src/math/scalar_multiplication.c
t_tuple		vec_negation(t_tuple v);
t_tuple		vec_scalar_multiplication(float s, t_tuple v);
//src/math/tuples.c
t_tuple		mk_pnt(float x, float y, float z);
t_tuple		mk_vec(float x, float y, float z);
int			pt_equal(t_tuple a, t_tuple b);
int			vc_equal(t_tuple a, t_tuple b);
void		tuple_print(t_tuple data);
//src/math/vector_math.c
float		vec_magnitude(t_tuple v);
t_tuple		vec_norm(t_tuple v);
float		vec_inner_product(t_tuple a, t_tuple b);
t_tuple		vec_cross_product(t_tuple a, t_tuple b);

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
int			dbg_write(char *str);
int			dbg_write_code(char *str, const char *code);
void		ft_free_n_null(void **ptr);
int			ft_isfloat(const char *str);
int			ft_isspace(char chr);
void		*ft_malloc(int total_size);
int			ft_strcmp(const char *s1, const char *s2);
int			is_float_triplet(char *str);
void		rt_lstadd_back(t_lst_obj **lst, t_lst_obj *new);

//temp
void		temp_testing(t_scene *rt);

#endif
