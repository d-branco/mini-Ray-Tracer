/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   old_looping_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:38 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 08:51:14 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			canvas_loop(t_scene *rt, int edge, t_cnv *canvas);
static void			paint_cnv(t_scene *rt, t_cnv coo, int edge);

int	old_looping_loop(t_scene *rt)
{
	static t_cnv	canvas = {WIDTH, HEIGHT};

	if (rt->edge >= 1)
	{
		if ((canvas.y >= HEIGHT) && (dbg_write("Drawing with edge: ")))
			ft_printf("%i... \n", rt->edge);
		canvas_loop(rt, rt->edge, &canvas);
		if (canvas.y >= HEIGHT)
		{
			canvas = (t_cnv){WIDTH, HEIGHT};
			if (rt->edge == 1)
				dbg_write("Drawing done!\n");
			rt->edge /= 2;
			if ((rt->edge % 2) && (rt->edge > 2))
				rt->edge++;
		}
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
	rt->key_pressed = FALSE;
	return (0);
}

static void	canvas_loop(t_scene *rt, int edge, t_cnv *c)
{
	if (c->y >= HEIGHT)
		c->y = edge / 2;
	if (c->y < HEIGHT)
	{
		c->x = edge / 2;
		while (c->x < WIDTH)
		{
			if (rt->map[(int)c->x][(int)c->y] == -1)
			{
				rt->map[(int)c->x][(int)c->y] = pix_smooth4(rt, c);
				pixel_put(rt, c->x, c->y, rt->map[(int)c->x][(int)c->y]);
				paint_cnv(rt, (t_cnv){c->x, c->y}, edge);
			}
			c->x += edge;
		}
		c->y += edge;
	}
}

static void	paint_cnv(t_scene *rt, t_cnv coo, int edge)
{
	t_cnv	t;

	t = (t_cnv){0, 0};
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
			if (POINT_AFTER_POINT)
				break ;
		}
		t.y++;
		if (POINT_AFTER_POINT)
			break ;
	}
}
