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

//	typedef struct s_vector
//	{
//		float					x;
//		float					y;
//		float					z;
//	}							t_vector;
t_vector	vec_addiction(t_vector a, t_vector b)
{
	t_vector	result;

	result = (t_vector){(a.x + b.x), (a.y + b.y), (a.z + b.z)};
	return (result);
}

t_vector	vec_subtraction(t_vector a, t_vector b)
{
	t_vector	result;

	result = (t_vector){(a.x - b.x), (a.y - b.y), (a.z - b.z)};
	return (result);
}

/*
//	cc src/math/addiction.c -I./include -o o && ./o
int	main(void)
{
	t_vector	a;
	t_vector	b;
	t_vector	result;

	a = (t_vector){1.0, 2.0, 3.0};
	b = (t_vector){4.0, 5.0, 6.0};
	result = vec_addiction(a, b);
	printf("Test 1 - Adding (1,2,3) + (4,5,6):\n");
	printf("Expected: (5.0, 7.0, 9.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	a = (t_vector){-1.0, 2.0, -3.0};
	b = (t_vector){1.0, -2.0, 3.0};
	result = vec_addiction(a, b);
	printf("Test 2 - Adding (-1,2,-3) + (1,-2,3):\n");
	printf("Expected: (0.0, 0.0, 0.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	a = (t_vector){5.0, -3.0, 2.5};
	b = (t_vector){0.0, 0.0, 0.0};
	result = vec_addiction(a, b);
	printf("Test 3 - Adding (5,-3,2.5) + (0,0,0):\n");
	printf("Expected: (5.0, -3.0, 2.5)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n\n", result.x, result.y, result.z);
	a = (t_vector){5.0, 7.0, 9.0};
	b = (t_vector){1.0, 2.0, 3.0};
	result = vec_subtraction(a, b);
	printf("Test 1 - Subtracting (5,7,9) - (1,2,3):\n");
	printf("Expected: (4.0, 5.0, 6.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	a = (t_vector){1.0, 2.0, 3.0};
	b = (t_vector){4.0, 5.0, 6.0};
	result = vec_subtraction(a, b);
	printf("Test 2 - Subtracting (1,2,3) - (4,5,6):\n");
	printf("Expected: (-3.0, -3.0, -3.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	a = (t_vector){5.0, -3.0, 2.5};
	b = (t_vector){5.0, -3.0, 2.5};
	result = vec_subtraction(a, b);
	printf("Test 3 - Subtracting (5,-3,2.5) - (5,-3,2.5):\n");
	printf("Expected: (0.0, 0.0, 0.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	a = (t_vector){3.0, -1.0, 4.0};
	b = (t_vector){0.0, 0.0, 0.0};
	result = vec_subtraction(a, b);
	printf("Test 4 - Subtracting (3,-1,4) - (0,0,0):\n");
	printf("Expected: (3.0, -1.0, 4.0)\n");
	printf("Got:      (%.1f, %.1f, %.1f)\n", result.x, result.y, result.z);
	return (EXIT_SUCCESS);
}*/
