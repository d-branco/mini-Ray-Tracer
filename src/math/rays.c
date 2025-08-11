/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:44:11 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 22:07:57 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	get_ray_direction(t_scene *rt, t_cnv coo)
{
	t_tuple		right;
	t_tuple		up;
	t_cnv		viewport;
	t_cnv		v;
	t_tuple		ray_dir;

	ray_dir = (t_tuple){0, 0, 1, VECTOR};
	if (((rt->c_dir.z) > 0.9f) || ((rt->c_dir.z) < -0.9f))
		ray_dir = (t_tuple){0, 1, 0, VECTOR};
	right = vec_norm(vec_cross_product(
				(t_tuple){rt->c_dir.x, rt->c_dir.y, rt->c_dir.z, 0}, ray_dir));
	up = vec_norm(vec_cross_product(
				right, (t_tuple){rt->c_dir.x, rt->c_dir.y, rt->c_dir.z, 0}));
	viewport.x = 2.0f * tan(rt->c_fov / 2.0f);
	viewport.y = viewport.x * ((float)HEIGHT / (float)WIDTH);
	v.x = ((2.0f * coo.x / (WIDTH - 1)) - 1.0f) * (viewport.x / 2.0f);
	v.y = (0.0f - (2.0f * coo.y / (HEIGHT - 1)) + 1.0f) * (viewport.y / 2.0f);
	ray_dir.x = rt->c_dir.x + (right.x * v.x) + (up.x * v.y);
	ray_dir.y = rt->c_dir.y + (right.y * v.x) + (up.y * v.y);
	ray_dir.z = rt->c_dir.z + (right.z * v.x) + (up.z * v.y);
	return (vec_norm(ray_dir));
}
