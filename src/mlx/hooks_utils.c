/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:42:15 by alde-alm          #+#    #+#             */
/*   Updated: 2025/08/19 21:42:23 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write_code("ERROR: return from close_win_button()\n", RED), 0);
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

void	select_object(t_scene *rt, t_lst_obj *hit)
{
	const char	*obj_name;

	obj_name = "UNKNOWN";
	rt->selected_obj = hit;
	rt->s_selected = 2;
	if (hit->id == e_SPHERE)
		obj_name = "SPHERE";
	else if (hit->id == e_PLANE)
		obj_name = "PLANE";
	else if (hit->id == e_CYLINDER)
		obj_name = "CYLINDER";
	ft_printf("Selected: Object (%s)\n", obj_name);
}

void	select_next_object(t_scene *rt)
{
	if (rt->s_selected == 0)
	{
		rt->s_selected = 1;
		dbg_write("Selected: Light\n");
		rt->selected_obj = NULL;
	}
	else
	{
		rt->s_selected = 0;
		rt->selected_obj = NULL;
		dbg_write("Selected: Camera\n");
	}
}
