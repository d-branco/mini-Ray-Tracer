/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:25:32 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 08:27:43 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	debug_write(char *str)
{
	size_t	len;

	if (!DEBUG)
		return (FALSE);
	write(STDOUT_FILENO, "==DEBUG== ", 10);
	len = ft_strlen(str);
	write(STDOUT_FILENO, str, len);
	return (TRUE);
}
