/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:02:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/02 18:09:37 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/*typedef struct s_matrix4
{
	float					m[4][4];
}							t_matrix4;
typedef struct s_matrix3
{
	float					m[3][3];
}							t_matrix3;
typedef struct s_matrix2
{
	float					m[2][2];
}							t_matrix2;*/

//for a matrix size 4:
//matrix_print((float*)matrix_4x4, 4)
void	m4_print(t_matrix4 matrix)
{
	t_canvas	i;
	int			size;

	size = 4;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		dbg_write("");
		if (i.y == 0)
			ft_printf("|\t");
		ft_printf("% 4i", (int)matrix.m[i.x][i.y]);
		ft_printf("\t|\t");
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
			ft_printf("\n");
		}
	}
}

void	m3_print(t_matrix3 matrix)
{
	t_canvas	i;
	int			size;

	size = 3;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		dbg_write("");
		if (i.y == 0)
			ft_printf("|\t");
		ft_printf("% 4i", (int)matrix.m[i.x][i.y]);
		ft_printf("\t|\t");
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
			ft_printf("\n");
		}
	}
}

void	m2_print(t_matrix2 matrix)
{
	t_canvas	i;
	int			size;

	size = 2;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		dbg_write("");
		if (i.y == 0)
			ft_printf("|\t");
		ft_printf("% 4i", (int)matrix.m[i.x][i.y]);
		ft_printf("\t|\t");
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
			ft_printf("\n");
		}
	}
}

//m4 = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
//m4 = (t_matrix4){{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
//cc -Wall -Wextra -Werror -I./include src/math/matrix.c -o o && ./o ; rm -f o
/*int	main(void)
{
	t_matrix2	m2;
	t_matrix3	m3;
	t_matrix4	m4;

	m2 = (t_matrix2){{{1, 2}, {1, 1}}};
	m3 = (t_matrix3){{{1, 2, 3}, {1, 1, 0}, {1, 0, 1}}};
	m4 = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
	m2_print(m2);
	printf("\n");
	m3_print(m3);
	printf("\n");
	m4_print(m4);
}*/
