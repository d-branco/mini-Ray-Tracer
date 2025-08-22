/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addiction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:08:20 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/22 14:37:25 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	vec_addiction(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (DEBUG_MATH && ((a.w != VECTOR) || (b.w != VECTOR)))
		dbg_write_code("Warning: non-vector in vector addiction\n", RED);
	result = (t_tuple){(a.x + b.x), (a.y + b.y), (a.z + b.z), VECTOR};
	return (result);
}

t_tuple	vec_subtraction(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (DEBUG_MATH && ((a.w != VECTOR) || (b.w != VECTOR)))
		dbg_write_code("Warning: non-vector in vector subtraction\n", RED);
	result = (t_tuple){(a.x - b.x), (a.y - b.y), (a.z - b.z), VECTOR};
	return (result);
}

t_tuple	pnt_subtr_to_vec(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if (DEBUG_MATH && ((a.w != POINT) || (b.w != POINT)))
		dbg_write_code("Warning: non-point in point subtraction\n", RED);
	result = (t_tuple){(a.x - b.x), (a.y - b.y), (a.z - b.z), VECTOR};
	return (result);
}
