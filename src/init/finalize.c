/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 16:23:05 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_lstclear(t_lst_obj **lst);

void	finalize(t_scene *rt)
{
	debug_write("Finalizing\n");
	debug_write("Destroying and freeing mlx pointers\n");
	mlx_destroy_window(rt->mlx, rt->mlx_win);
	mlx_destroy_display(rt->mlx);
	free(rt->mlx);
	debug_write("Freeing object list\n");
	rt_lstclear(&(rt->lst_obj));
	debug_write("Goodbye, friend\n");
	exit(EXIT_SUCCESS);
}

static void	rt_lstclear(t_lst_obj **lst)
{
	t_lst_obj	*current;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		current = (*lst)->next;
		free(*lst);
		*lst = current;
	}
	*lst = NULL;
}
