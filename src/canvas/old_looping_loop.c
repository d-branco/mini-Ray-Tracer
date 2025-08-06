/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_looping_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:38 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 13:42:52 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			canvas_loop(t_scene *rt, int edge);
static void			paint_canvas(t_scene *rt, t_canvas coo, int edge);
static t_lst_obj	*get_intersection(t_scene *rt, t_canvas coo);
static int			get_color(t_scene *rt, t_canvas coo, t_lst_obj *obj);

int	old_looping_loop(t_scene *rt)
{
	if (rt->edge >= MAP_RESOLUTION)
		rt->edge = MAP_RESOLUTION - 1;
	if (rt->edge >= 1)
	{
		dbg_write("Drawing a the map with edge: ");
		if (DEBUG)
			ft_printf("%i... ", rt->edge);
		canvas_loop(rt, rt->edge);
		rt->edge /= 2;
		if ((rt->edge % 2) && (rt->edge > 2))
			rt->edge++;
		if (DEBUG)
			write(STDOUT_FILENO, "done!\n", ft_strlen("done!\n"));
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
	rt->key_pressed = FALSE;
	return (0);
}

static void	canvas_loop(t_scene *rt, int edge)
{
	t_canvas	canvas;
	t_lst_obj	*o;

	canvas.y = edge / 2;
	while (canvas.y < HEIGHT)
	{
		canvas.x = edge / 2;
		while (canvas.x < WIDTH)
		{
			if (rt->map[canvas.x][canvas.y] == -1)
			{
				o = get_intersection(rt, canvas);
				rt->map[canvas.x][canvas.y] = get_color(rt, canvas, o);
				pixel_put(rt, canvas.x, canvas.y, rt->map[canvas.x][canvas.y]);
				paint_canvas(rt, (t_canvas){canvas.x, canvas.y}, edge);
			}
			canvas.x += edge;
		}
		canvas.y += edge;
	}
}

static void	paint_canvas(t_scene *rt, t_canvas coo, int edge)
{
	t_canvas	t;

	t = (t_canvas){0, 0};
	t.y = - (edge / 2);
	while (t.y < (edge / 2))
	{
		t.x = - (edge / 2);
		while (t.x < (edge / 2))
		{
			if ((coo.x + t.x < WIDTH) && (coo.y + t.y < HEIGHT)
				&& (rt->map[coo.x + t.x][coo.y + t.y] == -1))
				pixel_put(rt, (coo.x + t.x), (coo.y + t.y),
					rt->map[coo.x][coo.y]);
			t.x++;
		}
		t.y++;
	}
}

static t_lst_obj	*get_intersection(t_scene *rt, t_canvas coo)
{
	t_lst_obj	*current;
	float		dst;
	t_tuple		ray;
	t_lst_obj	*nearest;

	current = rt->lst_obj;
	dst = MAX_FLOAT;
	ray = old_get_ray_direction(rt, coo);
	nearest = NULL;
	while (current != NULL)
	{
		if (current->id == e_SPHERE)
		{
			if (smll_dst_to_sphere(rt, ray, current, &dst))
			{
				nearest = current;
				nearest->xs_pnt = mk_pnt(rt->c_coord.x + dst * ray.x,
						rt->c_coord.y + dst * ray.y,
						rt->c_coord.z + dst * ray.z);
			}
		}
		current = current->next;
	}
	return (nearest);
}

static int	get_color(t_scene *rt, t_canvas coo, t_lst_obj *obj)
{
	t_tuple	xs_to_c;

	(void) coo;
	if (obj == NULL)
		return (encode_rgb(53, 3, 144));
	//		(int)(rt->a_rgb.r * rt->a_ratio),
	//	(int)(rt->a_rgb.g * rt->a_ratio), (int)(rt->a_rgb.b * rt->a_ratio)));
	//if it can see the light, get the norm and check the angle.
	xs_to_c = pnt_subtraction_into_vec(rt->l_coo, obj->xs_pnt);
	if (!check_obj_xs(rt, obj->xs_pnt, xs_to_c))
		return (encode_rgb((int)obj->rgb_rng.r,
				(int)obj->rgb_rng.g,
				(int)obj->rgb_rng.b));
	// if no intersection with objects before hitting the ligh
	//	is of his own color plus the ambient light:
	return (encode_rgb((int)(obj->rgb_rng.r * rt->a_ratio),
		(int)(obj->rgb_rng.g * rt->a_ratio),
		(int)(obj->rgb_rng.b * rt->a_ratio)));
}
