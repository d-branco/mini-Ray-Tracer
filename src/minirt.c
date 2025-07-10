/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/10 11:36:31 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minirt.h"

int		input_validation(int argc, char **argv);
int		validate_file_type(char **argv);

int	main(int argc, char **argv)
{
	if (input_validation(argc, argv) == 1)
		return (write(STDOUT_FILENO, "usage:\n./miniRT scene.rt\n", 25), 2);
	write(STDOUT_FILENO, "main\n", 5);
	return (0);
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
		return (1);
	}
	else
		return(validate_file_type(argv));
}

int	validate_file_type(char **argv)
{
	int	len;

	len = ft_strlen(argv[1]);
	if ((len <= 3) || ((argv[1][len - 3] != '.')
		|| (argv[1][len - 2] != 'r') || (argv[1][len - 1] != 't')))
		return (write(STDOUT_FILENO, "INVALID INPUT: file type\n", 25), 1);
	return (0);
}
