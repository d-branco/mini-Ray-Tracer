/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_looping_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:38 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 21:08:00 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			canvas_loop(t_scene *rt, int edge, t_canvas *canvas);
static void			paint_canvas(t_scene *rt, t_canvas coo, int edge);
static t_lst_obj	*get_intersection(t_scene *rt, t_canvas coo);

int	old_looping_loop(t_scene *rt)
{
	static t_canvas	canvas = {WIDTH, HEIGHT};

	if (rt->edge >= MAP_RESOLUTION)
		rt->edge = MAP_RESOLUTION - 1;
	if (rt->edge >= 1)
	{
		if ((canvas.y >= HEIGHT) && (dbg_write("Drawing with edge: ")))
			ft_printf("%i... \n", rt->edge);
		canvas_loop(rt, rt->edge, &canvas);
		if (canvas.y >= HEIGHT)
		{
			canvas = (t_canvas){WIDTH, HEIGHT};
			rt->edge /= 2;
			if ((rt->edge % 2) && (rt->edge > 2))
				rt->edge++;
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
	rt->key_pressed = FALSE;
	return (0);
}

static void	canvas_loop(t_scene *rt, int edge, t_canvas *c)
{
	t_lst_obj	*o;

	if (c->y >= HEIGHT)
		c->y = edge / 2;
	if (c->y < HEIGHT)
	{
		c->x = edge / 2;
		while (c->x < WIDTH)
		{
			if (rt->map[(int)c->x][(int)c->y] == -1)
			{
				o = get_intersection(rt, *c);
				rt->map[(int)c->x][(int)c->y] = get_color(rt, o);
				pixel_put(rt, c->x, c->y, rt->map[(int)c->x][(int)c->y]);
				paint_canvas(rt, (t_canvas){c->x, c->y}, edge);
			}
			c->x += edge;
		}
		c->y += edge;
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
				&& (rt->map[(int)(coo.x + t.x)][(int)(coo.y + t.y)] == -1))
				pixel_put(rt, (coo.x + t.x), ((int)coo.y + t.y),
					rt->map[(int)coo.x][(int)coo.y]);
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
