/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 10:49:23 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/17 10:01:12 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	parse_line(char *line, t_scene **rt);

int	parse_input(t_scene *rt, char **argv)
{
	char	*line;
	int		ret;

	ret = EXIT_SUCCESS;
	debug_write("Parsing the input file\n");
	rt->file_fd = open(argv[1], O_RDONLY, 0644);
	if (rt->file_fd == -1)
		return (write(STDOUT_FILENO, "Error\ncould not open file\n", 26), 1);
	line = get_next_line(rt->file_fd);
	if (!line)
		return (write(STDOUT_FILENO, "Error\ncould not read file\n", 26), 1);
	while (line)
	{
		if (line[ft_strlen(line) - 1] != '\n')
			line = append_chr(line, '\n');
		debug_write("parsing line: ");
		if (DEBUG)
			ft_putstr_fd(line, STDOUT_FILENO);
		if (parse_line(line, &rt) != EXIT_SUCCESS)
			ret = EXIT_FAILURE;
		free(line);
		line = get_next_line(rt->file_fd);
	}
	free(line);
	return (debug_write("TODO: Check if A, C and L exist\n"), ret);
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
		debug_write("id: ");
		d = 0;
		while (ft_isalpha(line[d]))
			ft_putchar_fd(line[d++], 1);
		ft_putchar_fd('\n', 1);
	}
	if ((*line == 'A' || *line == 'C' || *line == 'L') && (ft_isspace(line[1])))
		return (parse_lights_and_camera(line, rt));
	else if (((line[0]) && (line[1])) && ((line[0] == 's' && line[1] == 'p')
			|| (line[0] == 'p' && line[1] == 'l')
			|| (line[0] == 'c' && line[1] == 'y')) && (ft_isspace(line[2])))
		return (parse_objects(line, rt));
	else
		return (ft_printf("Error\nInvalid line: %s", line), EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
