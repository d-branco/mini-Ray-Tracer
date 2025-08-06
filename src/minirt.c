/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/05 21:32:47 by abessa-m         ###   ########.fr       */
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
	mlx_hook(rt.mlx_win, 17, 0, close_win_button, &rt);
	mlx_hook(rt.mlx_win, 2, 1L << 0, key_hook, &rt);
	temp_testing(&rt);
	mlx_loop_hook(rt.mlx, &old_looping_loop, &rt);
	mlx_loop(rt.mlx);
	return (dbg_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

void	temp_testing(t_scene *rt)
{
	(void) rt;
}
