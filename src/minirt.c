/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/04 21:03:26 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	temp_testing(t_scene *rt);

int	main(int argc, char **argv)
{
	t_scene	rt;

	dbg_write("Hello, friend\n");
	if (input_validation(argc, argv) != 0)
		return (dbg_write("Goodbye, friend\n"), 2);
	if (initialize_scene(&rt, argv) != EXIT_SUCCESS)
		return (finalize(&rt), dbg_write("Goodbye, friend\n"), 3);
	mlx_hook(rt.mlx_win, 17, 0, close_win_button, &rt);
	mlx_hook(rt.mlx_win, 2, 1L << 0, key_hook, &rt);
	temp_testing(&rt);
	mlx_loop_hook(rt.mlx, &old_looping_loop, &rt);
	mlx_loop(rt.mlx);
	return (dbg_write("ERROR: return from main()\n"), EXIT_FAILURE);
}

static void	temp_testing(t_scene *rt)
{
	(void) rt;
}

/*static void	temp_testing(t_scene *rt)
{
	t_ray		ray;
	t_lst_obj	sp;
	t_lst_obj	*ptr;
	t_intersect	xs;

	(void) rt;
	(void) ray;
	ft_printf("\n TEST starts\n");
	ray = (t_ray){mk_pnt(0, 0, 0), mk_vec(0, 0, 1)};
	sp = (t_lst_obj){0, mk_pnt(0, 0, 0), 2.0f, (t_rgb){42, 42, 42},
		mk_vec(1, 1, 1), 0.0f, (t_intersect){0, {0, 0}}, NULL};
	ptr = &sp;
	if (!sp.next)
		ft_printf("Sempre escreve!\n");
	print_obj_list(&ptr);
	sp_intersect(ptr, ray);
	xs = ptr->intersect;
	ft_printf("xs.count: %i\n", xs.count);
	ft_printf("ptr->intersect.count: %i\n", ptr->intersect.count);
	if (ptr->intersect.count == 2)
	{
		ft_printf("[x] ");
		if (fl_equal(xs.dst[0], -1.0f))
			ft_printf("[x] ");
		else
			ft_printf("[ ] ");
		if (fl_equal(xs.dst[1], 1.0f))
			ft_printf("[x] ");
		else
			ft_printf("[ ] ");
	}
	else
		ft_printf("[ ] ");
	ft_printf(" TEST ends\n\n");
	ft_printf("\n TEST starts\n");
	ray = (t_ray){mk_pnt(0, 0, 5), mk_vec(0, 0, 1)};
	sp = (t_lst_obj){0, mk_pnt(0, 0, 0), 2.0f, (t_rgb){42, 42, 42},
		mk_vec(1, 1, 1), 0.0f, (t_intersect){0, {0, 0}}, NULL};
	ptr = &sp;
	if (!sp.next)
		ft_printf("Sempre escreve!\n");
	print_obj_list(&ptr);
	sp_intersect(ptr, ray);
	xs = ptr->intersect;
	ft_printf("xs.count: %i\n", xs.count);
	ft_printf("ptr->intersect.count: %i\n", ptr->intersect.count);
	if (ptr->intersect.count == 2)
	{
		ft_printf("[x] ");
		if (fl_equal(xs.dst[0], -6.0f))
			ft_printf("[x] ");
		else
			ft_printf("[ ] ");
		if (fl_equal(xs.dst[1], -4.0f))
			ft_printf("[x] ");
		else
			ft_printf("[ ] ");
	}
	else
		ft_printf("[ ] ");
	ft_printf(" TEST ends\n\n");
}*/

/*
typedef struct s_lst_obj
{
	int						id;
	struct s_tuple			center;
	float					diameter;
	struct s_rgb			rgb_rng;
	struct s_tuple			vec_uni;
	float					height;
	struct s_intersect		intersect;
	struct s_lst_obj		*next;
}							t_lst_obj;
*/
