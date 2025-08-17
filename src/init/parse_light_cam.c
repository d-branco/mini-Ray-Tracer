/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_light_cam.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:35:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 08:50:17 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_camera(char *line, t_scene *rt);
static int	parse_ambient_light(char *line, t_scene *rt);
static int	validate_value_range(t_scene *rt);
static int	parse_light(char *line, t_scene *rt);

int	parse_lights_and_camera(char *line, t_scene *rt)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((line[0] == 'A') && (fl_equal(rt->a_ratio, -1.0f)))
		ret += parse_ambient_light(line, rt);
	else if (line[0] == 'A')
		return (ft_putstr_fd("Error\nAmbient light can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if ((line[0] == 'C') && (fl_equal(rt->c_fov, -1.0f)))
		ret += parse_camera(line, rt);
	else if (line[0] == 'C')
		return (ft_putstr_fd("Error\nCamera can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if ((line[0] == 'L') && (fl_equal(rt->l_bri, -1.0f)))
		ret += parse_light(line, rt);
	else if (line[0] == 'L')
		return (ft_putstr_fd("Error\nLight can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	ret += validate_value_range(rt);
	return (ret);
}

static int	parse_light(char *line, t_scene *rt)
{
	dbg_write("identified: Capital letter \'L\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (rt->l_bri = -2, ft_putstr_fd("Error\ninvali"
				"d Light coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_point(line, &(rt->l_coo));
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (rt->l_bri = -2, ft_putstr_fd("Error\ninvali"
				"d Light ratio range (float)\n", 2), EXIT_FAILURE);
	rt->l_bri = ft_atof(line);
	line = skip_to_next_word(line);
	parse_float_rgb(line, &(rt->l_rgb));
	if (line && ft_isprint(*line))
	{
		if (!is_float_triplet(line))
			return (rt->l_bri = -2, ft_putstr_fd("Error\n"
					"invalid Light\n", 2), EXIT_FAILURE);
		parse_float_rgb(line, &(rt->l_rgb));
		line = skip_to_next_word(line);
	}
	if (line && ft_isprint(*line))
		return (rt->l_bri = -2, ft_putstr_fd("Error\n"
				"invalid Light\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_camera(char *line, t_scene *rt)
{
	dbg_write("identified: Capital letter \'C\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (rt->a_ratio = -2, ft_putstr_fd("Error\ninvalid Camera "
				"coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_point(line, &(rt->c_coo));
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (rt->c_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"orientation (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_vector(line, &(rt->c_dir));
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (rt->c_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"field of view (float)\n", 2), EXIT_FAILURE);
	rt->c_fov = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (rt->c_fov = -2, ft_putstr_fd("Error\n"
				"invalid Camera\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	parse_ambient_light(char *line, t_scene *rt)
{
	dbg_write("identified: Capital letter \'A\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (rt->a_ratio = -2, ft_putstr_fd("Error\n"
				"invalid Ambient light ratio (float)\n", 2), EXIT_FAILURE);
	rt->a_ratio = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (rt->a_ratio = -2, ft_putstr_fd("Error\ninvalid "
				"Ambient light RGB (float,float,float)\n", 2), EXIT_FAILURE);
	rt->a_rgb.r = ft_atof(line);
	line = skip_to_after_comma(line);
	rt->a_rgb.g = ft_atof(line);
	line = skip_to_after_comma(line);
	rt->a_rgb.b = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (rt->a_ratio = -2, ft_putstr_fd("Error\n"
				"invalid Ambient light\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	validate_value_range(t_scene *rt)
{
	if (!(fl_equal(rt->a_ratio, -1.0f))
		&& ((rt->a_ratio < 0.0f) || (rt->a_ratio > 1.0f)
			|| (rt->a_rgb.r < 0.0f) || (rt->a_rgb.r > 255.0f)
			|| (rt->a_rgb.g < 0.0f) || (rt->a_rgb.g > 255.0f)
			|| (rt->a_rgb.b < 0.0f) || (rt->a_rgb.b > 255.0f)
		))
		return (ft_putstr_fd("Error\nInvalid Ambient lighing value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	dbg_write("TODO: Check if Camara orientation vector is normalized!\n");
	if (!(fl_equal(rt->c_fov, -1.0f))
		&& ((rt->c_fov < 0.0f) || (rt->c_fov > 180.0f)
			|| (rt->c_dir.x < -1.0f) || (rt->c_dir.x > 1.0f)
			|| (rt->c_dir.y < -1.0f) || (rt->c_dir.y > 1.0f)
			|| (rt->c_dir.z < -1.0f) || (rt->c_dir.z > 1.0f)))
		return (ft_putstr_fd("Error\nInvalid Camera value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	dbg_write("TODO: Check RGB range if Bonus!\n");
	if (!(fl_equal(rt->l_bri, -1.0f))
		&& ((rt->l_bri < 0.0) || (rt->l_bri > 1.0)))
		return (ft_putstr_fd("Error\nInvalid Light value range\n",
				STDERR_FILENO), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
