/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:10:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/10 13:30:10 by abessa-m         ###   ########.fr       */
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

//src/init/input_validation.c
int			input_validation(int argc, char **argv);
//src/utils
void		debug_write(char *str);
void		ft_free_n_null(void **ptr);
int			ft_isspace(char chr);
void		*ft_malloc(int total_size);
int			ft_strcmp(const char *s1, const char *s2);

#endif
