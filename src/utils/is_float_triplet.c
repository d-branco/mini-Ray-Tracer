/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float_triplet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:37:04 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 20:45:35 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	skip_to_digit(const char *str);
static void	reset_counters(int *dot, int *digit);

int	is_float_triplet(char *str)
{
	int	i;
	int	dot;
	int	digit;
	int	comma;

	reset_counters(&dot, &digit);
	comma = 0;
	i = skip_to_digit(str);
	while (str[++i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			digit++;
		else if (str[i] == '.' && !dot)
			dot++;
		else if ((!str[i] || ft_isspace(str[i])) && (comma == 2) && (digit > 0))
			break ;
		else if (str[i] == ',' && (digit > 0))
		{
			comma++;
			reset_counters(&dot, &digit);
		}
		else
			return (debug_write("Invalid float_triplet!\n"), FALSE);
	}
	return (debug_write("Valid float_triplet!\n"), TRUE);
}

static void	reset_counters(int *dot, int *digit)
{
	*dot = 0;
	*digit = 0;
}

static int	skip_to_digit(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	i--;
	return (i);
}
