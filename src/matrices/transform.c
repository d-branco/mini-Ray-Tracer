/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:58:20 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/05 10:58:23 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_transform(t_ray ray, t_m4 matrix)
{
	t_ray	ret;

	ret = (t_ray){m4_tuple_multiplication(matrix, ray.origin),
		m4_tuple_multiplication(matrix, ray.direction)};
	return (ret);
}

/*void	temp_testing(t_scene *rt)
{
	t_ray	ray;
	t_m4	m;
	t_ray	r2;

	(void) rt;
	ray = (t_ray){mk_pnt(1, 2, 3), mk_vec(0, 1, 0)};
	m = (t_m4)translation(mk_vec(3, 4, 5));
	r2 = ray_transform(ray, m);
	tuple_print(mk_pnt(4, 6, 8));
	tuple_print(r2.origin);
	if (tuple_equal(r2.origin, mk_pnt(4, 6, 8)))
		write(1, "Correct  1\n", 11);
	else
		write(1, " ERROR   1\n", 11);
	tuple_print(mk_vec(0, 1, 0));
	tuple_print(r2.direction);
	if (tuple_equal(r2.direction, mk_vec(0, 1, 0)))
		write(1, "Correct  2\n", 11);
	else
		write(1, " ERROR   2\n", 11);
	ray = (t_ray){mk_pnt(1, 2, 3), mk_vec(0, 1, 0)};
	m = (t_m4)scaling(mk_vec(2, 3, 4));
	r2 = ray_transform(ray, m);
	tuple_print(mk_pnt(2, 6, 12));
	tuple_print(r2.origin);
	if (tuple_equal(r2.origin, mk_pnt(2, 6, 12)))
		write(1, "Correct  3\n", 11);
	else
		write(1, " ERROR   3\n", 11);
	tuple_print(mk_vec(0, 3, 0));
	tuple_print(r2.direction);
	if (tuple_equal(r2.direction, mk_vec(0, 3, 0)))
		write(1, "Correct  4\n", 11);
	else
		write(1, " ERROR   4\n", 11);
}*/
