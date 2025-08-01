/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 19:44:56 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		mlx_playground(t_scene *rt);

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
	looping_loop(&rt);
	if (DEBUG)
		finalize(&rt);
	mlx_put_image_to_window(rt.mlx, rt.mlx_win, rt.mlx_img, 0, 0);
	mlx_loop(rt.mlx);
	return (debug_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

static void	mlx_playground(t_scene *rt)
{
	t_vector	v;

	v = get_ray_direction(rt, (t_canvas){0, 0});
	if (debug_write("vector: top-left corner: "))
		printf("(%f, %f, %f)\n", v.x, v.y, v.z);
	v = get_ray_direction(rt, (t_canvas){(WIDTH - 1), 0});
	if (debug_write("vector: top-right corner: "))
		printf("(%f, %f, %f)\n", v.x, v.y, v.z);
	v = get_ray_direction(rt, (t_canvas){(WIDTH - 1), (HEIGHT - 1)});
	if (debug_write("vector: bottom-right corner: "))
		printf("(%f, %f, %f)\n", v.x, v.y, v.z);
	v = get_ray_direction(rt, (t_canvas){WIDTH / 2, HEIGHT / 2});
	if (debug_write("vector: center pixel: "))
		printf("(%f, %f, %f)\n", v.x, v.y, v.z);
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
