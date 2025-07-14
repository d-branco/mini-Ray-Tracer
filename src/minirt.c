/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/14 16:01:12 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		initialize(t_scene *rt);

int	main(int argc, char **argv)
{
	t_scene	rt;

	debug_write("Hello, friend\n");
	initialize(&rt);
	if (input_validation(argc, argv, &rt) != 0)
		return (debug_write("Goodbye, friend\n"), 2);
	finalize(&rt);
	return (debug_write("Goodbye, friend\n"), 0);
}

void	initialize(t_scene *rt)
{
	(void) rt;
	debug_write("Initializing the struct scene all to NULL\n");
	return ;
}
