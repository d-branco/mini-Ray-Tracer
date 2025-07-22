/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append_chr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 14:51:56 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/22 14:52:31 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*append_chr(char *str, char c)
{
	char	tmp[2];
	char	*ret;

	tmp[0] = c;
	tmp[1] = '\0';
	ret = ft_strjoin(str, tmp);
	free(str);
	return (ret);
}
