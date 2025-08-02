/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 15:48:24 by abessa-m          #+#    #+#             */
/*   Updated: 2025/07/18 16:01:18 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	close_win_button(t_scene *rt)
{
	dbg_write("Closing by CLOSE button on the window\n");
	finalize(rt);
	return (dbg_write("ERROR: return from close_win_button()\n"), 0);
}

int	key_hook(int keycode, t_scene *rt)
{
	if (keycode == 65307)
	{
		dbg_write("Closing by ESC key\n");
		finalize(rt);
	}
	return (EXIT_SUCCESS);
}
