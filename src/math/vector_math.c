/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_math.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:26:53 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 14:57:42 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	typedef struct s_vector
//	{
//		float					x;
//		float					y;
//		float					z;
//	}							t_vector;
float	vec_magnitude(t_vector v)
{
	float	result;

	result = sqrtf(powf(v.x, 2) + powf(v.y, 2) + powf(v.z, 2));
	return (result);
}

//returns a unit vector
t_vector	vec_normalization(t_vector v)
{
	t_vector	result;
	float		magnitude;

	magnitude = vec_magnitude(v);
	result.x = v.x / magnitude;
	result.y = v.y / magnitude;
	result.z = v.z / magnitude;
	return (result);
}

//also known as the dot product
//the smaller the angle, the smaller
float	vec_inner_product(t_vector a, t_vector b)
{
	float	result;

	result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return (result);
}

t_vector	vec_cross_product(t_vector a, t_vector b)
{
	t_vector	result;

	result = (t_vector){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x};
	return (result);
}

/*
//	cc -Wall -Wextra src/math/vector_math.c -I./include -lm -o o && ./o
void	print_vector(const char* name, t_vector v)
{
	printf("%s: (%.3f, %.3f, %.3f)\n", name, v.x, v.y, v.z);
}

int	main(void)
{
	printf("=== Vector Function Tests ===\n\n");
	t_vector v1 = {3.0f, 4.0f, 0.0f};// Simple 3-4-5 triangle
	t_vector v2 = {1.0f, 0.0f, 0.0f};// Unit vector along x-axis
	t_vector v3 = {0.0f, 1.0f, 0.0f};// Unit vector along y-axis
	t_vector v4 = {1.0f, 1.0f, 1.0f};// Equal components
	t_vector v5 = {0.0f, 0.0f, 0.0f};// Zero vector
	printf("Test vectors:\n");
	print_vector("v1", v1);
	print_vector("v2", v2);
	print_vector("v3", v3);
	print_vector("v4", v4);
	print_vector("v5", v5);
	printf("\n");
	printf("--- Magnitude Tests ---\n");
	printf("Magnitude of v1 (3,4,0): %.3f (expected: 5.000)\n",
		vec_magnitude(v1));
	printf("Magnitude of v2 (1,0,0): %.3f (expected: 1.000)\n",
		vec_magnitude(v2));
	printf("Magnitude of v4 (1,1,1): %.3f (expected: 1.732)\n",
		vec_magnitude(v4));
	printf("Magnitude of v5 (0,0,0): %.3f (expected: 0.000)\n",
		vec_magnitude(v5));
	printf("\n");
	printf("--- Normalization Tests ---\n");
	t_vector norm_v1 = vec_normalization(v1);
	t_vector norm_v4 = vec_normalization(v4);
	print_vector("Normalized v1", norm_v1);
	printf("Magnitude of normalized v1: %.3f (should be ~1.000)\n",
		vec_magnitude(norm_v1));
	print_vector("Normalized v4", norm_v4);
	printf("Magnitude of normalized v4: %.3f (should be ~1.000)\n",
		vec_magnitude(norm_v4));
	printf("\n");
	printf("--- Inner Product Tests ---\n");
	printf("v1 · v2: %.3f\n", vec_inner_product(v1, v2));
	printf("v2 · v3: %.3f (perpendicular vectors, should be 0.000)\n",
		vec_inner_product(v2, v3));
	printf("v1 · v1: %.3f (should equal magnitude squared: %.3f)\n",
			vec_inner_product(v1, v1), powf(vec_magnitude(v1), 2));
	printf("v4 · v4: %.3f\n", vec_inner_product(v4, v4));
	printf("\n");
	printf("--- Cross Product Tests ---\n");
	t_vector cross_v2_v3 = vec_cross_product(v2, v3);
	t_vector cross_v3_v2 = vec_cross_product(v3, v2);
	print_vector("v2 × v3", cross_v2_v3);
	print_vector("v3 × v2", cross_v3_v2);
	printf("Note: v3 × v2 should be negative of v2 × v3\n");
	printf("(v2 × v3) · v2: %.3f (should be 0.000)\n",
		vec_inner_product(cross_v2_v3, v2));
	printf("(v2 × v3) · v3: %.3f (should be 0.000)\n",
		vec_inner_product(cross_v2_v3, v3));
	printf("\n");
	printf("--- Edge Case Tests ---\n");
	printf("Cross product with zero vector:\n");
	t_vector cross_zero = vec_cross_product(v1, v5);
	print_vector("v1 × zero_vector", cross_zero);
	printf("Cross product of parallel vectors (should be zero):\n");
	t_vector v1_scaled = {6.0f, 8.0f, 0.0f};  // v1 * 2
	t_vector cross_parallel = vec_cross_product(v1, v1_scaled);
	print_vector("v1 × (2*v1)", cross_parallel);
	return (0);
}*/
