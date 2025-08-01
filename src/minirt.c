/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 12:11:38 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		mlx_playground(t_scene *rt);
static t_vector	get_ray_direction(t_scene *rt, t_canvas coo);

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

static t_vector	get_ray_direction(t_scene *rt, t_canvas coo)
{
	t_vector	right;
	t_vector	up;
	t_canvasf	viewport;
	t_canvasf	v;
	t_vector	ray_dir;

	ray_dir = (t_vector){0, 1, 0};
	if (((rt->c_ori.y) > 0.9f) || ((rt->c_ori.y) < -0.9f))
		ray_dir = (t_vector){0, 0, -1};
	right = vec_normalization(vec_cross_product(
				(t_vector){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z}, ray_dir));
	up = vec_normalization(vec_cross_product(
				right, (t_vector){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z}));
	viewport.x = 2.0 * tan(rt->c_fov / 2.0);
	viewport.y = viewport.x * ((float)HEIGHT / (float)WIDTH);
	v.x = ((2.0f * coo.x / (WIDTH - 1)) - 1.0f) * (viewport.x / 2.0f);
	v.y = ((2.0f * coo.y / (HEIGHT - 1)) - 1.0f) * (viewport.y / 2.0f);
	ray_dir.x = rt->c_ori.x + (right.x * v.x) + (up.x * v.y);
	ray_dir.y = rt->c_ori.y + (right.y * v.x) + (up.y * v.y);
	ray_dir.z = rt->c_ori.z + (right.z * v.x) + (up.z * v.y);
	return (vec_normalization(ray_dir));
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
