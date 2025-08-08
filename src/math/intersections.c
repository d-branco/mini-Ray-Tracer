/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 08:31:54 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_lst_obj	*get_xs(t_scene *rt, t_cnv coo)
{
	t_lst_obj	*current;
	float		dst;
	t_tuple		ray;
	t_lst_obj	*nearest;

	current = rt->lst_obj;
	dst = MAX_FLOAT;
	ray = get_ray_direction(rt, coo);
	nearest = NULL;
	while (current != NULL)
	{
		if (current->id == e_SPHERE)
		{
			if (smll_dst_to_sphere(rt, ray, current, &dst))
			{
				nearest = current;
				nearest->xs_pnt = mk_pnt(rt->c_coord.x + dst * ray.x,
						rt->c_coord.y + dst * ray.y,
						rt->c_coord.z + dst * ray.z);
			}
		}
		current = current->next;
	}
	return (nearest);
}

int	check_obj_xs(t_scene *rt, t_tuple pnt, t_tuple dir)
{
	t_lst_obj	*current;

	current = rt->lst_obj;
	while (current != NULL)
	{
		if (current->id == e_SPHERE)
		{
			if (sp_intersect(rt, pnt, dir, current))
				return (TRUE);
		}
		current = current->next;
	}
	return (FALSE);
}
