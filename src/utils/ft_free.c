/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:09:19 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/19 08:26:10 by abessa-m         ###   ########.fr       */
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
	if ((ptr) && (*ptr))
	{
		free(*ptr);
		if (dbg_write("Pointer at: "))
			ft_printf("%p points to %p. Now freed.\n", ptr, *ptr);
		if (dbg_write("Pointer at: "))
			ft_printf("%p ", ptr);
		*ptr = NULL;
		if (DEBUG)
			ft_printf("is set to %p.\n", *ptr);
	}
	else if (dbg_write("Hmmmmm, "))
		ft_printf("at %p there's no pointer to free!\n", ptr);
}

/* Requires DEBUG and TRUE macros
int	dbg_write(char *str)
{
	size_t	len;

	if (!DEBUG)
		return (FALSE);
	write(STDOUT_FILENO, "==DEBUG== ", 10);
	len = ft_strlen(str);
	write(STDOUT_FILENO, str, len);
	return (TRUE);
}*/
