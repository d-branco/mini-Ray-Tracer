/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 08:50:17 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

static int	handle_camera_keys(int keycode, t_scene *rt)
{
	if (keycode == KEY_RIGHT)
		key_right_left(rt, 1.0f);
	else if (keycode == KEY_LEFT)
		key_right_left(rt, -1.0f);
	else if (keycode == KEY_UP)
		key_up_down(rt, 1.0f);
	else if (keycode == KEY_DOWN)
		key_up_down(rt, -1.0f);
	else if (keycode == KEY_R)
		rotate_camera(rt, 'x', 10.0f);
	else if (keycode == KEY_T)
		rotate_camera(rt, 'x', -10.0f);
	else if (keycode == KEY_F)
		rotate_camera(rt, 'y', 10.0f);
	else if (keycode == KEY_G)
		rotate_camera(rt, 'y', -10.0f);
	else if (keycode == KEY_V)
		rotate_camera(rt, 'z', 10.0f);
	else if (keycode == KEY_B)
		rotate_camera(rt, 'z', -10.0f);
	return (EXIT_SUCCESS);
}

static int	handle_light_keys(int keycode, t_scene *rt)
{
	if (keycode == KEY_W)
		move_light(rt, 0, 1, 0);
	else if (keycode == KEY_S)
		move_light(rt, 0, -1, 0);
	else if (keycode == KEY_A)
		move_light(rt, -1, 0, 0);
	else if (keycode == KEY_D)
		move_light(rt, 1, 0, 0);
	else if (keycode == KEY_Q)
		move_light(rt, 0, 0, 1);
	else if (keycode == KEY_E)
		move_light(rt, 0, 0, -1);
	return (EXIT_SUCCESS);
}

static int	handle_object_keys(int keycode, t_scene *rt)
{
	if (keycode == KEY_W)
		move_selected_object(rt, 0, 1, 0);
	else if (keycode == KEY_S)
		move_selected_object(rt, 0, -1, 0);
	else if (keycode == KEY_A)
		move_selected_object(rt, 1, 0, 0);
	else if (keycode == KEY_D)
		move_selected_object(rt, -1, 0, 0);
	else if (keycode == KEY_Q)
		move_selected_object(rt, 0, 0, 1);
	else if (keycode == KEY_E)
		move_selected_object(rt, 0, 0, -1);
	else if (keycode == KEY_R)
		rotate_selected_object(rt, 'x', 10.0f);
	else if (keycode == KEY_T)
		rotate_selected_object(rt, 'x', -10.0f);
	else if (keycode == KEY_F)
		rotate_selected_object(rt, 'y', 10.0f);
	else if (keycode == KEY_G)
		rotate_selected_object(rt, 'y', -10.0f);
	else if (keycode == KEY_V)
		rotate_selected_object(rt, 'z', 10.0f);
	else if (keycode == KEY_B)
		rotate_selected_object(rt, 'z', -10.0f);
	return (EXIT_SUCCESS);
}

int	mouse_hook(int button, int x, int y, t_scene *rt)
{
	t_cnv		coo;
	t_lst_obj	*hit;

	coo.x = x;
	coo.y = y;
	hit = get_xs(rt, coo);
	if (button != 1)
		return (0);
	if (hit)
	{
		select_object(rt, hit);
	}
	else
	{
		rt->selected_obj = NULL;
		rt->s_selected = 0;
		ft_printf("Selected: Camera\n");
	}
	return (0);
}

int	key_hook(int keycode, t_scene *rt)
{
	if (keycode == KEY_ESC)
		return (dbg_write("key ESC pressed. Closing\n"), finalize(rt), 0);
	if (keycode == KEY_TAB)
	{
		select_next_object(rt);
		return (EXIT_SUCCESS);
	}
	if (rt->s_selected == 0)
		return (handle_camera_keys(keycode, rt));
	else if (rt->s_selected == 1)
		return (handle_light_keys(keycode, rt));
	else if (rt->s_selected >= 2)
		return (handle_object_keys(keycode, rt));
	return (EXIT_SUCCESS);
}
