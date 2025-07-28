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
	if (((a - b) < MOE) && ((a - b) > (0 - MOE)))
		return (TRUE);
	return (FALSE);
}

/*
//	cc src/math/comparisson.c -I./include -o o && ./o
int	main(void)
{
	float	a;
	float	b;

	a = 42;
	b = a - (MOE / 2);
	write(1, "Should be EQUAL:\n", 17);
	if (fl_equal(a, b))
		write(1, "          EQUAL\n", 16);
	else
		write(1, "          NOT EQUAL\n", 20);
	b = a - (MOE * 2);
	write(1, "Should be NOT EQUAL:\n", 21);
	if (fl_equal(a, b))
		write(1, "          EQUAL\n", 16);
	else
		write(1, "          NOT EQUAL\n", 20);
	return (EXIT_SUCCESS);
}*/
