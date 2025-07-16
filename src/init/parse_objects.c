/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:15:22 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 20:16:14 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_sphere(char *line, t_scene **rt);

void		rt_lstadd_back(t_lst_obj **lst, t_lst_obj *new);

int	parse_objects(char *line, t_scene **rt)
{
	int	ret;

	ret = 0;
	(void) line;
	(void) rt;
	debug_write("identified: object!\n");
	debug_write("TODO: Validate, check if repeated and add to linked list\n");
	if ((line[0] == 's') && (line[1] == 'p'))
		ret += parse_sphere(line, rt);
	return (ret);
}

static int	parse_sphere(char *line, t_scene **rt)
{
	t_lst_obj	*obj;

	obj = (t_lst_obj *) malloc(sizeof(t_lst_obj) * 1);
	if (obj == NULL)
		return (ft_printf("ERROR: Malloc actually failed!\n"), free(obj), 1);
	debug_write("identified: object: SPhere!\n");
	(*obj).identifier = e_SPHERE;
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid sp center!\n"), free(obj), 1);
	parse_float_triplet(line, (*obj).center);
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return (ft_printf("Error\nInvalid sp diameter!\n"), free(obj), 1);
	(*obj).diameter = ft_atof(line);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return (ft_printf("Error\nInvalid sp rgb range!\n"), free(obj), 1);
	parse_float_triplet(line, (*obj).rgb_range);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return (ft_printf("Error\nInvalid sphere!\n"), free(obj), 1);
	(*obj).next = NULL;
	rt_lstadd_back(&(*rt)->lst_obj, obj);
	return (EXIT_SUCCESS);
}

/*
static int	parse_camera(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'C\'!\n");
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->amb_ratio = -2, ft_putstr_fd("Error\ninvalid Camera "
				"coordinates (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->cam_coord);
	line = skip_to_next_word(line);
	if (!line || !ft_isprint(*line) || !is_float_triplet(line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"orientation (float,float,float)\n", 2), EXIT_FAILURE);
	parse_float_triplet(line, (*rt)->cam_orient);
	line = skip_to_next_word(line);
	if (!line || !ft_isfloat(line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("Error\ninvalid Camera "
				"field of view (float)\n", 2), EXIT_FAILURE);
	(*rt)->cam_fov = ft_atof(line);
	line = skip_to_next_word(line);
	if (line && ft_isprint(*line))
		return ((*rt)->cam_fov = -2, ft_putstr_fd("Error\n"
				"invalid Camera\n", 2), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*first;

	first = (t_list *) malloc(sizeof(t_list));
	if (first == NULL)
		return (NULL);
	(*first).content = content;
	(*first).next = NULL;
	return (first);
}*/

void	rt_lstadd_back(t_lst_obj **lst, t_lst_obj *new)
{
	t_lst_obj	*last;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
}
