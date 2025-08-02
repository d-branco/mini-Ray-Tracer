/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mx_equal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 18:13:28 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/02 18:31:54 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	m4_equal(t_matrix4 a, t_matrix4 b)
{
	int			size;
	t_canvas	i;

	size = 4;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		if (!fl_equal(a.m[i.x][i.y], b.m[i.x][i.y]))
			return (FALSE);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	return (TRUE);
}

int	m3_equal(t_matrix3 a, t_matrix3 b)
{
	int			size;
	t_canvas	i;

	size = 3;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		if (!fl_equal(a.m[i.x][i.y], b.m[i.x][i.y]))
			return (FALSE);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	return (TRUE);
}

int	m2_equal(t_matrix2 a, t_matrix2 b)
{
	int			size;
	t_canvas	i;

	size = 2;
	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		if (!fl_equal(a.m[i.x][i.y], b.m[i.x][i.y]))
			return (FALSE);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	return (TRUE);
}

//cc -Wall -Wextra -Werror -I./include
//	src/matrixes/mx_equal.c src/math/comparisson.c -o o && ./o ; rm -f o
/*int	main(void)
{
	t_matrix4	a;
	t_matrix4	b;
	t_matrix3	c;
	t_matrix3	d;
	t_matrix2	e;
	t_matrix2	f;

	a = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
	b = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
	if ((m4_equal(a, b)) == TRUE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
	b = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 2, 1, 0}, {1, 0, 0, 1}}};
	if ((m4_equal(a, b)) == FALSE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
	c = (t_matrix3){{{1, 2, 3}, {1, 1, 0}, {1, 0, 1}}};
	d = (t_matrix3){{{1, 2, 3}, {1, 1, 0}, {1, 0, 1}}};
	if ((m3_equal(c, d)) == TRUE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
	d = (t_matrix3){{{1, 2, 3}, {1, 1, 0}, {1, 2, 1}}};
	if ((m3_equal(c, d)) == FALSE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
	e = (t_matrix2){{{1, 2}, {1, 1}}};
	f = (t_matrix2){{{1, 2}, {1, 1}}};
	if ((m2_equal(e, f)) == TRUE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
	f = (t_matrix2){{{1, 2}, {1, 2}}};
	if ((m2_equal(e, f)) == FALSE)
		write(1, "Correct\n", 8);
	else
		write(1, "Incorrect\n", 10);
}*/
