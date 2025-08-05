/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:02:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/04 20:29:08 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//abc.x		a
//abc.y		b
//abc.z		c
//abc.w		discriminator

//abc.z = vec_inner_product(sphere_to_ray, sphere_to_ray)
//	- ((sp->diameter / 2.0f) * (sp->diameter / 2.0f));

t_intersect	*sp_intersect(t_lst_obj *sp, t_ray ray)
{
	t_tuple		abc;
	t_tuple		sphere_to_ray;
	t_ray		rayt;

	rayt = ray_transform(ray, m4_inverse(sp->transform));
	sp->intersect.count = 2;
	sphere_to_ray = pnt_subtraction_into_vec(rayt.origin, sp->center);
	abc.x = vec_inner_product(rayt.direction, rayt.direction);
	abc.y = 2 * vec_inner_product(rayt.direction, sphere_to_ray);
	abc.z = vec_inner_product(sphere_to_ray, sphere_to_ray) - 1.0f;
	abc.w = powf(abc.y, 2) - (4 * abc.x * abc.z);
	if (dbg_write("Discriminator: "))
		ft_printf("%i\n", abc.w);
	if (abc.w < 0)
		return (sp->intersect.count = 0, &sp->intersect);
	if (fl_equal(abc.w, 0.0f))
		sp->intersect.count = 1;
	sp->intersect.dst[0] = (-abc.y - sqrtf(abc.w)) / (2 * abc.x);
	sp->intersect.dst[1] = (-abc.y + sqrtf(abc.w)) / (2 * abc.x);
	return (&sp->intersect);
}

//typedef struct s_intersect
//{
//	int						count;
//	float					dst[2];
//}							t_intersect;

int	smll_dst_to_sphere(t_scene *rt, t_tuple dir, t_lst_obj *sp, float *dst)
{
	t_tuple		oc;
	t_tuple		abc;
	float		discriminant;
	float		smaller;
	float		bigger;

	oc = pnt_subtraction_into_vec(rt->c_coord,
			(t_tuple){sp->center.x, sp->center.y, sp->center.z, POINT});
	abc.x = vec_inner_product(dir, dir);
	abc.y = 2.0f * vec_inner_product(oc, dir);
	abc.z = vec_inner_product(oc, oc) - powf((sp->diameter / 2), 2);
	discriminant = (abc.y * abc.y) - (4 * abc.x * abc.z);
	if (discriminant < 0)
		return (FALSE);
	smaller = (-abc.y - sqrtf(discriminant)) / (2 * abc.x);
	bigger = (-abc.y + sqrtf(discriminant)) / (2 * abc.x);
	if ((smaller > EPSILON) && (smaller < *dst))
		return (*dst = smaller, TRUE);
	else if ((bigger > EPSILON) && (bigger < *dst))
		return (*dst = bigger, TRUE);
	return (FALSE);
}
