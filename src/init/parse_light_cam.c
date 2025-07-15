/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:35:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 20:30:49 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_ambient_light(char *line, t_scene **rt);

int			is_float_triplet(char *str);
static int	skip_to_digit(const char *str);

int	parse_lights_and_camera(char *line, t_scene **rt)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((line[0] == 'A') && ((*rt)->amb_ratio == -1))
		ret += parse_ambient_light(line, rt);
	else if (line[0] == 'A')
		return (ft_putstr_fd("ERROR: Ambient light can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if (line[0] == 'C')
		debug_write("identified: Capital letter \'C\'!\n");
	else if (line[0] == 'L')
		debug_write("identified: Capital letter \'L\'!\n");
	debug_write("TODO: Check if only one and validate\n");
	return (ret);
}

static int	parse_ambient_light(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'A\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: "
				"invalid Ambient light ratio (float)\n", 2), EXIT_FAILURE);
	(*rt)->amb_ratio = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: "
				"invalid Ambient light RGB (int,int,int)\n", 2), EXIT_FAILURE);
	(*rt)->amb_rgb_range[0] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_range[1] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_range[2] = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: "
				"invalid Ambient light\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	is_float_triplet(char *str)
{
	int	i;
	int	dot;
	int	digit;
	int	comma;

	debug_write("Is it a float_triplet: ");
	ft_putstr_fd(str, 1);
	dot = 0;
	digit = 0;
	comma = 0;
	i = skip_to_digit(str);
	while (str[i])
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
			digit = 0;
			dot = 0;
		}
		else
			return (debug_write("It is NOT a float_triplet!\n"), 0);
		i++;
	}
	return (debug_write("It is a float_triplet!\n"), TRUE);
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
