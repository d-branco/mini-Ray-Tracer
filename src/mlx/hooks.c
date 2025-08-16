/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 09:00:42 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void ghosting_map(t_scene *rt);
static void	key_right_left(t_scene *rt, float translation);
static void	key_up_down(t_scene *rt, float translation);
static void	move_selected_object(t_scene *rt, float dx, float dy, float dz);
static void	move_light(t_scene *rt, float dx, float dy, float dz);
static void	select_next_object(t_scene *rt);
static int	s_selected = 0; // 0: camera, 1: light, >=2: objects
static t_lst_obj *selected_obj = NULL;
	
int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write_code("ERROR: return from close_win_button()\n", RED), 0);
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
	if (s_selected == 0)// Camera translation
	{
		if (keycode == KEY_RIGHT)
			key_right_left(rt, 1.0f);
		else if (keycode == KEY_LEFT)
			key_right_left(rt, -1.0f);
		else if (keycode == KEY_UP)
			key_up_down(rt, 1.0f);
		else if (keycode == KEY_DOWN)
			key_up_down(rt, -1.0f);
	}
	else if (s_selected == 1)// Light translation
	{
		if (keycode == KEY_I)
			move_light(rt, 0, 1, 0);
		else if (keycode == KEY_K)
			move_light(rt, 0, -1, 0);
		else if (keycode == KEY_J)
			move_light(rt, -1, 0, 0);
		else if (keycode == KEY_L)
			move_light(rt, 1, 0, 0);
		else if (keycode == KEY_U)
			move_light(rt, 0, 0, 1);
		else if (keycode == KEY_O)
			move_light(rt, 0, 0, -1);
	}
	else if (s_selected >= 2 && selected_obj)// Object translation
	{
		if (keycode == KEY_W)
			move_selected_object(rt, 0, 1, 0);
		else if (keycode == KEY_S)
			move_selected_object(rt, 0, -1, 0);
		else if (keycode == KEY_A)
			move_selected_object(rt, -1, 0, 0);
		else if (keycode == KEY_D)
			move_selected_object(rt, 1, 0, 0);
		else if (keycode == KEY_Q)
			move_selected_object(rt, 0, 0, 1);
		else if (keycode == KEY_E)
			move_selected_object(rt, 0, 0, -1);
	}
	return (EXIT_SUCCESS);
}
static void select_next_object(t_scene *rt)// Selects the next object/light/camera
{
	static int obj_index = 0;
	t_lst_obj *obj = rt->lst_obj;
	if (s_selected == 0)
	{
		s_selected = 1;
		dbg_write("Selected: Light\n");
		selected_obj = NULL;
	}
	else if (s_selected == 1)
	{
		if (obj)
		{
			s_selected = 2;
			selected_obj = obj;
			obj_index = 0;
			const char *obj_name = "UNKNOWN";
			if (selected_obj->id == e_SPHERE) obj_name = "SPHERE";
			else if (selected_obj->id == e_PLANE) obj_name = "PLANE";
			else if (selected_obj->id == e_CYlINDER) obj_name = "CYLINDER";
			ft_printf("Selected: Object 1 (%s)\n", obj_name);
		}
		else
		{
			s_selected = 0;
			dbg_write("Selected: Camera\n");
		}
	}
	else
	{
		if (selected_obj && selected_obj->next)
		{
			selected_obj = selected_obj->next;
			obj_index++;
			const char *obj_name = "UNKNOWN";
			if (selected_obj->id == e_SPHERE) obj_name = "SPHERE";
			else if (selected_obj->id == e_PLANE) obj_name = "PLANE";
			else if (selected_obj->id == e_CYlINDER) obj_name = "CYLINDER";
			ft_printf("Selected: Object %d (%s)\n", obj_index + 1, obj_name);
		}
		else
		{
			s_selected = 0;
			selected_obj = NULL;
			dbg_write("Selected: Camera\n");
		}
	}
}

static void move_selected_object(t_scene *rt, float dx, float dy, float dz)// Translates the selected object
{
	if (!selected_obj) return;
	if (selected_obj->id == e_SPHERE)
		return;// Does not translate/rotate sphere
	selected_obj->center.x += dx;
	selected_obj->center.y += dy;
	selected_obj->center.z += dz;
	if (dbg_write("Object: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) selected_obj->center.x,
			(int) selected_obj->center.y, (int) selected_obj->center.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

static void move_light(t_scene *rt, float dx, float dy, float dz)// Translates the light
{
	rt->l_coo.x += dx;
	rt->l_coo.y += dy;
	rt->l_coo.z += dz;
	if (dbg_write("Light: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) rt->l_coo.x,
			(int) rt->l_coo.y, (int) rt->l_coo.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

void	ghosting_map(t_scene *rt)
{
	int	x;
	int	y;

	dbg_write("Initiating the map\n");
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			rt->map[x][y] = -1;
			y++;
		}
		x++;
	}
	rt->edge = MAP_RESOLUTION;
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
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
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
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
	rt->key_pressed = TRUE;
}
