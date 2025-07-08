/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:09:19 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/08 22:31:01 by abessa-m         ###   ########.fr       */
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
			if (DEBUG)
				ft_printf("Pointer at %p pointing to %p freed.\n", ptr, *ptr);
			if (DEBUG)
				ft_printf("Pointer at %p ", ptr);
			*ptr = NULL;
			if (DEBUG)
				ft_printf("set to %p.\n", *ptr);
		}
		else if (DEBUG)
			ft_printf("Hmmmmm, at %p there's no pointer to free!\n", ptr);
	}
}
