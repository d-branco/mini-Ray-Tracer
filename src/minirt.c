/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/24 06:57:16 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int			mlx_initialize(t_scene *rt);

static void	mlx_playground(t_scene *rt);

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
	mlx_playground(&rt);
	mlx_put_image_to_window(rt.mlx, rt.mlx_win, rt.mlx_img, 0, 0);
	mlx_loop(rt.mlx);
	return (debug_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

int	mlx_initialize(t_scene *rt)
{
	rt->mlx_win = mlx_new_window(rt->mlx, WIDTH, HEIGHT, "miniRT");
	rt->mlx_img = mlx_new_image(rt->mlx, WIDTH, HEIGHT);
	rt->mlx_addr = mlx_get_data_addr(
			rt->mlx_img, &rt->bits_per_pixel, &rt->line_length, &rt->endian);
	if (!rt->mlx_win || !rt->mlx_img || !rt->mlx_addr)
		return (finalize(rt), debug_write("ERROR: mlx pointer\n"), 1);
	return (EXIT_SUCCESS);
}

static void	mlx_playground(t_scene *rt)
{
	t_point		origin;
	t_canvas	c;

	(void) origin;
	origin = (t_point){rt->cam_coord[0], rt->cam_coord[1], rt->cam_coord[2]};
	debug_write("Setting the screen black\n");
	color_screen(rt, encode_rgb(0, 0, 0));
	debug_write("Painting a white dot at (0, 0)\n");
	pixel_put(rt, 0, 0, encode_rgb(225, 42, 42));
	debug_write("Drawing a yellow circle...");
	c = (t_canvas){0, 0};
	while (c.x < WIDTH)
	{
		c.y = 0;
		while (c.y < HEIGHT)
		{
			if (((powf(c.x - (WIDTH / 2), 2)
						+ powf(c.y - (HEIGHT / 2), 2)))
				< pow(42, 2))
				pixel_put(rt, c.x, c.y, encode_rgb(255, 255, 0));
			c.y++;
		}
		c.x++;
	}
	write(STDOUT_FILENO, "done!\n", ft_strlen("done!\n"));
}
