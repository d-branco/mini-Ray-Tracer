/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_looping_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:38 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/05 07:34:42 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			canvas_loop(t_scene *rt, int edge);
static void			paint_canvas(t_scene *rt, t_canvas coo, int edge);
static t_lst_obj	*get_intersetion(t_scene *rt, t_canvas coo);
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
				o = get_intersetion(rt, canvas);
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

static t_lst_obj	*get_intersetion(t_scene *rt, t_canvas coo)
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
				nearest = current;
		}
		current = current->next;
	}
	if (nearest)
		return (nearest);
	return (NULL);
}

static int	get_color(t_scene *rt, t_canvas coo, t_lst_obj *obj)
{
	(void) coo;
	if (obj == NULL)
		return (encode_rgb(rt->a_rgb.r, rt->a_rgb.g, rt->a_rgb.b));
	else
		return (encode_rgb(
				(int)obj->rgb_rng.r, (int)obj->rgb_rng.g, (int)obj->rgb_rng.b));
}
