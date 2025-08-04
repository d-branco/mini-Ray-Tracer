/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:07 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/04 21:08:44 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	debug_print_s_scene(t_scene *rt);
static void	print_obj_list(t_lst_obj **head);

int	initialize_scene(t_scene *rt, char **argv)
{
	dbg_write("Initializing the struct scene\n");
	rt->a_ratio = -1.0f;
	rt->c_fov = -1.0f;
	rt->l_bri = -1.0f;
	rt->lst_obj = NULL;
	rt->mlx = NULL;
	rt->mlx_win = NULL;
	rt->mlx_img = NULL;
	rt->mlx_addr = NULL;
	rt->edge = MAP_RESOLUTION;
	if (parse_input(rt, argv) != EXIT_SUCCESS)
		return (dbg_write("ERROR: Parsing input\n"), 1);
	rt->mlx = mlx_init();
	dbg_write_code("Initiating miniLibX\n", PURPLE);
	if (mlx_initialize(rt) != EXIT_SUCCESS)
		return (dbg_write("Goodbye, friend\n"), 4);
	initialize_map(rt);
	debug_print_s_scene(rt);
	dbg_write("rad: Correcting degrees to radians\n");
	rt->c_fov = (rt->c_fov) * (TAU / 360.0);
	if (dbg_write(""))
		ft_printf("rad: s_scene: c_fov %i,%i rad\n",
			(int)(rt->c_fov), (((int)(rt->c_fov * 100)) % 100));
	return (EXIT_SUCCESS);
}

//		ft_printf("s_scene: ligh_rgb: %i,%i,%i\n", (int) rt->l_rgb[0],
//			(int) rt->l_rgb[1], (int) rt->l_rgb[2]);
static void	debug_print_s_scene(t_scene *rt)
{
	if (!DEBUG)
		return ;
	dbg_write("");
	ft_printf("s_scene: file_fd: %i\n", rt->file_fd);
	dbg_write("");
	ft_printf("s_scene: a_ratio: %i.%i\n", (int) rt->a_ratio,
		(((int)(rt->a_ratio * 100)) % 100));
	dbg_write("");
	ft_printf("s_scene: amb_rgb: %i,%i,%i\n", (int) rt->a_rgb.r,
		(int) rt->a_rgb.g, (int) rt->a_rgb.b);
	dbg_write("");
	ft_printf("s_scene: c_coord: %i,%i,%i\n", (int) rt->c_coord.x,
		(int) rt->c_coord.y, (int) rt->c_coord.z);
	dbg_write("");
	ft_printf("s_scene: c_orient: %i,%i,%i\n", (int) rt->c_ori.x,
		(int) rt->c_ori.y, (int) rt->c_ori.z);
	dbg_write("");
	ft_printf("s_scene: c_fov %i degrees\n", (int)rt->c_fov);
	dbg_write("");
	ft_printf("s_scene: l_coo: %i,%i,%i\n", (int) rt->l_coo.x,
		(int) rt->l_coo.y, (int) rt->l_coo.z);
	dbg_write("");
	ft_printf("s_scene: lig_brit: %i.%i\n", (int)rt->l_bri,
		(((int)(rt->l_bri * 100)) % 100));
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
				(int)o->center.x, (int)o->center.y, (int)o->center.z);
		if ((o->id == e_SPHERE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst diameter: %i\n", (int)o->diameter);
		if ((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst rgb range: %i,%i,%i\n",
				(int)o->rgb_rng.r, (int)o->rgb_rng.g, (int)o->rgb_rng.b);
		if ((o->id == e_PLANE) || (o->id == e_CYlINDER))
			ft_printf("==DEBUG== obj_lst vec_uni: %i,%i,%i\n",
				(int)o->vec_uni.x, (int)o->vec_uni.y, (int)o->vec_uni.z);
		if (o->id == e_CYlINDER)
			ft_printf("==DEBUG== obj_lst height: %i\n", (int)o->height);
		ft_printf("==DEBUG== obj_lst ======== next obj at: %p\n", o->next);
		o = o->next;
	}
}

void	initialize_map(t_scene *rt)
{
	int	x;
	int	y;

	dbg_write("Initiating the map\n");
	x = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			rt->map[x][y] = -1;
			y++;
		}
		x++;
	}
	color_screen(rt, encode_rgb(rt->a_rgb.r, rt->a_rgb.g, rt->a_rgb.b));
}
