/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:10:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 20:37:49 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <math.h>
# include <fcntl.h>

# ifndef DEBUG
#  define DEBUG FALSE
# endif

# define TRUE				1
# define FALSE				0

typedef struct s_scene
{
	int						file_fd;
	float					amb_ratio;
	float					amb_rgb_range[3];
	float					cam_coord[3];
	float					cam_orientation[3];
	float					cam_fov;
	float					light_coord[3];
	float					light_brightness_ration;
	float					light_rgb_range[3];
	struct s_lst_obj		*lst_obj;
}							t_scene;

enum	e_obj
{
	e_SPHERE,
	e_PLANE,
	e_TRIANGLE
};

typedef struct s_lst_obj
{
	int						identifier;
	float					center[3];
	float					diameter;
	int						rgb_range[3];
	float					vec_uni[3];
	float					height;
	struct s_lst_obj		*next;
}							t_lst_obj;

//src/init/initialize.c
void		initialize(t_scene *rt, char **argv);
//src/init/finalize.c
void		finalize(t_scene *rt);
//src/init/parse.c
int			parse_input(t_scene *rt, char **argv);
char		*skip_to_next_word(char *line);
char		*skip_to_after_comma(char *line);
//src/init/parse_light_cam.c
int			parse_lights_and_camera(char *line, t_scene **rt);
//src/init/input_validation.c
int			input_validation(int argc, char **argv);
//src/utils
float		ft_atof(const char *str);
void		debug_write(char *str);
void		ft_free_n_null(void **ptr);
int			ft_isfloat(const char *str);
int			ft_isspace(char chr);
void		*ft_malloc(int total_size);
int			ft_strcmp(const char *s1, const char *s2);
int			is_float_triplet(char *str);

#endif
