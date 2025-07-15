/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 11:27:30 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_s_scene(t_scene *rt);

void	initialize(t_scene *rt, char **argv)
{
	debug_write("Initializing the struct scene\n");
	if (parse_input(rt, argv) != EXIT_SUCCESS)
		return ;
	debug_print_s_scene(rt);
	return ;
}

static void	debug_print_s_scene(t_scene *rt)
{
	if (DEBUG)
	{
		debug_write("s_scene: file_fd: ");
		ft_putnbr_fd(rt->file_fd, 1);
		ft_putchar_fd('\n', 1);
	}
}
