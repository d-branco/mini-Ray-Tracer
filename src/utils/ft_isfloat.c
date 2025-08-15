/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isfloat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 18:35:32 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 19:34:06 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	skip_to_digit(const char *str);

int	ft_isfloat(const char *str)
{
	int	i;
	int	dot;
	int	digits;

	dot = 0;
	digits = 0;
	i = skip_to_digit(str);
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digits++;
		else if (str[i] == '.' && !dot)
			dot++;
		else if (!str[i] || ft_isspace(str[i]))
			break ;
		else
			return (0);
		i++;
	}
	return (digits);
}

static int	skip_to_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	return (i);
}
