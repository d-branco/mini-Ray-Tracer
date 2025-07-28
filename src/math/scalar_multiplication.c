/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_multiplication.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:22:09 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 14:36:05 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	typedef struct s_vector
//	{
//		float					x;
//		float					y;
//		float					z;
//	}							t_vector;
t_vector	vec_negation(t_vector v)
{
	t_vector	result;

	result = vec_scalar_multiplication(-1.0, v);
	return (result);
}

t_vector	vec_scalar_multiplication(float s, t_vector v)
{
	t_vector	result;

	result = (t_vector){(s * v.x), (s * v.y), (s * v.z)};
	return (result);
}
