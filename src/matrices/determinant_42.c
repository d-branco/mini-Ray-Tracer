/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant_42.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 14:44:47 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 21:12:10 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_m3		m4_submatrix(t_m4 m4, t_canvas rm);

float	m4_determinant(t_m4 m4)
{
	float	ret;

	ret = m4.m[0][0] * m4_cofactor(m4, (t_canvas){0, 0})
		+ m4.m[0][1] * m4_cofactor(m4, (t_canvas){0, 1})
		+ m4.m[0][2] * m4_cofactor(m4, (t_canvas){0, 2})
		+ m4.m[0][3] * m4_cofactor(m4, (t_canvas){0, 3});
	return (ret);
}

float	m2_determinant(t_m2 m2)
{
	return (m2.m[0][0] * m2.m[1][1] - m2.m[0][1] * m2.m[1][0]);
}

float	m4_cofactor(t_m4 m4, t_canvas c)
{
	float	ret;

	ret = m3_determinant(m4_submatrix(m4, c));
	if (((int)(c.x + c.y) % 2) == 1)
		ret = -ret;
	return (ret);
}

static t_m3	m4_submatrix(t_m4 m4, t_canvas rm)
{
	t_m3		ret;
	t_canvas	i;
	t_canvas	offset;
	int			size;

	size = 4;
	i = (t_canvas){0, 0};
	offset = (t_canvas){0, 0};
	while (i.y < size - 1)
	{
		if (rm.x == i.x)
			offset.x = 1;
		if (rm.y == i.y)
			offset.y = 1;
		ret.m[(int)i.x][(int)i.y]
			= m4.m[(int)(i.x + offset.x)][(int)(i.y + offset.y)];
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
