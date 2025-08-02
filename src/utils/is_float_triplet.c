/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_float_triplet.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 20:37:04 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 09:36:58 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	skip_to_digit(const char *str);
static int	reset_counters(int *dot, int *digit, int *comma, char sign);
static void	print_triplet(char *str);

int	is_float_triplet(char *str)
{
	int	i;
	int	dot;
	int	digit;
	int	comma;

	dbg_write("Is it a float_triplet: ");
	if (DEBUG)
		print_triplet(str);
	comma = -1;
	reset_counters(&dot, &digit, &comma, ' ');
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
			i += reset_counters(&dot, &digit, &comma, str[i + 1]);
		else
			return (dbg_write("It is NOT a float_triplet!\n"), FALSE);
	}
	return (dbg_write("It is a float_triplet!\n"), TRUE);
}

static void	print_triplet(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ',' || str[i] == '.' || ft_isdigit(str[i]))
	{
		ft_putchar_fd(str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}

static int	reset_counters(int *dot, int *digit, int *comma, char sign)
{
	*dot = 0;
	*digit = 0;
	*comma = *comma + 1;
	if (sign == '+' || sign == '-')
		return (1);
	return (0);
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
