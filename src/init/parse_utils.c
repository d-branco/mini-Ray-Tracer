/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:58:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/30 11:54:00 by abessa-m         ###   ########.fr       */
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

void	parse_float_vector(char *line, t_vector *array)
{
	array->x = ft_atof(line);
	line = skip_to_after_comma(line);
	array->y = ft_atof(line);
	line = skip_to_after_comma(line);
	array->z = ft_atof(line);
}

void	parse_float_point(char *line, t_point *array)
{
	array->x = ft_atof(line);
	line = skip_to_after_comma(line);
	array->y = ft_atof(line);
	line = skip_to_after_comma(line);
	array->z = ft_atof(line);
}

int	validate_object_parsing(t_lst_obj *o)
{
	if (((o->id == e_SPHERE) || (o->id == e_CYlINDER)) && (o->diameter <= 0))
		return (ft_printf("Error\nInvalid diameter value\n"), EXIT_FAILURE);
	if (((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYlINDER))
		&& ((o->rgb_rng.r < 0.0f) || (o->rgb_rng.r > 255.0f)
			|| (o->rgb_rng.g < 0.0f) || (o->rgb_rng.g > 255.0f)
			|| (o->rgb_rng.b < 0.0f) || (o->rgb_rng.b > 255.0f)))
		return (ft_printf("Error\nInvalid rgb range value\n"), EXIT_FAILURE);
	if (((o->id == e_PLANE) || (o->id == e_CYlINDER))
		&& ((o->vec_uni.x < 0.0f) || (o->vec_uni.x > 1.0f)
			|| (o->vec_uni.y < 0.0f) || (o->vec_uni.y > 1.0f)
			|| (o->vec_uni.z < 0.0f) || (o->vec_uni.z > 1.0f)))
		return (ft_printf("Error\nInvalid vector unit value\n"), EXIT_FAILURE);
	if ((o->id == e_CYlINDER) && (o->height <= 0))
		return (ft_printf("Error\nInvalid height value\n"), EXIT_FAILURE);
	return (debug_write("Obj values validated\n"), EXIT_SUCCESS);
}
