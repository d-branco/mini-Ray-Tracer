/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:35:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/28 18:12:34 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_camera(char *line, t_scene **rt);
static int	parse_ambient_light(char *line, t_scene **rt);
static int	validate_value_range(t_scene **rt);
static int	parse_light(char *line, t_scene **rt);

int	parse_lights_and_camera(char *line, t_scene **rt)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((line[0] == 'A') && ((*rt)->amb_ratio == -1))
		ret += parse_ambient_light(line, rt);
	else if (line[0] == 'A')
		return (ft_putstr_fd("Error\nAmbient light can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if ((line[0] == 'C') && ((*rt)->c_fov == -1))
		ret += parse_camera(line, rt);
	else if (line[0] == 'C')
		return (ft_putstr_fd("Error\nCamera can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if ((line[0] == 'L') && ((*rt)->light_brightness == -1))
		ret += parse_light(line, rt);
	else if (line[0] == 'L')
		return (ft_putstr_fd("Error\nLight can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	ret += validate_value_range(rt);
	return (ret);
}

static int	parse_light(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'L\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->light_brightness = -2, ft_putstr_fd("Error\ninvali"
				"d Light coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->light_coord);
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->light_brightness = -2, ft_putstr_fd("Error\ninvali"
				"d Light ratio range (float)\n", 2), EXIT_FAILURE);
	(*rt)->light_brightness = ft_atof(line);
	line = skip_to_next_word(line);
	parse_float_triplet("-1,-1,-1", (*rt)->light_rgb_rng);
	if (line && ft_isprint(*line))
	{
		if (!is_float_triplet(line))
			return ((*rt)->light_brightness = -2, ft_putstr_fd("Error\n"
					"invalid Light\n", 2), EXIT_FAILURE);
		parse_float_triplet(line, (*rt)->light_rgb_rng);
		line = skip_to_next_word(line);
	}
	if (line && ft_isprint(*line))
		return ((*rt)->light_brightness = -2, ft_putstr_fd("Error\n"
				"invalid Light\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_camera(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'C\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("Error\ninvalid Camera "
				"coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->c_coord);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->c_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"orientation (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->c_orient);
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->c_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"field of view (float)\n", 2), EXIT_FAILURE);
	(*rt)->c_fov = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->c_fov = -2, ft_putstr_fd("Error\n"
				"invalid Camera\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_ambient_light(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'A\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("Error\n"
				"invalid Ambient light ratio (float)\n", 2), EXIT_FAILURE);
	(*rt)->amb_ratio = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("Error\ninvalid "
				"Ambient light RGB (float,float,float)\n", 2), EXIT_FAILURE);
	(*rt)->amb_rgb_rng[0] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_rng[1] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_rng[2] = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("Error\n"
				"invalid Ambient light\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	validate_value_range(t_scene **rt)
{
	if (((*rt)->amb_ratio != -1)
		&& (((*rt)->amb_ratio < 0.0) || ((*rt)->amb_ratio > 1.0)
			|| ((*rt)->amb_rgb_rng[0] < 0.0) || ((*rt)->amb_rgb_rng[0] > 255.0)
			|| ((*rt)->amb_rgb_rng[1] < 0.0) || ((*rt)->amb_rgb_rng[1] > 255.0)
			|| ((*rt)->amb_rgb_rng[2] < 0.0) || ((*rt)->amb_rgb_rng[2] > 255.0)
		))
		return (ft_putstr_fd("Error\nInvalid Ambient lighing value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	debug_write("TODO: Check if Camara orientation vector is normalized!\n");
	if (((*rt)->c_fov != -1)
		&& (((*rt)->c_fov < 0.0) || ((*rt)->c_fov > 180.0)
			|| ((*rt)->c_orient[0] < -1.0) || ((*rt)->c_orient[0] > 1.0)
			|| ((*rt)->c_orient[1] < -1.0) || ((*rt)->c_orient[1] > 1.0)
			|| ((*rt)->c_orient[2] < -1.0) || ((*rt)->c_orient[2] > 1.0)))
		return (ft_putstr_fd("Error\nInvalid Camera value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	debug_write("TODO: Check RGB range if Bonus!\n");
	if (((*rt)->light_brightness != -1)
		&& (((*rt)->light_brightness < 0.0) || ((*rt)->light_brightness > 1.0)))
		return (ft_putstr_fd("Error\nInvalid Light value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
