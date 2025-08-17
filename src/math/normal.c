/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:39:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 07:39:41 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (normal <= EPSILON)
		normal = 0;
	return (normal);
}
