/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 17:49:49 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 17:58:14 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static float	decimals(const char *nptr, size_t *j);

float	ft_atof(const char *str)
{
	float	nbr;
	float	sign;
	size_t	j;

	j = 0;
	while (str[j] == 32 || (str[j] >= 9 && str[j] <= 13))
		j++;
	sign = 1.0;
	if (str[j] == '+' || str[j] == '-')
	{
		if (str[j] == '-')
			sign = -1.0;
		j++;
	}
	nbr = 0.0;
	while (ft_isdigit(str[j]))
	{
		nbr = (10.0 * nbr) + (str[j] - '0');
		j++;
	}
	if (str[j] == '.')
		nbr += decimals(str, &j);
	nbr *= sign;
	return (nbr);
}

static float	decimals(const char *nptr, size_t *j)
{
	float	decimal;
	float	divisor;

	decimal = 0.0;
	divisor = 10.0;
	(*j)++;
	while (ft_isdigit(nptr[*j]))
	{
		decimal = decimal + ((nptr[*j] - '0') / divisor);
		divisor *= 10.0;
		(*j)++;
	}
	return (decimal);
}
