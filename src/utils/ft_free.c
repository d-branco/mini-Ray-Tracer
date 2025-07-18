/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:09:19 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 16:48:46 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

//	Alternative to:
//		free(ptr);
//		ptr = NULL;

//	Usage:
//		ft_free_n_null((void **)&ptr);
void	ft_free_n_null(void **ptr)
{
	if (ptr)
	{
		if (*ptr)
		{
			free(*ptr);
			if (debug_write("Pointer at: "))
				ft_printf("%p points to %p. Now freed.\n", ptr, *ptr);
			if (debug_write("Pointer at: "))
				ft_printf("%p ", ptr);
			*ptr = NULL;
			if (DEBUG)
				ft_printf("is set to %p.\n", *ptr);
		}
		else if (debug_write("Hmmmmm, "))
			ft_printf("at %p there's no pointer to free!\n", ptr);
	}
}
