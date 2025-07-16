/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 14:01:30 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 20:15:52 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	rt_lstclear(t_lst_obj **lst);

void	finalize(t_scene *rt)
{
	debug_write("Finalizing the struct scene\n");
	close(rt->file_fd);
	debug_write("Freeing object list\n");
	rt_lstclear(&(rt->lst_obj));
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
