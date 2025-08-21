/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:56:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/21 22:17:58 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//abc.w is the discriminant
static t_tuple	cy_abcd(t_tuple coo, t_tuple dir, t_lst_obj *cy);
static float	calc_surface(t_tuple pnt, t_tuple dir, float t, t_lst_obj *cy);

int	cy_intersect(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *cy)
{
	t_tuple	abc;
	float	result;
	float	surface;

	(void) rt;
	abc = cy_abcd(pnt, dir, cy);
	if (abc.w < EPSILON)
		return (FALSE);
	result = (-abc.y - sqrtf(abc.w)) / (2 * abc.x);
	surface = calc_surface(pnt, dir, result, cy);
	result = (-abc.y + sqrtf(abc.w)) / (2 * abc.x);
	if ((result > EPSILON) && (surface >= -(cy->height / 2.0f))
		&& (surface <= (cy->height / 2.0f)))
		return (TRUE);
	result = (-abc.y + sqrtf(abc.w)) / (2 * abc.x);
	surface = calc_surface(pnt, dir, result, cy);
	if ((result > EPSILON) && (surface >= -(cy->height / 2.0f))
		&& (surface <= (cy->height / 2.0f)))
		return (TRUE);
	return (FALSE);
}

int	smll_dst_to_cylinder(t_scene *rt, t_tuple dir, t_lst_obj *cy, float *dst)
{
	t_tuple	abc;
	float	result;
	float	surface;
	float	half_height;

	abc = cy_abcd(rt->c_coo, dir, cy);
	if (abc.w < EPSILON)
		return (FALSE);
	half_height = cy->height / 2.0f;
	result = (-abc.y - sqrtf(abc.w)) / (2 * abc.x);
	surface = calc_surface(rt->c_coo, dir, result, cy);
	if ((result > EPSILON) && (result < *dst)
		&& (surface >= -half_height) && (surface <= half_height))
		return (*dst = result, TRUE);
	result = (-abc.y + sqrtf(abc.w)) / (2 * abc.x);
	surface = calc_surface(rt->c_coo, dir, result, cy);
	if ((result > EPSILON) && (result < *dst)
		&& (surface >= -half_height) && (surface <= half_height))
		return (*dst = result, TRUE);
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

static float	calc_surface(
					t_tuple pnt, t_tuple dir, float t, t_lst_obj *cy)
{
	t_tuple	intersection_point;

	intersection_point = vec_addiction(pnt, vec_scalar_multiplication(t, dir));
	return (vec_inner_product(
			vec_subtraction(intersection_point, cy->center), cy->vec_uni));
}
