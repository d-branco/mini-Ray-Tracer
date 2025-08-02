/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_sphere.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 19:02:46 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/01 21:20:57 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	smll_dst_to_sphere(t_scene *rt, t_tuple dir, t_lst_obj *sp, float *dst)
{
	t_tuple		oc;
	t_tuple		abc;
	float		discriminant;
	float		smaller;
	float		bigger;

	oc = vec_subtraction(rt->c_ori,
			(t_tuple){sp->center.x, sp->center.y, sp->center.z, VECTOR});
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
