/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:56:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/22 15:26:56 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	smll_dst_to_circle(
				t_scene *rt, t_tuple dir, t_lst_obj *circle, float *dst);

int	cy_intersect(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *cy)
{
	int	ret;

	ret = FALSE;
	if (cy_body_xs(rt, pnt, dir, cy) || cy_top_xs(rt, pnt, dir, cy))
		ret = TRUE;
	return (ret);
}

int	smll_dst_to_cylinder(t_scene *rt, t_tuple dir, t_lst_obj *cy, float *dst)
{
	int	ret;

	ret = FALSE;
	if (smll_dst_to_cy_body(rt, dir, cy, dst))
		ret = TRUE;
	if (smll_dst_to_cy_top(rt, dir, cy, dst))
		ret = TRUE;
	return (ret);
}

int	cy_top_xs(t_scene *rt, t_tuple pnt, t_tuple dir, t_lst_obj *cy)
{
	//TODO second
	(void) rt;
	(void) pnt;
	(void) dir;
	(void) cy;
	return (FALSE);
}

int	smll_dst_to_cy_top(t_scene *rt, t_tuple dir, t_lst_obj *cy, float *dst)
{
	t_lst_obj		circle;

	circle.vec_uni = cy->vec_uni;
	circle.diameter = cy->diameter;
	circle.center = cy->center;
	circle.center.x += cy->vec_uni.x * (cy->height / 2.0f);
	circle.center.y += cy->vec_uni.y * (cy->height / 2.0f);
	circle.center.z += cy->vec_uni.z * (cy->height / 2.0f);
	if (smll_dst_to_circle(rt, dir, &circle, dst))
		return (TRUE);
	circle.center = cy->center;
	circle.center.x -= cy->vec_uni.x * (cy->height / 2.0f);
	circle.center.y -= cy->vec_uni.y * (cy->height / 2.0f);
	circle.center.z -= cy->vec_uni.z * (cy->height / 2.0f);
	if (smll_dst_to_circle(rt, dir, &circle, dst))
		return (TRUE);
	return (FALSE);
}

static int	smll_dst_to_circle(
				t_scene *rt, t_tuple dir, t_lst_obj *circle, float *dst)
{
	t_tuple		oc;
	float		denom;
	float		t;
	t_tuple		xs_pnt;
	t_tuple		center_to_xs;

	oc = pnt_subtr_to_vec(rt->c_coo, circle->center);
	denom = vec_inner_product(dir, circle->vec_uni);
	if (fabs(denom) < EPSILON)
		return (FALSE);
	t = -vec_inner_product(oc, circle->vec_uni) / denom;
	if (t <= EPSILON || t >= *dst)
		return (FALSE);
	xs_pnt = vec_addiction(rt->c_coo, vec_scalar_multiplication(t, dir));
	center_to_xs = pnt_subtr_to_vec(xs_pnt, circle->center);
	if ((vec_inner_product(center_to_xs, center_to_xs))
		<= powf((circle->diameter / 2.0f), 2))
		return ((*dst = t), TRUE);
	return (FALSE);
}
