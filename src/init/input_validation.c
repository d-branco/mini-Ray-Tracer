/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 13:28:53 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/14 15:59:49 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	validate_file_type(char **argv, t_scene *rt);
static int	validate_file_fd(char *file_name, t_scene *rt);

int	input_validation(int argc, char **argv, t_scene *rt)
{
	(void) argv;
	if (argc != 2)
	{
		if (argc == 1)
			write(STDOUT_FILENO, "INVALID INPUT: no scene provided\n", 33);
		if (argc > 2)
			write(STDOUT_FILENO, "INVALID INPUT: too many arguments\n", 34);
		return (write(STDOUT_FILENO, "usage:\n./miniRT scene.rt\n", 25), 1);
	}
	else
		return (validate_file_type(argv, rt));
}

static int	validate_file_type(char **argv, t_scene *rt)
{
	int	len;

	len = ft_strlen(argv[1]);
	if ((len <= 3) || ((argv[1][len - 3] != '.')
		|| (argv[1][len - 2] != 'r') || (argv[1][len - 1] != 't')))
		return (write(STDOUT_FILENO, "INVALID INPUT: file type\n", 25),
			write(STDOUT_FILENO, "usage:\n./miniRT scene.rt\n", 25), 1);
	else
		return (validate_file_fd(argv[1], rt));
}

static int	validate_file_fd(char *file_name, t_scene *rt)
{
	char	*line;
	int		file_fd;

	file_fd = open(file_name, O_RDONLY, 0644);
	if (file_fd == -1)
		return (write(STDOUT_FILENO, "ERROR: could not open file\n", 27), 1);
	line = get_next_line(file_fd);
	if (!line)
		return (write(STDOUT_FILENO, "ERROR: could not read file\n", 28),
			close(file_fd), 1);
	while (line)
	{
		debug_write("INPUT FILE: ");
		ft_putstr_fd(line, 1);
		free(line);
		line = get_next_line(file_fd);
	}
	free(line);
	rt->file_fd = file_fd;
	return (0);
}
