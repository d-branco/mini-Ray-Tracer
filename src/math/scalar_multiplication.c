/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:22:09 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/22 14:31:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	vec_negation(t_tuple v)
{
	t_tuple	result;

	if (v.w != VECTOR)
		dbg_write("Warning: point intead of vector\n");
	result = vec_scalar_multiplication(-1.0, v);
	return (result);
}

t_tuple	vec_scalar_multiplication(float s, t_tuple v)
{
	t_tuple	result;

	if (v.w != VECTOR)
		dbg_write("Warning: point intead of vector\n");
	result = (t_tuple){(s * v.x), (s * v.y), (s * v.z), VECTOR};
	return (result);
}
