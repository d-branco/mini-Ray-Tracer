/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addiction.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:08:20 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 14:21:15 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	vec_addiction(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if ((a.w != VECTOR) || (b.w != VECTOR))
		dbg_write("Warning: point in vector addiction\n");
	result = (t_tuple){(a.x + b.x), (a.y + b.y), (a.z + b.z), VECTOR};
	return (result);
}

t_tuple	vec_subtraction(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if ((a.w != VECTOR) || (b.w != VECTOR))
		dbg_write("Warning: point in vector subtraction\n");
	result = (t_tuple){(a.x - b.x), (a.y - b.y), (a.z - b.z), VECTOR};
	return (result);
}
