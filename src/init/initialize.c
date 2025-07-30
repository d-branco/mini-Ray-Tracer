/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/30 12:00:13 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_s_scene(t_scene rt);
static void	print_obj_list(t_lst_obj **head);
static void	initialize_map(int map[WIDTH][HEIGHT]);

int	initialize_scene(t_scene *rt, char **argv)
{
	debug_write("Initializing the struct scene\n");
	rt->a_ratio = -1;
	rt->c_fov = -1;
	rt->l_bri = -1;
	rt->lst_obj = NULL;
	rt->mlx = NULL;
	rt->mlx_win = NULL;
	rt->mlx_img = NULL;
	rt->mlx_addr = NULL;
	initialize_map(rt->map);
	if (parse_input(rt, argv) != EXIT_SUCCESS)
		return (debug_write("ERROR: Parsing input\n"), 1);
	debug_print_s_scene(*rt);
	debug_write("Correcting degrees to radians\n");
	rt->c_fov = (rt->c_fov) * (TAU / 360.0);
	if (debug_write(""))
		ft_printf("s_scene: c_fov %i,%i rad\n",
			(int)(rt->c_fov), (((int)(rt->c_fov * 100)) % 100));
	return (EXIT_SUCCESS);
}

//		ft_printf("s_scene: ligh_rgb: %i,%i,%i\n", (int) rt->l_rgb[0],
//			(int) rt->l_rgb[1], (int) rt->l_rgb[2]);
static void	debug_print_s_scene(t_scene rt)
{
	if (!DEBUG)
		return ;
	debug_write("");
	ft_printf("s_scene: file_fd: %i\n", rt.file_fd);
	debug_write("");
	ft_printf("s_scene: a_ratio: %i.%i\n", (int) rt.a_ratio,
		(((int)(rt.a_ratio * 100)) % 100));
	debug_write("");
	ft_printf("s_scene: amb_rgb: %i,%i,%i\n", (int) rt.a_rgb.r,
		(int) rt.a_rgb.g, (int) rt.a_rgb.b);
	debug_write("");
	ft_printf("s_scene: c_coord: %i,%i,%i\n", (int) rt.c_coord.x,
		(int) rt.c_coord.y, (int) rt.c_coord.z);
	debug_write("");
	ft_printf("s_scene: c_orient: %i,%i,%i\n", (int) rt.c_ori.x,
		(int) rt.c_ori.y, (int) rt.c_ori.z);
	debug_write("");
	ft_printf("s_scene: c_fov %i degrees\n", (int)rt.c_fov);
	debug_write("");
	ft_printf("s_scene: l_coo: %i,%i,%i\n", (int) rt.l_coo.x,
		(int) rt.l_coo.y, (int) rt.l_coo.z);
	debug_write("");
	ft_printf("s_scene: lig_brit: %i.%i\n", (int)rt.l_bri,
		(((int)(rt.l_bri * 100)) % 100));
	print_obj_list(&(rt.lst_obj));
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

static void	initialize_map(int map[WIDTH][HEIGHT])
{
	int	x;
	int	y;

	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			map[x][y] = -1;
			y++;
		}
		x++;
	}
}
