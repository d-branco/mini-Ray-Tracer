/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alde-alm <alde-alm@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 21:42:45 by alde-alm          #+#    #+#             */
/*   Updated: 2025/08/19 21:42:57 by alde-alm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minirt.h"

t_tuple	rotate_vec(t_tuple v, char axis, float angle_deg)
{
	float	angle;
	float	c;
	float	s;
	t_tuple	res;

	angle = angle_deg * (PI / 180.0f);
	res = v;
	c = cosf(angle);
	s = sinf(angle);
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
	return (res);
}

void	rotate_camera(t_scene *rt, char axis, float angle)
{
	rt->c_dir = rotate_vec(rt->c_dir, axis, angle);
	rt->c_dir = vec_norm(rt->c_dir);
	if (dbg_write("Camera rotated: direction: "))
		ft_printf("(%d,%d,%d)\n", (int)rt->c_dir.x,
			(int)rt->c_dir.y, (int)rt->c_dir.z);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}

void	rotate_selected_object(t_scene *rt, char axis, float angle)
{
	if (!rt->selected_obj)
		return ;
	if (rt->selected_obj->id == e_SPHERE)
		return ;
	rt->selected_obj->vec_uni = rotate_vec(rt->selected_obj->vec_uni,
			axis, angle);
	rt->selected_obj->vec_uni = vec_norm(rt->selected_obj->vec_uni);
	if (POINT_AFTER_POINT)
		ghosting_map(rt);
	else
		initialize_map(rt);
}
