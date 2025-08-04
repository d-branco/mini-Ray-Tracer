/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/04 16:40:32 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write("ERROR: return from close_win_button()\n"), 0);
}

int	key_hook(int keycode, t_scene *rt)
{
	if (keycode == KEY_ESC)
		return (dbg_write("Closing by ESC key\n"), finalize(rt), EXIT_SUCCESS);
	else if (keycode == KEY_RIGHT)
	{
		dbg_write("key UP pressed!\n");
		rt->c_coord.x += 10;
		if (DEBUG)
			ft_printf("s_scene: c_coord: %3i,%3i,%3i\n", (int) rt->c_coord.x,
				(int) rt->c_coord.y, (int) rt->c_coord.z);
		rt->edge = MAP_RESOLUTION;
		initialize_map(rt);
		looping_loop(rt);
	}
	else if (keycode == KEY_LEFT)
	{
		dbg_write("key DOWN pressed!\n");
		rt->c_coord.x -= 10;
		if (DEBUG)
			ft_printf("s_scene: c_coord: %3i,%3i,%3i\n", (int) rt->c_coord.x,
				(int) rt->c_coord.y, (int) rt->c_coord.z);
		rt->edge = MAP_RESOLUTION;
		initialize_map(rt);
		looping_loop(rt);
	}
	else if (keycode == KEY_UP)
	{
		dbg_write("key UP pressed!\n");
		rt->c_coord.y += 10;
		if (DEBUG)
			ft_printf("s_scene: c_coord: %3i,%3i,%3i\n", (int) rt->c_coord.x,
				(int) rt->c_coord.y, (int) rt->c_coord.z);
		rt->edge = MAP_RESOLUTION;
		initialize_map(rt);
		looping_loop(rt);
	}
	else if (keycode == KEY_DOWN)
	{
		dbg_write("key DOWN pressed!\n");
		rt->c_coord.y -= 10;
		if (DEBUG)
			ft_printf("s_scene: c_coord: %3i,%3i,%3i\n", (int) rt->c_coord.x,
				(int) rt->c_coord.y, (int) rt->c_coord.z);
		rt->edge = MAP_RESOLUTION;
		initialize_map(rt);
		looping_loop(rt);
	}
	return (EXIT_SUCCESS);
}
