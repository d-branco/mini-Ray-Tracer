/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 08:56:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 08:56:50 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mlx_initialize(t_scene *rt)
{
	rt->mlx_win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, "miniRT");
	rt->mlx_img = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	rt->mlx_addr = mlx_get_data_addr(
			rt->mlx_img, &rt->bits_per_pixel, &rt->line_length, &rt->endian);
	if (!rt->mlx_win || !rt->mlx_img || !rt->mlx_addr)
		return (finalize(rt), dbg_write_code("ERROR: mlx pointer\n", RED), 1);
	return (EXIT_SUCCESS);
}
