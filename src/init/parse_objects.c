/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:15:22 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/17 09:49:06 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_sphere(char *line, t_scene *rt);
static int	parse_plane(char *line, t_scene *rt);
static int	parse_cylinder(char *line, t_scene *rt);
static int	rest_of_the_friendly_cylinder(
				char *line, t_scene *rt, t_lst_obj *obj);

int	parse_objects(char *line, t_scene *rt)
{
	int	ret;

	ret = 0;
	dbg_write("identified: object!\n");
	dbg_write("TODO: Validate, check if repeated and add to linked list\n");
	if ((line[0] == 's') && (line[1] == 'p'))
		ret += parse_sphere(line, rt);
	else if ((line[0] == 'p') && (line[1] == 'l'))
		ret += parse_plane(line, rt);
	else if ((line[0] == 'c') && (line[1] == 'y'))
		ret += parse_cylinder(line, rt);
	return (ret);
}

static int	parse_cylinder(char *line, t_scene *rt)
{
	t_lst_obj	*obj;

	obj = (t_lst_obj *)ft_malloc(sizeof(t_lst_obj) * 1);
	dbg_write("identified: object: CYlinder!\n");
	(*obj).id = e_CYLINDER;
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid cy coord!\n"), free(obj), 1);
	parse_float_point(line, &(obj->center));
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid cy vector!\n"), free(obj), 1);
	parse_float_vector(line, &(obj->vec_uni));
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (ft_printf("Error\nInvalid cy diameter!\n"), free(obj), 1);
	(*obj).diameter = ft_atof(line);
	line = skip_to_next_word(line);
	return (rest_of_the_friendly_cylinder(line, rt, obj));
}

static int	rest_of_the_friendly_cylinder(
				char *line, t_scene *rt, t_lst_obj *obj)
{
	if (!line || !ft_isfloat(line))
		return (ft_printf("Error\nInvalid cy height!\n"), free(obj), 1);
	(*obj).height = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid cy rgb range!\n"), free(obj), 1);
	parse_float_rgb(line, &(obj->rgb_rng));
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (ft_printf("Error\nInvalid cylinder!\n"), free(obj), 1);
	(*obj).next = NULL;
	rt_lstadd_back(&(*rt).lst_obj, obj);
	return (validate_object_parsing(obj));
}

static int	parse_plane(char *line, t_scene *rt)
{
	t_lst_obj	*obj;

	obj = (t_lst_obj *)ft_malloc(sizeof(t_lst_obj) * 1);
	dbg_write("identified: object: PLane!\n");
	(*obj).id = e_PLANE;
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid pl coord!\n"), free(obj), 1);
	parse_float_point(line, &(obj->center));
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid pl vector!\n"), free(obj), 1);
	parse_float_vector(line, &(obj->vec_uni));
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid pl rgb range!\n"), free(obj), 1);
	parse_float_rgb(line, &(obj->rgb_rng));
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (ft_printf("Error\nInvalid plane!\n"), free(obj), 1);
	(*obj).next = NULL;
	rt_lstadd_back(&(*rt).lst_obj, obj);
	return (validate_object_parsing(obj));
}

static int	parse_sphere(char *line, t_scene *rt)
{
	t_lst_obj	*obj;

	obj = (t_lst_obj *)ft_malloc(sizeof(t_lst_obj) * 1);
	dbg_write("identified: object: SPhere!\n");
	obj->id = e_SPHERE;
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid sp center!\n"), free(obj), 1);
	parse_float_point(line, &(obj->center));
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (ft_printf("Error\nInvalid sp diameter!\n"), free(obj), 1);
	obj->diameter = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid sp rgb range!\n"), free(obj), 1);
	parse_float_rgb(line, &(obj->rgb_rng));
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (ft_printf("Error\nInvalid sphere!\n"), free(obj), 1);
	obj->next = NULL;
	rt_lstadd_back(&(*rt).lst_obj, obj);
	return (validate_object_parsing(obj));
}
