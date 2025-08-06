/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:26:53 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/06 20:13:02 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float	vec_magnitude(t_tuple v)
{
	float	result;

	if (v.w != VECTOR)
		dbg_write("Warning: calculating magnitude to a point\n");
	result = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	return (result);
}

//returns a unit vector
t_tuple	vec_norm(t_tuple v)
{
	t_tuple	result;
	float	magnitude;

	if (v.w != VECTOR)
		dbg_write("Warning: point intead of vector\n");
	magnitude = vec_magnitude(v);
	result.x = v.x / magnitude;
	result.y = v.y / magnitude;
	result.z = v.z / magnitude;
	result.w = VECTOR;
	return (result);
}

//also known as the dot product
//the smaller the angle, the smaller
float	vec_inner_product(t_tuple a, t_tuple b)
{
	float	result;

	if ((a.w != VECTOR) || (b.w != VECTOR))
		dbg_write("Warning: calculating inner product with point\n");
	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (result);
}

t_tuple	vec_cross_product(t_tuple a, t_tuple b)
{
	t_tuple	result;

	if ((a.w != VECTOR) || (b.w != VECTOR))
		dbg_write("Warning: calculating inner product with point\n");
	result = (t_tuple){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x,
		VECTOR};
	return (result);
}
