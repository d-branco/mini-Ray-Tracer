/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:39:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/22 14:39:28 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	cylinder_body_normal(t_scene *rt, t_lst_obj *obj);

float	calculate_normal(t_scene *rt, t_lst_obj *obj)
{
	float	normal;

	if (obj->id == e_SPHERE)
		normal = vec_inner_product(
				vec_norm(pnt_subtr_to_vec(obj->center, obj->xs_pnt)),
				vec_norm(pnt_subtr_to_vec(obj->xs_pnt, rt->l_coo)));
	if (obj->id == e_PLANE)
		normal = fabsf(vec_inner_product(vec_norm(obj->vec_uni),
					vec_norm(pnt_subtr_to_vec(rt->l_coo, obj->xs_pnt))));
	if (obj->id == e_CYLINDER)
	{
		normal = cylinder_body_normal(rt, obj);
		//TODO third: tops cases are missing. Ought to go here
	}
	if (normal <= EPSILON)
		normal = 0;
	return (normal);
}

static float	cylinder_body_normal(t_scene *rt, t_lst_obj *obj)
{
	float		normal;
	t_tuple		axis_to_point;
	t_tuple		projection;
	t_tuple		surface_normal;

	axis_to_point = pnt_subtr_to_vec(obj->xs_pnt, obj->center);
	projection = vec_scalar_multiplication(
			vec_inner_product(axis_to_point, obj->vec_uni), obj->vec_uni);
	surface_normal = vec_norm(vec_subtraction(axis_to_point, projection));
	normal = fabsf(vec_inner_product(surface_normal,
				vec_norm(pnt_subtr_to_vec(rt->l_coo, obj->xs_pnt))));
	return (normal);
}
