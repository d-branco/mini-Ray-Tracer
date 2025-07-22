/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/21 14:44:38 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_s_scene(t_scene *rt);
static void	print_obj_list(t_lst_obj **head);

int	initialize_scene(t_scene *rt, char **argv)
{
	debug_write("Initializing the struct scene\n");
	rt->amb_ratio = -1;
	rt->cam_fov = -1;
	rt->light_brightness = -1;
	rt->lst_obj = NULL;
	rt->mlx = NULL;
	rt->mlx_win = NULL;
	rt->mlx_img = NULL;
	rt->mlx_addr = NULL;
	if (parse_input(rt, argv) != EXIT_SUCCESS)
		return (debug_write("ERROR: Parsing input\n"), 1);
	debug_print_s_scene(rt);
	return (EXIT_SUCCESS);
}

//		ft_printf("s_scene: ligh_rgb: %i,%i,%i\n", (int) rt->light_rgb_rng[0],
//			(int) rt->light_rgb_rng[1], (int) rt->light_rgb_rng[2]);
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
	print_obj_list(&(rt->lst_obj));
}

static void	print_obj_list(t_lst_obj **head)
{
	t_lst_obj	*o;
	const char	*str[] = {"sphere  (   )", "plane ///////", "cylinder(\\ )\\"};

	o = *head;
	if (!o || !DEBUG)
		return ;
	while (o)
	{
		ft_printf("==DEBUG== obj_lst id: %s at: %p\n", str[o->id], o);
		if ((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst center: %i,%i,%i\n",
				(int)o->center[0], (int)o->center[1], (int)o->center[2]);
		if ((o->id == e_SPHERE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst diameter: %i\n", (int)o->diameter);
		if ((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst rgb range: %i,%i,%i\n",
				(int)o->rgb_rng[0], (int)o->rgb_rng[1], (int)o->rgb_rng[2]);
		if ((o->id == e_PLANE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst vec_uni: %i,%i,%i\n",
				(int)o->vec_uni[0], (int)o->vec_uni[1], (int)o->vec_uni[2]);
		if (o->id == e_CYlINDER)
			ft_printf("==DEBUG== obj_lst height: %i\n", (int)o->height);
		ft_printf("==DEBUG== obj_lst ======== next obj at: %p\n", o->next);
		o = o->next;
	}
}
