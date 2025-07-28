/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 18:19:53 by abessa-m         ###   ########.fr       */
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
	t_vector	direction;

	(void) origin;
	(void) direction;
	origin = (t_point){rt->c_coord[0], rt->c_coord[1], rt->c_coord[2]};
	direction = (t_vector){rt->c_orient[0], rt->c_orient[1], rt->c_orient[2]};
	if (fl_equal(cosf(TAU), 1.0))
		debug_write("We have radians\n");
}

/*static void	mlx_playground(t_scene *rt)
{
	t_canvas	c;
	float		j;
	float		i;
	int			pixel_edge;

	pixel_edge = HEIGHT;
	if (WIDTH < HEIGHT)
		pixel_edge = WIDTH;
	debug_write("Drawing a yellow circle...");
	while (pixel_edge >= 1)
	{
		color_screen(rt, encode_rgb(
				rt->amb_rgb_rng[0], rt->amb_rgb_rng[1], rt->amb_rgb_rng[2]));
		c = (t_canvas){0, 0};
		while (c.x < WIDTH)
		{
			c.y = 0;
			while (c.y < HEIGHT)
			{
				if (((powf(c.x, 2)
							+ powf(c.y, 2)))
					< pow(225, 2))
				{
					i = 0;
					while (i < pixel_edge)
					{
						j = 0;
						while (j < pixel_edge)
						{
							pixel_put(rt, (c.x + j), (c.y + i),
								encode_rgb(255, 255, 0));
							j++;
						}
						i++;
					}
				}
				c.y += pixel_edge;
			}
			c.x += pixel_edge;
		}
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
		pixel_edge /= 2;
	}
	if (DEBUG)
		write(STDOUT_FILENO, "done!\n", ft_strlen("done!\n"));
}*/
