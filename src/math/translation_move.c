/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translation_move.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:43:11 by alde-alm          #+#    #+#             */
/*   Updated: 2025/08/19 21:43:14 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

void	move_selected_object(t_scene *rt, float dx, float dy, float dz)
{
	if (!rt->selected_obj)
		return ;
	rt->selected_obj->center.x += dx;
	rt->selected_obj->center.y += dy;
	rt->selected_obj->center.z += dz;
	if (dbg_write("Object: center: "))
		ft_printf("(%3i),(%3i),(%3i)\n", (int) rt->selected_obj->center.x,
			(int) rt->selected_obj->center.y, (int) rt->selected_obj->center.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

void	move_light(t_scene *rt, float dx, float dy, float dz)
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

void	key_right_left(t_scene *rt, float translation)
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

void	key_up_down(t_scene *rt, float translation)
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
