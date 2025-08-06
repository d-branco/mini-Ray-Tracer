/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:44:11 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 21:08:55 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	make_ray(t_tuple origin, t_tuple direction)
{
	t_ray	ret;

	if (origin.w != POINT)
		dbg_write_code("Error:\nThis is NOT a point!\n", RED);
	if (direction.w != VECTOR)
		dbg_write_code("Error:\nThis is NOT a vector!\n", RED);
	ret = (t_ray){origin, direction};
	return (ret);
}

t_tuple	ray_position(t_ray r, float dst)
{
	return (mk_pnt(
			r.origin.x + r.direction.x * dst,
			r.origin.y + r.direction.y * dst,
			r.origin.z + r.direction.z * dst));
}

t_tuple	old_get_ray_direction(t_scene *rt, t_canvas coo)
{
	t_tuple		right;
	t_tuple		up;
	t_canvas	viewport;
	t_canvas	v;
	t_tuple		ray_dir;

	ray_dir = (t_tuple){0, 1, 0, VECTOR};
	if (((rt->c_ori.y) > 0.9f) || ((rt->c_ori.y) < -0.9f))
		ray_dir = (t_tuple){0, 0, -1, VECTOR};
	right = vec_norm(vec_cross_product(
				(t_tuple){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z, 0}, ray_dir));
	up = vec_norm(vec_cross_product(
				right, (t_tuple){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z, 0}));
	viewport.x = 2.0f * tan(rt->c_fov / 2.0f);
	viewport.y = viewport.x * ((float)HEIGHT / (float)WIDTH);
	v.x = ((2.0f * coo.x / (WIDTH - 1)) - 1.0f) * (viewport.x / 2.0f);
	v.y = (0.0f - (2.0f * coo.y / (HEIGHT - 1)) + 1.0f) * (viewport.y / 2.0f);
	ray_dir.x = rt->c_ori.x + (right.x * v.x) + (up.x * v.y);
	ray_dir.y = rt->c_ori.y + (right.y * v.x) + (up.y * v.y);
	ray_dir.z = rt->c_ori.z + (right.z * v.x) + (up.z * v.y);
	return (vec_norm(ray_dir));
}
