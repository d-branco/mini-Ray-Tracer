/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 10:06:35 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 21:11:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_m2		m3_submatrix(t_m3 m3, t_canvas rm);
static float	m3_cofactor(t_m3 m3, t_canvas c);
//static float	m3_minor(t_m3 m3, t_canvas c);

float	m3_determinant(t_m3 m3)
{
	float	ret;

	ret = m3.m[0][0] * m3_cofactor(m3, (t_canvas){0, 0})
		+ m3.m[0][1] * m3_cofactor(m3, (t_canvas){0, 1})
		+ m3.m[0][2] * m3_cofactor(m3, (t_canvas){0, 2});
	return (ret);
}

static t_m2	m3_submatrix(t_m3 m3, t_canvas rm)
{
	t_m2		ret;
	t_canvas	i;
	t_canvas	offset;
	int			size;

	size = 3;
	i = (t_canvas){0, 0};
	offset = (t_canvas){0, 0};
	while (i.y < size - 1)
	{
		if (rm.x == i.x)
			offset.x = 1;
		if (rm.y == i.y)
			offset.y = 1;
		ret.m[(int)i.x][(int)i.y]
			= m3.m[(int)(i.x + offset.x)][(int)(i.y + offset.y)];
		i.x++;
		if (i.x >= size - 1)
		{
			i.x = 0;
			i.y++;
			offset.x = 0;
		}
	}
	return (ret);
}

static float	m3_cofactor(t_m3 m3, t_canvas c)
{
	float	ret;

	ret = m2_determinant(m3_submatrix(m3, c));
	if (((int)(c.x + c.y) % 2) == 1)
		ret = -ret;
	return (ret);
}

//	static float	m3_minor(t_m3 m3, t_canvas c)
//	{
//		return (m2_determinant(m3_submatrix(m3, c)));
//	}

//cc -Wall -Wextra -Werror src/matrices/mx_equal.c src/math/comparisson.c
//	src/matrices/mx_print.c src/matrices/m4_multiplication.c
//	src/utils/ft_debug.c src/matrices/mx_transpose.c src/matrices/determinant.c
//	-I./include include/libft/libft.a -o o && ./o ; rm -f o

/*int	main(void)
{
	t_m2	m2;
	t_m4	m4;
	t_m3	m3;

	m2 = (t_m2){{{1, 5}, {-3, 2}}};
	if ((fl_equal(17.0f, m2_determinant(m2))) == TRUE)
		ft_printf("Determinant:    Correct\n\n");
	else
		ft_printf("Determinant:    Incorrect\n\n");
	m4 = (t_m4){{{-6, 1, 1, 6}, {-8, 5, 8, 6}, {-1, 0, 8, 2}, {-7, 1, -1, 1}}};
	m3 = (t_m3){{{-6, 1, 6}, {-8, 8, 6}, {-7, -1, 1}}};
	if (m3_equal(m3, m4_submatrix(m4, (t_canvas){2, 1})))
		ft_printf("m4 submatrix:   Correct\n");
	else
		ft_printf("m4 submatrix:   Incorrect\n");
	m3 = (t_m3){{{1, 5, 0}, {-3, 2, 7}, {0, 6, -3}}};
	m2 = (t_m2){{{-3, 2}, {0, 6}}};
	if (m2_equal(m2, m3_submatrix(m3, (t_canvas){0, 2})))
		ft_printf("m3 submatrix:   Correct\n");
	else
		ft_printf("m3 submatrix:   Incorrect\n");
	m3 = (t_m3){{{3, 5, 0}, {2, -1, -7}, {6, -1, 5}}};
	if ((fl_equal(m2_determinant(m3_submatrix(m3, (t_canvas){1, 0})),
			m3_minor(m3, (t_canvas){1, 0})))
			&& (m3_minor(m3, (t_canvas){1, 0}) == 25.0f))
		ft_printf("m3 minor:       Correct\n");
	else
		ft_printf("m3 minor:       Incorrect\n");
	if ((m3_minor(m3, (t_canvas){0, 0}) == -12.f)
		&& (m3_cofactor(m3, (t_canvas){0, 0}) == -12.f))
		ft_printf("m3 cofactor 1:  Correct\n");
	else
		ft_printf("m3 cofactor 1:  Incorrect\n");
	if ((fl_equal(m3_minor(m3, (t_canvas){1, 0}), 25.f))
		&& (fl_equal(m3_cofactor(m3, (t_canvas){1, 0}), -25.f)))
		ft_printf("m3 cofactor 2:  Correct\n");
	else
		ft_printf("m3 cofactor 2:  Incorrect\n");
	m3 = (t_m3){{{1, 2, 6}, {-5, 8, -4}, {2, 6, 4}}};
	if (fl_equal(m3_cofactor(m3, (t_canvas){0, 0}), 56)
		&& fl_equal(m3_cofactor(m3, (t_canvas){0, 1}), 12)
		&& fl_equal(m3_cofactor(m3, (t_canvas){0, 2}), -46))
		ft_printf("m3 cofactor 3:  Correct\n");
	else
		ft_printf("m3 cofactor 3:  Incorrect\n");
	if (fl_equal(m3_determinant(m3), -196))
		ft_printf("m3 determinant: Correct\n\n");
	else
		ft_printf("m3 determinant: Incorrect\n\n");
	m4 = (t_m4){{{-2, -8, 3, 5}, {-3, 1, 7, 3}, {1, 2, -9, 6}, {-6, 7, 7, -9}}};
	if ((fl_equal(m4_cofactor(m4, (t_canvas){0, 0}), 690))
		&& (fl_equal(m4_cofactor(m4, (t_canvas){0, 1}), 447))
		&& (fl_equal(m4_cofactor(m4, (t_canvas){0, 2}), 210))
		&& (fl_equal(m4_cofactor(m4, (t_canvas){0, 3}), 51)))
		ft_printf("m4 cofactor 1:  Correct\n");
	else
		ft_printf("m4 cofactor 1:  Incorrect\n");
	if (fl_equal(m4_determinant(m4), -4071))
		ft_printf("m4 determinant: Correct\n");
	else
		ft_printf("m4 determinant: Incorrect\n");
}*/
