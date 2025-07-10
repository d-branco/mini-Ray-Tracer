/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/10 12:56:09 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

void	debug_write(char *str);

int		input_validation(int argc, char **argv);
int		validate_file_type(char **argv);
int		validate_file_fd(char *file_name);

int	main(int argc, char **argv)
{
	debug_write("==DEBUGG== Hello, friend\n");
	if (input_validation(argc, argv) != 0)
		return (debug_write("==DEBUGG== Goodbye, friend\n"), 2);
	return (debug_write("==DEBUGG== Goodbye, friend\n"), 0);
}

void	debug_write(char *str)
{
	size_t	len;

	if (!DEBUG || !str || !str[0])
		return ;
	len = ft_strlen(str);
	write(STDOUT_FILENO, str, len);
}

int	input_validation(int argc, char **argv)
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
		return (validate_file_type(argv));
}

int	validate_file_type(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if ((len <= 3) || ((argv[1][len - 3] != '.')
		|| (argv[1][len - 2] != 'r') || (argv[1][len - 1] != 't')))
		return (write(STDOUT_FILENO, "INVALID INPUT: file type\n", 25),
			write(STDOUT_FILENO, "usage:\n./miniRT scene.rt\n", 25), 1);
	else
		return (validate_file_fd(argv[1]));
}

int	validate_file_fd(char *file_name)
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
		debug_write(line);
		free(line);
		line = get_next_line(file_fd);
	}
	free(line);
	close(file_fd);
	return (0);
}
