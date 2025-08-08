/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/07 13:41:18 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 13:41:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	smll_dst_to_plane(t_scene *rt, t_tuple dir, t_lst_obj *pl, float *dst)
{
	float	ret;

	if (fl_equal(vec_inner_product(dir, pl->vec_uni), 0))
		return (FALSE);
	if (fl_equal(vec_inner_product(
				pnt_subtraction_into_vec(rt->c_coord, pl->center),
				pl->vec_uni), 0))
		return (FALSE);
	ret = vec_inner_product(
			pnt_subtraction_into_vec(pl->center, rt->c_coord), pl->vec_uni)
		/ vec_inner_product(dir, pl->vec_uni);
	if ((ret < 0) || (ret > *dst))
		return (FALSE);
	*dst = ret;
	return (TRUE);
}

int	pl_intersect(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *pl)
{
	float	dst;

	(void) rt;
	if (fl_equal(vec_inner_product(dir, pl->vec_uni), 0))
		return (FALSE);
	if (fl_equal(vec_inner_product(
				pnt_subtraction_into_vec(pnt, pl->center), pl->vec_uni), 0))
		return (FALSE);
	dst = vec_inner_product(pl->vec_uni,
			pnt_subtraction_into_vec(pl->center, pnt))
		/ vec_inner_product(
			pnt_subtraction_into_vec(pnt, pl->center), pl->vec_uni);
	if (dst < 0)
		return (FALSE);
	return (TRUE);
}
