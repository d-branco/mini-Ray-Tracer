/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:58:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 07:54:19 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

char	*skip_to_next_word(char *line)
{
	int	i;

	i = 0;
	while (!ft_isspace(line[i]))
		i++;
	while (ft_isspace(line[i]))
		i++;
	return (&line[i]);
}

char	*skip_to_after_comma(char *line)
{
	int	i;

	i = 0;
	while (line[i] != ',')
		i++;
	i++;
	return (&line[i]);
}

void	parse_float_vector(char *line, t_tuple *array)
{
	array->x = ft_atof(line);
	line = skip_to_after_comma(line);
	array->y = ft_atof(line);
	line = skip_to_after_comma(line);
	array->z = ft_atof(line);
	array->w = VECTOR;
}

void	parse_float_point(char *line, t_tuple *array)
{
	array->x = ft_atof(line);
	line = skip_to_after_comma(line);
	array->y = ft_atof(line);
	line = skip_to_after_comma(line);
	array->z = ft_atof(line);
	array->w = POINT;
}

int	validate_object_parsing(t_lst_obj *o)
{
	if (((o->id == e_SPHERE) || (o->id == e_CYLINDER)) && (o->diameter <= 0))
		return (ft_printf("Error\nInvalid diameter value\n"), EXIT_FAILURE);
	if (((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYLINDER))
		&& ((o->rgb_rng.r < 0.0f) || (o->rgb_rng.r > 255.0f)
			|| (o->rgb_rng.g < 0.0f) || (o->rgb_rng.g > 255.0f)
			|| (o->rgb_rng.b < 0.0f) || (o->rgb_rng.b > 255.0f)))
		return (ft_printf("Error\nInvalid rgb range value\n"), EXIT_FAILURE);
	if (((o->id == e_PLANE) || (o->id == e_CYLINDER))
		&& ((o->vec_uni.x < -1.0f) || (o->vec_uni.x > 1.0f)
			|| (o->vec_uni.y < -1.0f) || (o->vec_uni.y > 1.0f)
			|| (o->vec_uni.z < -1.0f) || (o->vec_uni.z > 1.0f)))
		return (ft_printf("Error\nInvalid pl/cy vector unit value\n"), 1);
	if ((o->id == e_CYLINDER) && (o->height <= 0))
		return (ft_printf("Error\nInvalid height value\n"), EXIT_FAILURE);
	return (dbg_write("Obj values validated\n"), EXIT_SUCCESS);
}
