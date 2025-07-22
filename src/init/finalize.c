/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/21 14:44:45 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_lstclear(t_lst_obj **lst);

void	finalize(t_scene *rt)
{
	debug_write("Finalizing\n");
	debug_write("Closing fd\n");
	close(rt->file_fd);
	debug_write("Destroying and freeing mlx pointers\n");
	if (rt->mlx_win)
		mlx_destroy_image(rt->mlx, rt->mlx_img);
	if (rt->mlx_win)
		mlx_destroy_window(rt->mlx, rt->mlx_win);
	if (rt->mlx)
		mlx_destroy_display(rt->mlx);
	ft_free_n_null(&(rt->mlx));
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
