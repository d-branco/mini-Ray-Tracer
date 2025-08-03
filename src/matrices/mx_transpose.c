/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_transpose.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 09:10:05 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/03 09:19:15 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//m4 = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
//m4 = (t_matrix4){{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
//cc -Wall -Wextra -Werror src/matrices/mx_equal.c src/math/comparisson.c
//	src/matrices/mx_print.c src/matrices/m4_multiplication.c
//	src/utils/ft_debug.c src/matrices/mx_transpose.c
//	-I./include include/libft/libft.a -o o && ./o ; rm -f o

t_matrix4	m4_transpose(t_matrix4 a)
{
	t_matrix4	ret;
	t_canvas	i;
	int			size;

	size = 4;
	i = (t_canvas){0, 0};
	while (i.y < size)
	{
		ret.m[i.x][i.y] = a.m[i.y][i.x];
		i.x++;
		if (i.x >= size)
		{
			i.x = 0;
			i.y++;
		}
	}
	return (ret);
}

t_matrix3	m3_transpose(t_matrix3 a)
{
	t_matrix3	ret;
	t_canvas	i;
	int			size;

	size = 3;
	i = (t_canvas){0, 0};
	while (i.y < size)
	{
		ret.m[i.x][i.y] = a.m[i.y][i.x];
		i.x++;
		if (i.x >= size)
		{
			i.x = 0;
			i.y++;
		}
	}
	return (ret);
}

t_matrix2	m2_transpose(t_matrix2 a)
{
	t_matrix2	ret;
	t_canvas	i;
	int			size;

	size = 2;
	i = (t_canvas){0, 0};
	while (i.y < size)
	{
		ret.m[i.x][i.y] = a.m[i.y][i.x];
		i.x++;
		if (i.x >= size)
		{
			i.x = 0;
			i.y++;
		}
	}
	return (ret);
}

/*int	main(void)
{
	t_matrix4	a;
	t_matrix3	b;
	t_matrix2	c;

	a = (t_matrix4){{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
	m4_print(a);
	write(STDOUT_FILENO, "\n", 1);
	a = m4_transpose(a);
	m4_print(a);
	write(STDOUT_FILENO, "\n", 1);
	b = (t_matrix3){{{-2, 1, 2}, {3, 2, 1}, {4, 3, 6}}};
	m3_print(b);
	write(STDOUT_FILENO, "\n", 1);
	b = m3_transpose(b);
	m3_print(b);
	write(STDOUT_FILENO, "\n", 1);
	c = (t_matrix2){{{1, 2}, {0, 4}}};
	m2_print(c);
	write(STDOUT_FILENO, "\n", 1);
	c = m2_transpose(c);
	m2_print(c);
}*/
