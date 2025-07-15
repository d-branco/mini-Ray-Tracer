/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:23 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 12:03:43 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	parse_line(char *line, t_scene **rt);
static void	parse_lights_and_camera(char *line, t_scene **rt);
static void	parse_objects(char *line, t_scene **rt);

int	parse_input(t_scene *rt, char **argv)
{
	char	*line;

	debug_write("Parsing the input file\n");
	rt->file_fd = open(argv[1], O_RDONLY, 0644);
	if (rt->file_fd == -1)
		return (write(STDOUT_FILENO, "ERROR: could not open file\n", 27), 1);
	line = get_next_line(rt->file_fd);
	if (!line)
		return (write(STDOUT_FILENO, "ERROR: could not read file\n", 28), 1);
	while (line)
	{
		debug_write("parsing line: ");
		if (DEBUG)
			ft_putstr_fd(line, 1);
		parse_line(line, &rt);
		free(line);
		line = get_next_line(rt->file_fd);
	}
	free(line);
	return (EXIT_SUCCESS);
}

static void	parse_line(char *line, t_scene **rt)
{
	int	d;

	(void) rt;
	if (!line || (line[0] == '\0') || (line[0] == '\n'))
		return ;
	while (ft_isspace(*line))
		line++;
	if (DEBUG)
	{
		debug_write("identifier: ");
		d = 0;
		while (ft_isalpha(line[d]))
			ft_putchar_fd(line[d++], 1);
		ft_putchar_fd('\n', 1);
	}
	if ((*line == 'A' || *line == 'C' || *line == 'L')
		&& (ft_isspace(line[1])))
		parse_lights_and_camera(line, rt);
	if (((line[0]) && (line[1]))
		&& ((line[0] == 's' && line[1] == 'p')
			|| (line[0] == 'p' && line[1] == 'l')
			|| (line[0] == 'c' && line[1] == 'y'))
		&& (ft_isspace(line[2])))
		parse_objects(line, rt);
}

static void	parse_lights_and_camera(char *line, t_scene **rt)
{
	(void) line;
	(void) rt;
	debug_write("identified: Capital letter!\n");
	debug_write("TODO: Check if only one and validate\n");
}

static void	parse_objects(char *line, t_scene **rt)
{
	(void) line;
	(void) rt;
	debug_write("identified: object!\n");
	debug_write("TODO: Validate and add to linked list\n");
}
