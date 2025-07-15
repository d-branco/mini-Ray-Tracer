/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 11:30:55 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_scene	rt;

	debug_write("Hello, friend\n");
	if (input_validation(argc, argv) != 0)
		return (debug_write("Goodbye, friend\n"), 2);
	initialize(&rt, argv);
	finalize(&rt);
	return (debug_write("Goodbye, friend\n"), 0);
}
