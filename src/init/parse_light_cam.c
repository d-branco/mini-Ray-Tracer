/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:35:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 10:14:27 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_camera(char *line, t_scene **rt);
static int	parse_ambient_light(char *line, t_scene **rt);
static int	validate_value_range(t_scene **rt);

int	parse_lights_and_camera(char *line, t_scene **rt)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((line[0] == 'A') && ((*rt)->amb_ratio == -1))
		ret += parse_ambient_light(line, rt);
	else if (line[0] == 'A')
		return (ft_putstr_fd("ERROR: Ambient light can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if ((line[0] == 'C') && ((*rt)->cam_fov == -1))
		ret += parse_camera(line, rt);
	else if (line[0] == 'C')
		return (ft_putstr_fd("ERROR: Camera can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if (line[0] == 'L')
		debug_write("identified: Capital letter \'L\'!\n");
	debug_write("TODO: Check if only one and validate\n");
	ret += validate_value_range(rt);
	return (ret);
}

static int	parse_camera(char *line, t_scene **rt)
{
	(void) rt;
	debug_write("identified: Capital letter \'C\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: invalid Camera "
				"coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->cam_coord);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("ERROR: invalid Camera "
				"orientation (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->cam_orient);
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("ERROR: invalid Camera "
				"field of view (float)\n", 2), EXIT_FAILURE);
	(*rt)->cam_fov = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("ERROR: "
				"invalid Camera\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
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
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: invalid "
				"Ambient light RGB (float,float,float)\n", 2), EXIT_FAILURE);
	(*rt)->amb_rgb_rng[0] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_rng[1] = ft_atof(line);
	line = skip_to_after_comma(line);
	(*rt)->amb_rgb_rng[2] = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("ERROR: "
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
		return (ft_putstr_fd("ERROR: Invalid Ambient lighing value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	debug_write("TODO: Check if Camara orientation vector is normalized!\n");
	if (((*rt)->cam_fov != -1)
		&& (((*rt)->cam_fov < 0.0) || ((*rt)->cam_fov > 180.0)
			|| ((*rt)->cam_orient[0] < 0.0) || ((*rt)->cam_orient[0] > 1.0)
			|| ((*rt)->cam_orient[1] < 0.0) || ((*rt)->cam_orient[1] > 1.0)
			|| ((*rt)->cam_orient[2] < 0.0) || ((*rt)->cam_orient[2] > 1.0)))
		return (ft_putstr_fd("ERROR: Invalid Camera value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
