/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 10:15:22 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/16 10:15:41 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	parse_objects(char *line, t_scene **rt)
{
	(void) line;
	(void) rt;
	debug_write("identified: object!\n");
	debug_write("TODO: Validate, check if repeated and add to linked list\n");
	return (EXIT_SUCCESS);
}
