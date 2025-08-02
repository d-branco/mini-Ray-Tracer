/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:44:11 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 20:40:33 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	get_ray_direction(t_scene *rt, t_canvas coo)
{
	t_tuple		right;
	t_tuple		up;
	t_canvasf	viewport;
	t_canvasf	v;
	t_tuple		ray_dir;

	ray_dir = (t_tuple){0, 1, 0, VECTOR};
	if (((rt->c_ori.y) > 0.9f) || ((rt->c_ori.y) < -0.9f))
		ray_dir = (t_tuple){0, 0, -1, VECTOR};
	right = vec_normalization(vec_cross_product(
				(t_tuple){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z, 0}, ray_dir));
	up = vec_normalization(vec_cross_product(
				right, (t_tuple){rt->c_ori.x, rt->c_ori.y, rt->c_ori.z, 0}));
	viewport.x = 2.0f * tan(rt->c_fov / 2.0f);
	viewport.y = viewport.x * ((float)HEIGHT / (float)WIDTH);
	v.x = ((2.0f * coo.x / (WIDTH - 1)) - 1.0f) * (viewport.x / 2.0f);
	v.y = (0.0f - (2.0f * coo.y / (HEIGHT - 1)) + 1.0f) * (viewport.y / 2.0f);
	ray_dir.x = rt->c_ori.x + (right.x * v.x) + (up.x * v.y);
	ray_dir.y = rt->c_ori.y + (right.y * v.x) + (up.y * v.y);
	ray_dir.z = rt->c_ori.z + (right.z * v.x) + (up.z * v.y);
	return (vec_normalization(ray_dir));
}
