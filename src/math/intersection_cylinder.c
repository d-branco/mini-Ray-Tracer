/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:56:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 18:12:32 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_tuple	cy_abcd(t_tuple coo, t_tuple dir, t_lst_obj *cy);
//abc.w is the discriminant

int	cy_intersect(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *cy)
{
	t_tuple	abc;

	(void) rt;
	abc = cy_abcd(pnt, dir, cy);
	if (abc.w < EPSILON)
		return (FALSE);
	if ((((-abc.y + sqrtf(abc.w)) / (2 * abc.x)) > EPSILON)
		|| (((-abc.y - sqrtf(abc.w)) / (2 * abc.x)) > EPSILON))
		return (TRUE);
	return (FALSE);
}

int	smll_dst_to_cylinder(t_scene *rt, t_tuple dir, t_lst_obj *cy, float *dst)
{
	t_tuple	abc;
	float	smaller;
	float	bigger;

	abc = cy_abcd(rt->c_coo, dir, cy);
	if (abc.w < 0.0f)
		return (FALSE);
	smaller = (-abc.y - sqrtf(abc.w)) / (2 * abc.x);
	bigger = (-abc.y + sqrtf(abc.w)) / (2 * abc.x);
	if ((smaller > EPSILON) && (smaller < *dst))
		return (*dst = smaller, TRUE);
	else if ((bigger > EPSILON) && (bigger < *dst))
		return (*dst = bigger, TRUE);
	return (FALSE);
}

static t_tuple	cy_abcd(t_tuple coo, t_tuple dir, t_lst_obj *cy)
{
	t_tuple	abcd;
	t_tuple	oc;
	t_tuple	axis;
	t_tuple	d_perp;
	t_tuple	oc_perp;

	axis = vec_norm(cy->vec_uni);
	oc = pnt_subtr_to_vec(coo, cy->center);
	d_perp = vec_subtraction(dir,
			vec_scalar_multiplication(vec_inner_product(dir, axis), axis));
	oc_perp = vec_subtraction(oc,
			vec_scalar_multiplication(vec_inner_product(oc, axis), axis));
	abcd.x = vec_inner_product(d_perp, d_perp);
	abcd.y = 2.0f * vec_inner_product(d_perp, oc_perp);
	abcd.z = vec_inner_product(oc_perp, oc_perp) - powf(cy->diameter / 2.0f, 2);
	abcd.w = (abcd.y * abcd.y) - (4 * abcd.x * abcd.z);
	return (abcd);
}
