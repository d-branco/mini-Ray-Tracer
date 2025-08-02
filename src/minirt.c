/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/02 17:32:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	rt;

	dbg_write("Hello, friend\n");
	if (input_validation(argc, argv) != 0)
		return (dbg_write("Goodbye, friend\n"), 2);
	if (initialize_scene(&rt, argv) != EXIT_SUCCESS)
		return (finalize(&rt), dbg_write("Goodbye, friend\n"), 3);
	rt.mlx = mlx_init();
	if (dbg_write("Pointer to mlx: "))
		ft_printf("%p\n", rt.mlx);
	dbg_write_code("Initiating miniLibX\n", PURPLE);
	if (mlx_initialize(&rt) != EXIT_SUCCESS)
		return (dbg_write("Goodbye, friend\n"), 4);
	mlx_hook(rt.mlx_win, 17, 0, close_win_button, &rt);
	mlx_hook(rt.mlx_win, 2, 1L << 0, key_hook, &rt);
	looping_loop(&rt);
	if (DEBUG)
		finalize(&rt);
	mlx_put_image_to_window(rt.mlx, rt.mlx_win, rt.mlx_img, 0, 0);
	mlx_loop(rt.mlx);
	return (dbg_write("ERROR: return from main()\n"), EXIT_FAILURE);
}
