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

static void	key_right_left(t_scene *rt, float translation);
static void	key_up_down(t_scene *rt, float translation);
static void	move_selected_object(t_scene *rt, float dx, float dy, float dz);
static void	move_light(t_scene *rt, float dx, float dy, float dz);
static void	select_next_object();
int	s_selected = 0; // 0: camera, 1: light, >=2: objects
t_lst_obj *selected_obj = NULL;
//extern t_lst_obj *selected_obj;
void ghosting_map(t_scene *rt);

static t_tuple rotate_vec(t_tuple v, char axis, float angle_deg)
{
	float angle = angle_deg * (PI / 180.0f);
	t_tuple res = v;
	float c = cosf(angle);
	float s = sinf(angle);
	if (axis == 'x')
	{
		res.y = v.y * c - v.z * s;
		res.z = v.y * s + v.z * c;
	}
	else if (axis == 'y')
	{
		res.x = v.x * c + v.z * s;
		res.z = -v.x * s + v.z * c;
	}
	else if (axis == 'z')
	{
		res.x = v.x * c - v.y * s;
		res.y = v.x * s + v.y * c;
	}
	return res;
}

static void rotate_camera(t_scene *rt, char axis, float angle)
{
	rt->c_dir = rotate_vec(rt->c_dir, axis, angle);
	rt->c_dir = vec_norm(rt->c_dir);
	if (dbg_write("Camera rotated: direction: "))
		ft_printf("(%d,%d,%d)\n", (int)rt->c_dir.x, (int)rt->c_dir.y, (int)rt->c_dir.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

static void rotate_selected_object(t_scene *rt, char axis, float angle)
{
	if (!selected_obj) return;
	if (selected_obj->id == e_SPHERE) return; // Não rotaciona esfera
	selected_obj->vec_uni = rotate_vec(selected_obj->vec_uni, axis, angle);
	selected_obj->vec_uni = vec_norm(selected_obj->vec_uni);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write_code("ERROR: return from close_win_button()\n", RED), 0);
}

int mouse_hook(int button, int x, int y, t_scene *rt)
{
	if (button != 1)// Left mouse button
		return (0);
	t_cnv coo = {x, y};
	t_lst_obj *hit = get_xs(rt, coo);
	if (hit)
	{
		selected_obj = hit;
		s_selected = 2;
		const char *obj_name = "UNKNOWN";
		if (hit->id == e_SPHERE) obj_name = "SPHERE";
		else if (hit->id == e_PLANE) obj_name = "PLANE";
		else if (hit->id == e_CYlINDER) obj_name = "CYLINDER";
		ft_printf("Selected: Object (%s)\n", obj_name);
	}
	else
	{
		selected_obj = NULL;
		s_selected = 0;
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
	if (s_selected == 0)// Camera
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
	}
	else if (s_selected == 1)// Light
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
	else if (s_selected >= 2 && selected_obj)
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
	}
	return (EXIT_SUCCESS);
}

static void select_next_object()
{
	if (s_selected == 0)
	{
		s_selected = 1;
		dbg_write("Selected: Light\n");
		selected_obj = NULL;
	}
	else
	{
		s_selected = 0;
		selected_obj = NULL;
		dbg_write("Selected: Camera\n");
	}
}

static void move_selected_object(t_scene *rt, float dx, float dy, float dz)// Translates the selected object
{
	if (!selected_obj) return;
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
	if (dbg_write("Camera: center: "))
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
	if (dbg_write("Camera: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) rt->c_coord.x,
			(int) rt->c_coord.y, (int) rt->c_coord.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
	rt->key_pressed = TRUE;
}
