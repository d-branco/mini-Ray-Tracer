/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 09:06:28 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (DEBUG)
		finalize(&rt);
	mlx_put_image_to_window(rt.mlx, rt.mlx_win, rt.mlx_img, 0, 0);
	mlx_loop(rt.mlx);
	return (debug_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

/*
	debug_write("First pixel orientation calculation\n");
	if (debug_write(""))
		ft_printf("s_scene: c_orient: %i,%i,%i\n", (int) rt->c_ori.x,
			(int) rt->c_ori.y, (int) rt->c_ori.z);
	debug_write("Distance to camera plane \n");
	distance = (float)((WIDTH / 2) / sinf(rt->c_fov / 2));

	if (debug_write(""))
		ft_printf("distance to canvas plane: %i.%i pixeis\n",
			(int) distance, (((int)(distance * 10000)) % 10000));

	ori = (t_vector){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z};
	uni = vec_scalar_multiplication(distance, ori);
	if (debug_write(""))
		ft_printf("vector distance: %i,%i,%i\n", (int) uni.x,
			(int) uni.y, (int) uni.z);
*/

/*static void	mlx_playground(t_scene *rt)
{
	t_canvas	c;
	float		j;
	float		i;
	int			edge;

	edge = HEIGHT;
	if (WIDTH > HEIGHT)
		edge = WIDTH;
	debug_write("Drawing a yellow circle... ");
	while (edge >= 1)
	{
		color_screen(rt, encode_rgb(
				rt->a_rgb[0], rt->a_rgb[1], rt->a_rgb[2]));
		c = (t_canvas){0, 0};
		while (c.x < WIDTH)
		{
			c.y = 0;
			while (c.y < HEIGHT)
			{
				if (((powf(c.x - 225, 2)
							+ powf(c.y - 225, 2)))
					< pow(225, 2))
				{
					i = 0;
					while (i < edge)
					{
						j = 0;
						while (j < edge)
						{
							pixel_put(rt, (c.x + j), (c.y + i),
								encode_rgb(255, 255, 0));
							j++;
						}
						i++;
					}
				}
				c.y += edge;
			}
			c.x += edge;
		}
		mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
		if (DEBUG)
			ft_printf("%i, ", edge);
		edge /= 2;
	}
	if (DEBUG)
		write(STDOUT_FILENO, "done!\n", ft_strlen("done!\n"));
}*/
