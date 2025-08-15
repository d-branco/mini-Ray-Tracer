/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparisson.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 13:18:08 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 14:17:07 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	fl_equal(float a, float b)
{
	if (((a - b) < EPSILON) && ((a - b) > (0 - EPSILON)))
		return (TRUE);
	return (FALSE);
}

int	tuple_equal(t_tuple a, t_tuple b)
{
	if ((DEBUG) && !fl_equal(a.w, b.w))
		dbg_write_code("Comparisson between different tuple types!\n", RED);
	if ((((a.x - b.x) < EPSILON) && ((a.x - b.x) > (0 - EPSILON)))
		|| (((a.y - b.y) < EPSILON) && ((a.y - b.y) > (0 - EPSILON)))
		|| (((a.z - b.z) < EPSILON) && ((a.z - b.z) > (0 - EPSILON)))
		|| (((a.w - b.w) < EPSILON) && ((a.w - b.w) > (0 - EPSILON))))
		return (TRUE);
	return (FALSE);
}
