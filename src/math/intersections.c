/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:15:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 14:15:31 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
