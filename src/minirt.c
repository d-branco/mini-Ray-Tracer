/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 11:54:25 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	rt;

	if ((debug_write("Hello, friend\n")) && (input_validation(argc, argv) != 0))
		return (debug_write("Goodbye, friend\n"), 2);
	initialize(&rt, argv);
	if (debug_write("Pointer to mlx: "))
		ft_printf("%p\n", rt.mlx);
	rt.mlx = mlx_init();
	if (debug_write("Pointer to mlx: "))
		ft_printf("%p\n", rt.mlx);
	mlx_new_window(rt.mlx, 1920, (1080 - 40), "miniRT");
	mlx_loop(rt.mlx);
	finalize(&rt);
	return (debug_write("Goodbye, friend\n"), EXIT_SUCCESS);
}
