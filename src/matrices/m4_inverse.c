/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4_inverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 15:07:28 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 22:08:23 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	m4_is_invertible(t_m4 m4)
{
	if (fl_equal(m4_determinant(m4), 0))
		return (FALSE);
	dbg_write_code("Matrix found to NOT be invertible!\n", RED);
	return (TRUE);
}

t_m4	m4_inverse(t_m4 m4)
{
	t_m4		ret;
	t_cnv		i;
	float		det;
	int			size;

	dbg_write("Remeber to check m4_is_invertible()\n");
	size = 4;
	i = (t_cnv){0, 0};
	det = m4_determinant(m4);
	while (i.y < size)
	{
		ret.m[(int)i.y][(int)i.x] = m4_cofactor(m4, i) / det;
		i.x++;
		if (i.x >= size)
		{
			i.x = 0;
			i.y++;
		}
	}
	return (ret);
}

//cc -Wall -Wextra -Werror src/matrices/m4_inverse.c src/matrices/mx_equal.c
//	src/math/comparisson.c src/matrices/mx_print.c
//	src/matrices/m4_multiplication.c src/utils/ft_debug.c
//	src/matrices/mx_transpose.c src/matrices/determinant_3.c
//	src/matrices/determinant_42.c
//	-I./include include/libft/libft.a -o o && ./o ; rm -f o

/*int	main(void)
{
	t_m4	m4;
	t_m4	a;
	t_m4	b;

	m4 = (t_m4){{{-0.15385, -0.15385, -0.28205, -0.53846},
	{-0.07692, 0.12308, 0.02564, 0.03077},
	{0.35897, 0.35897, 0.43590, 0.92308},
	{-0.69231, -0.69231, -0.76923, -1.92308}}};
	if (!m4_is_invertible(m4))
		ft_printf("It CANNOT be inverted!\n");
	else
	{
		m4_print(m4);
		ft_printf("It will be inverted: \n");
		m4 = m4_inverse(m4);
		m4_print(m4);
	}
	write(1, "\n", 1);
	m4 = (t_m4){{{-0.04074, -0.07778, 0.14444, -0.22222},
	{-0.07778, 0.03333, 0.36667, -0.33333},
	{-0.02901, -0.14630, -0.10926, 0.12963},
	{0.17778, 0.06667, -0.26667, 0.33333}}};
	if (!m4_is_invertible(m4))
		ft_printf("It CANNOT be inverted!\n");
	else
	{
		m4_print(m4);
		ft_printf("It will be inverted: \n");
		m4 = m4_inverse(m4);
		m4_print(m4);
	}
	write(1, "\na:\n", 4);
	a = (t_m4){{{3, -9, 7, 3}, {3, -8, 2, -9}, {-4, 4, 4, 1}, {-6, 5, -1, 1}}};
	m4_print(a);
	write(1, "b:\n", 3);
	b = (t_m4){{{8, 2, 2, 2}, {3, -1, 7, 0}, {7, 0, 5, 4}, {6, -2, 0, 5}}};
	m4_print(b);
	write(1, "a * b:\n", 7);
	m4 = m4_multiplication(a, b);
	m4_print(m4);
	write(1, "inverse(b):\n", 12);
	a = m4_multiplication(m4, m4_inverse(b));
	m4_print(a);
}*/
