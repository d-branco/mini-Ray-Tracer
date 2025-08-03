/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m4_transformations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 17:49:44 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/03 18:35:04 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_m4	translation(t_tuple t)
{
	t_m4	ret;

	ret = (t_m4){{
	{1, 0, 0, t.x},
	{0, 1, 0, t.y},
	{0, 0, 1, t.z},
	{0, 0, 0, 1}
	}};
	return (ret);
}

t_m4	scaling(t_tuple t)
{
	t_m4	ret;

	if (t.x == 0.0f || t.y == 0.0f || t.z == 0.0f)
	{
		dbg_write_code("Error:\nDivision by 0", RED);
		ret = (t_m4){{
		{1, 0, 0, 0},
		{0, 1, 0, 0},
		{0, 0, 1, 0},
		{0, 0, 0, 1}
		}};
	}
	else
		ret = (t_m4){{
		{t.x, 0, 0, 0},
		{0, t.y, 0, 0},
		{0, 0, t.z, 0},
		{0, 0, 0, 1}
		}};
	return (ret);
}

t_m4	rotate_x(float rad)
{
	t_m4	ret;

	ret = (t_m4){{
	{1, 0, 0, 0},
	{0, cosf(rad), -sinf(rad), 0},
	{0, sinf(rad), cosf(rad), 0},
	{0, 0, 0, 1}
	}};
	return (ret);
}

t_m4	rotate_y(float rad)
{
	t_m4	ret;

	ret = (t_m4){{
	{cosf(rad), 0, sinf(rad), 0},
	{0, 1, 0, 0},
	{-sinf(rad), 0, cosf(rad), 0},
	{0, 0, 0, 1}
	}};
	return (ret);
}

t_m4	rotate_z(float rad)
{
	t_m4	ret;

	ret = (t_m4){{
	{cosf(rad), -sinf(rad), 0, 0},
	{sinf(rad), cosf(rad), 0, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 1}
	}};
	return (ret);
}
