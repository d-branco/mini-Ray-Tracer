/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/10 15:53:56 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		initialize(t_rt *rt);

int	main(int argc, char **argv)
{
	t_rt	rt;

	debug_write("Hello, friend\n");
	if (input_validation(argc, argv, &rt) != 0)
		return (debug_write("Goodbye, friend\n"), 2);
	initialize(&rt);
	finalize(&rt);
	return (debug_write("Goodbye, friend\n"), 0);
}

void	initialize(t_rt *rt)
{
	(void) rt;
	return ;
}
