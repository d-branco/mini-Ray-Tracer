/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4_multiplication.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 07:35:01 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/03 09:12:14 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//m4 = (t_matrix4){{{1, 2, 3, 4}, {1, 1, 0, 0}, {1, 0, 1, 0}, {1, 0, 0, 1}}};
//m4 = (t_matrix4){{{1, 0, 0, 0}, {0, 1, 0, 0}, {0, 0, 1, 0}, {0, 0, 0, 1}}};
//cc -Wall -Wextra -Werror src/matrices/mx_equal.c src/math/comparisson.c
//	src/matrices/mx_print.c src/matrices/m4_multiplication.c
//	src/utils/ft_debug.c -I./include include/libft/libft.a -o o && ./o ; rm -f o

t_matrix4	m4_multiplication(t_matrix4 a, t_matrix4 b)
{
	t_matrix4	ret;
	t_canvas	i;
	int			size;

	size = 4;
	i = (t_canvas){0, 0};
	while (i.y < size)
	{
		ret.m[i.x][i.y] = a.m[i.x][0] * b.m[0][i.y] + a.m[i.x][1] * b.m[1][i.y]
			+ a.m[i.x][2] * b.m[2][i.y] + a.m[i.x][3] * b.m[3][i.y];
		i.x++;
		if (i.x >= size)
		{
			i.x = 0;
			i.y++;
		}
	}
	return (ret);
}

t_tuple	m4_tuple_multiplication(t_matrix4 m, t_tuple t)
{
	t_tuple	ret;

	ret.x = m.m[0][0] * t.x + m.m[0][1] * t.y + m.m[0][2] * t.z
		+ m.m[0][3] * t.w;
	ret.y = m.m[1][0] * t.x + m.m[1][1] * t.y + m.m[1][2] * t.z
		+ m.m[1][3] * t.w;
	ret.z = m.m[2][0] * t.x + m.m[2][1] * t.y + m.m[2][2] * t.z
		+ m.m[2][3] * t.w;
	ret.w = m.m[3][0] * t.x + m.m[3][1] * t.y + m.m[3][2] * t.z
		+ m.m[3][3] * t.w;
	return (ret);
}

/*int	main(void)
{
	t_matrix4	a;
	t_matrix4	b;
	t_tuple		t;

	a = (t_matrix4){{{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 8, 7, 6}, {5, 4, 3, 2}}};
	b = (t_matrix4){{{-2, 1, 2, 3}, {3, 2, 1, -1}, {4, 3, 6, 5}, {1, 2, 7, 8}}};
	m4_print(a);
	printf("times\n");
	m4_print(b);
	printf("equals\n");
	a = m4_multiplication(a, b);
	m4_print(a);
	printf("\n\n");
	a = (t_matrix4){{{1, 2, 3, 4}, {2, 4, 4, 2}, {8, 6, 4, 1}, {0, 0, 0, 1}}};
	t = (t_tuple){1, 2, 3, 1};
	m4_print(a);
	printf("tuple: {%i, %i, %i, %i}\n", (int)t.x, (int)t.y, (int)t.z, (int)t.w);
	t = m4_tuple_multiplication(a, t);
	printf("tuple: {%i, %i, %i, %i}\n", (int)t.x, (int)t.y, (int)t.z, (int)t.w);
}*/
