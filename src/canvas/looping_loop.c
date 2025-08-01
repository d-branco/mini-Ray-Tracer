/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   looping_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 09:03:38 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 21:17:03 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			canvas_loop(t_scene *rt, int edge);
static void			paint_canvas(t_scene *rt, t_canvas coo, int edge);
static t_lst_obj	*get_intersetion(t_scene *rt, t_canvas coo);
static int			get_color(t_scene *rt, t_canvas coo, t_lst_obj *obj);

void	looping_loop(t_scene *rt)
{
	int	edge;

	edge = HEIGHT;
	if (WIDTH > HEIGHT)
		edge = WIDTH;
	debug_write("Drawing a the map... ");
	color_screen(rt, encode_rgb(rt->a_rgb.r, rt->a_rgb.g, rt->a_rgb.b));
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
	while (edge >= 1)
	{
		canvas_loop(rt, edge);
		if (DEBUG)
			ft_printf("%i, ", edge);
		edge /= 2;
		if ((edge % 2) && (edge > 2))
			edge++;
	}
	if (DEBUG)
		write(STDOUT_FILENO, "done!\n", ft_strlen("done!\n"));
}

static void	canvas_loop(t_scene *rt, int edge)
{
	t_canvas	canvas;

	canvas.y = edge / 2;
	while (canvas.y < HEIGHT)
	{
		canvas.x = edge / 2;
		while (canvas.x < WIDTH)
		{
			if (rt->map[canvas.x][canvas.y] == -1)
				paint_canvas(rt, (t_canvas){canvas.x, canvas.y}, edge);
			canvas.x += edge;
		}
		canvas.y += edge;
	}
	mlx_put_image_to_window(rt->mlx, rt->mlx_win, rt->mlx_img, 0, 0);
}

static void	paint_canvas(t_scene *rt, t_canvas coo, int edge)
{
	t_canvas	t;
	t_lst_obj	*o;

	t = (t_canvas){0, 0};
	o = get_intersetion(rt, coo);
	rt->map[coo.x][coo.y] = get_color(rt, coo, o);
	pixel_put(rt, (coo.x), (coo.y), rt->map[coo.x][coo.y]);
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
	t_vector	ray;
	t_lst_obj	*nearest;

	current = rt->lst_obj;
	dst = 340282346638528859811704183484516925440.0f;
	ray = get_ray_direction(rt, coo);
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
