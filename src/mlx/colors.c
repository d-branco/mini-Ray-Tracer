/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 13:28:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 08:49:12 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_float_rgb(char *line, t_rgb *array)
{
	array->r = ft_atof(line);
	line = skip_to_after_comma(line);
	array->g = ft_atof(line);
	line = skip_to_after_comma(line);
	array->b = ft_atof(line);
}

void	pixel_put(t_scene *rt, int x, int y, int color)
{
	int	offset;

	if ((x < 0) || (x >= WIDTH) || (y < 0) | (y >= HEIGHT))
		return ;
	offset = (rt->line_length * y) + (x * (rt->bits_per_pixel / 8));
	*((unsigned int *)(rt->mlx_addr + offset)) = color;
}

int	encode_rgb(unsigned char red, unsigned char green, unsigned char blue)
{
	return (red << 16 | green << 8 | blue);
}

void	color_screen(t_scene *rt, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			pixel_put(rt, x, y, color);
			x++;
		}
		y++;
	}
}
