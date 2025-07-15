/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:23 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/15 19:02:24 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_line(char *line, t_scene **rt);
static int	parse_lights_and_camera(char *line, t_scene **rt);
static int	parse_objects(char *line, t_scene **rt);

static int	parse_ambient_light(char *line, t_scene **rt);

int	parse_input(t_scene *rt, char **argv)
{
	char	*line;
	int		exit_code;

	exit_code = EXIT_SUCCESS;
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
		if (parse_line(line, &rt) != EXIT_SUCCESS)
			exit_code = EXIT_FAILURE;
		free(line);
		line = get_next_line(rt->file_fd);
	}
	free(line);
	debug_write("TODO: Check if Ambient_light, Camara and Light exist\n");
	return (exit_code);
}

static int	parse_line(char *line, t_scene **rt)
{
	int	d;

	(void) rt;
	if (!line || (line[0] == '\0') || (line[0] == '\n'))
		return (EXIT_SUCCESS);
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
		return (parse_lights_and_camera(line, rt));
	else if (((line[0]) && (line[1]))
		&& ((line[0] == 's' && line[1] == 'p')
			|| (line[0] == 'p' && line[1] == 'l')
			|| (line[0] == 'c' && line[1] == 'y'))
		&& (ft_isspace(line[2])))
		return (parse_objects(line, rt));
	return (EXIT_SUCCESS);
}

static int	parse_lights_and_camera(char *line, t_scene **rt)
{
	int	ret;

	ret = EXIT_SUCCESS;
	if ((line[0] == 'A') && ((*rt)->amb_ratio == -1))
		ret += parse_ambient_light(line, rt);
	else if (line[0] == 'A')
		return (ft_putstr_fd("ERROR: Ambient light can only be declared once\n",
				STDERR_FILENO), EXIT_FAILURE);
	else if (line[0] == 'C')
		debug_write("identified: Capital letter \'C\'!\n");
	else if (line[0] == 'L')
		debug_write("identified: Capital letter \'L\'!\n");
	debug_write("TODO: Check if only one and validate\n");
	return (ret);
}

static int	parse_ambient_light(char *line, t_scene **rt)
{
	debug_write("identified: Capital letter \'A\'!\n");
	while (!ft_isspace(*line))
		line++;
	while (ft_isspace(*line))
		line++;
	if (!(*line))
		return ((*rt)->amb_ratio = -2,
			ft_putstr_fd("ERROR: Ambient light ratio missing\n", 2),
			EXIT_FAILURE);
	if (!ft_isfloat(line))
		return ((*rt)->amb_ratio = -2,
			ft_putstr_fd("ERROR: Ambient light ratio must be a float\n", 2),
			EXIT_FAILURE);
	(*rt)->amb_ratio = ft_atof(line);
	return (EXIT_SUCCESS);
}

static int	parse_objects(char *line, t_scene **rt)
{
	(void) line;
	(void) rt;
	debug_write("identified: object!\n");
	debug_write("TODO: Validate, check if repeated and add to linked list\n");
	return (EXIT_SUCCESS);
}
