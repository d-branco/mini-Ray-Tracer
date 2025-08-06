/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 10:05:41 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	key_right_left(t_scene *rt, float translation);
static void	key_up_down(t_scene *rt, float translation);

int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write("ERROR: return from close_win_button()\n"), 0);
}

int	key_hook(int keycode, t_scene *rt)
{
	if (keycode == KEY_ESC)
		return (dbg_write("key ESC pressed. Closing\n"), finalize(rt), 0);
	else if (keycode == KEY_RIGHT)
		key_right_left(rt, 1.0f);
	else if (keycode == KEY_LEFT)
		key_right_left(rt, -1.0f);
	else if (keycode == KEY_UP)
		key_up_down(rt, 1.0f);
	else if (keycode == KEY_DOWN)
		key_up_down(rt, -1.0f);
	return (EXIT_SUCCESS);
}

static void	key_right_left(t_scene *rt, float translation)
{
	if (rt->key_pressed == TRUE)
		return ;
	if (translation > 0)
		dbg_write("key RIGHT pressed!\n");
	else
		dbg_write("key LEFT pressed!\n");
	rt->c_coord.x += translation;
	if (dbg_write("Camara: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) rt->c_coord.x,
			(int) rt->c_coord.y, (int) rt->c_coord.z);
	initialize_map(rt);
	rt->key_pressed = TRUE;
}

static void	key_up_down(t_scene *rt, float translation)
{
	if (rt->key_pressed == TRUE)
		return ;
	if (translation > 0)
		dbg_write("key UP pressed!\n");
	else
		dbg_write("key DOWN pressed!\n");
	rt->c_coord.y += translation;
	if (dbg_write("Camara: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) rt->c_coord.x,
			(int) rt->c_coord.y, (int) rt->c_coord.z);
	initialize_map(rt);
	rt->key_pressed = TRUE;
}
