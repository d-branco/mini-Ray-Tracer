/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 09:49:27 by abessa-m         ###   ########.fr       */
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
		if (((current->id == e_SPHERE)
				&& (smll_dst_to_sphere(rt, ray, current, &dst)))
			|| ((current->id == e_PLANE)
				&& (smll_dst_to_plane(rt, ray, current, &dst)))
			|| ((current->id == e_CYLINDER)
				&& (smll_dst_to_cylinder(rt, ray, current, &dst))))
		{
			nearest = current;
			nearest->xs_pnt = (t_tuple){rt->c_coo.x + dst * ray.x,
				rt->c_coo.y + dst * ray.y, rt->c_coo.z + dst * ray.z, POINT};
		}
		current = current->next;
	}
	return (nearest);
}

int	check_obj_xs(t_scene *rt, t_tuple ray_pnt, t_tuple ray_dir)
{
	t_lst_obj	*current;

	current = rt->lst_obj;
	while (current != NULL)
	{
		if ((current->id == e_SPHERE)
			&& (sp_intersect(rt, ray_pnt, ray_dir, current)))
			return (TRUE);
		else if ((current->id == e_PLANE)
			&& (pl_intersect(rt, ray_pnt, ray_dir, current)))
			return (TRUE);
		else if ((current->id == e_CYLINDER)
			&& (cy_intersect(rt, ray_pnt, ray_dir, current)))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}
