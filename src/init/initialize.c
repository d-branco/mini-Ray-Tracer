/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 18:10:56 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_s_scene(t_scene *rt);

void	initialize(t_scene *rt, char **argv)
{
	debug_write("Initializing the struct scene\n");
	rt->amb_ratio = -1;
	rt->cam_fov = -1;
	rt->light_brightness = -1;
	if (parse_input(rt, argv) != EXIT_SUCCESS)
		return ;
	debug_print_s_scene(rt);
	return ;
}

//		ft_printf("s_scene: ligh_rgb: %i,%i,%i\n", (int) rt->light_rgb_range[0],
//			(int) rt->light_rgb_range[1], (int) rt->light_rgb_range[2]);
static void	debug_print_s_scene(t_scene *rt)
{
	if (!DEBUG)
		return ;
	debug_write("");
	ft_printf("s_scene: file_fd: %i\n", rt->file_fd);
	debug_write("");
	ft_printf("s_scene: amb_ratio: %i.%i\n", (int) rt->amb_ratio,
		(((int)(rt->amb_ratio * 100)) % 100));
	debug_write("");
	ft_printf("s_scene: amb_rgb: %i,%i,%i\n", (int) rt->amb_rgb_rng[0],
		(int) rt->amb_rgb_rng[1], (int) rt->amb_rgb_rng[2]);
	debug_write("");
	ft_printf("s_scene: cam_coord: %i,%i,%i\n", (int) rt->cam_coord[0],
		(int) rt->cam_coord[1], (int) rt->cam_coord[2]);
	debug_write("");
	ft_printf("s_scene: cam_orient: %i,%i,%i\n", (int) rt->cam_orient[0],
		(int) rt->cam_orient[1], (int) rt->cam_orient[2]);
	debug_write("");
	ft_printf("s_scene: cam_fov %i\n", (int)rt->cam_fov);
	debug_write("");
	ft_printf("s_scene: light_coord: %i,%i,%i\n", (int) rt->light_coord[0],
		(int) rt->light_coord[1], (int) rt->light_coord[2]);
	debug_write("");
	ft_printf("s_scene: lig_brit: %i.%i\n", (int)rt->light_brightness,
		(((int)(rt->light_brightness * 100)) % 100));
}
