/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 16:36:58 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	rt;

	if ((debug_write("Hello, friend\n")) && (input_validation(argc, argv) != 0))
		return (debug_write("Goodbye, friend\n"), 2);
	initialize_scene(&rt, argv);
	rt.mlx = mlx_init();
	if (debug_write("Pointer to mlx: "))
		ft_printf("%p\n", rt.mlx);
	debug_write("Initiating miniLibX\n");
	rt.mlx_win = mlx_new_window(rt.mlx, 192, (108 - 4), "miniRT");
	mlx_hook(rt.mlx_win, 17, 0, close_win_button, &rt);
	mlx_hook(rt.mlx_win, 2, 1L << 0, key_hook, &rt);
	mlx_loop(rt.mlx);
	return (debug_write("ERROR: return from main()\n"), EXIT_FAILURE);
}
