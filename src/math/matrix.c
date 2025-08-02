/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_make.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:02:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/02 14:21:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//for a matrix size 4:
//matrix_print((float*)matrix_4x4, 4)
void	matrix_print(float *matrix, int size)
{
	t_canvas	i;

	i = (t_canvas){0, 0};
	while (i.x < size)
	{
		dbg_write("");
		if (i.y == 0)
			ft_printf("|\t");
		ft_printf("% 4i", (int)matrix[i.x * size + i.y]);
		ft_printf("\t|\t");
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
}

/*int	main(void)
{
	float		m2[2][2];
	float		m3[3][3];
	float		m4[4][4];
	t_canvas	i;
	int			size;

	size = 2;
	i = (t_canvas){0,0};
	while (i.x < size)
	{
		m2[i.x][i.y] = (int)(i.x * i.y + 1);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	matrix_print((float*)m2, size);
	printf("\n");

	size = 3;
	i = (t_canvas){0,0};
	while (i.x < size)
	{
		m3[i.x][i.y] = (int)(i.x * i.y + 1);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	matrix_print((float*)m3, size);
	printf("\n");

	size = 4;
	i = (t_canvas){0,0};
	while (i.x < size)
	{
		m4[i.x][i.y] = (int)(i.x * i.y + 1);
		i.y++;
		if (i.y >= size)
		{
			i.y = 0;
			i.x++;
		}
	}
	matrix_print((float*)m4, size);
}*/
