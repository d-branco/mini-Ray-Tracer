/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 21:30:17 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/08 22:37:50 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(void)
{
	char	*str;

	str = ft_strdup("42");
	if (DEBUG)
		ft_printf("Pointer at %p pointing at %p "
			"with the allocated string: %s.\n", &str, str, str);
	ft_free_n_null((void *)&str);
	ft_free_n_null((void *)&str);
	str = ft_strdup("225");
	free(str);
	str = NULL;
	free(str);
	return (0);
}
