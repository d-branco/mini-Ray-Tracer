/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_cylinder.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/17 07:56:37 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/22 14:39:07 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	if (smll_dst_to_cy_body(rt, dir, cy, dst)
		|| smll_dst_to_cy_top(rt, dir, cy, dst))
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
	//TODO first
	(void) rt;
	(void) dir;
	(void) cy;
	(void) dst;
	return (FALSE);
}
