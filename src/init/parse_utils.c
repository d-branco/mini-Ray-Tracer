/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 09:58:29 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/17 10:04:31 by abessa-m         ###   ########.fr       */
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

void	parse_float_triplet(char *line, float array[3])
{
	array[0] = ft_atof(line);
	line = skip_to_after_comma(line);
	array[1] = ft_atof(line);
	line = skip_to_after_comma(line);
	array[2] = ft_atof(line);
}

int	validate_object_parsing(t_lst_obj *o)
{
	if (((o->id == e_SPHERE) || (o->id == e_CYlINDER)) && (o->diameter <= 0))
		return (ft_printf("Error\nInvalid diameter value\n"), EXIT_FAILURE);
	if (((o->id == e_SPHERE) || (o->id == e_PLANE) || (o->id == e_CYlINDER))
		&& ((o->rgb_rng[0] < 0.0) || (o->rgb_rng[0] > 255.0)
			|| (o->rgb_rng[1] < 0.0) || (o->rgb_rng[1] > 255.0)
			|| (o->rgb_rng[2] < 0.0) || (o->rgb_rng[2] > 255.0)))
		return (ft_printf("Error\nInvalid rgb range value\n"), EXIT_FAILURE);
	if (((o->id == e_PLANE) || (o->id == e_CYlINDER))
		&& ((o->vec_uni[0] < 0.0) || (o->vec_uni[0] > 1.0)
			|| (o->vec_uni[1] < 0.0) || (o->vec_uni[1] > 1.0)
			|| (o->vec_uni[2] < 0.0) || (o->vec_uni[2] > 1.0)))
		return (ft_printf("Error\nInvalid vector unit value\n"), EXIT_FAILURE);
	if ((o->id == e_CYlINDER) && (o->height <= 0))
		return (ft_printf("Error\nInvalid height value\n"), EXIT_FAILURE);
	return (debug_write("Obj values validated\n"), EXIT_SUCCESS);
}
