/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/21 14:53:37 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	mlx_initialize(t_scene *rt);

int	main(int argc, char **argv)
{
	t_scene	rt;

	if ((debug_write("Hello, friend\n")) && (input_validation(argc, argv) != 0))
		return (debug_write("Goodbye, friend\n"), 2);
	if (initialize_scene(&rt, argv) != EXIT_SUCCESS)
		return (finalize(&rt), debug_write("Goodbye, friend\n"), 3);
	rt.mlx = mlx_init();
	if (debug_write("Pointer to mlx: "))
		ft_printf("%p\n", rt.mlx);
	debug_write("Initiating miniLibX\n");
	if (mlx_initialize(&rt) != EXIT_SUCCESS)
		return (debug_write("Goodbye, friend\n"), 4);

	mlx_hook(rt.mlx_win, 17, 0, close_win_button, &rt);
	mlx_hook(rt.mlx_win, 2, 1L << 0, key_hook, &rt);
	mlx_loop(rt.mlx);
	return (debug_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

/* from fdf
int	mlx_initialize(t_scene *rt)
{
	rt->mlx_win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, "miniRT");
	rt->mlx_img = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	if (!rt->mlx_win || !rt->mlx_img)
		return (finalize(&rt), debug_write("ERROR: mlx pointer\n"), 1);
	rt->mlx_addr = mlx_get_data_addr(
			rt->mlx_img, &rt->bits_per_pixel, &rt->line_length, &rt->endian);
}

void	our_pixel_put(t_scene *rt, int x, int y, int color)
{
	int	offset;

	if ((x < 0) || (WIDTH) || (y < 0) | (HEIGHT))
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
			our_pixel_put(rt, x, y, color);
			x++;
		}
		y++;
	}
}*/