/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 08:02:44 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/04 08:41:32 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Makes a point
t_tuple	mk_pnt(float x, float y, float z)
{
	return ((t_tuple){x, y, z, POINT});
}

// Makes a vector
t_tuple	mk_vec(float x, float y, float z)
{
	return ((t_tuple){x, y, z, VECTOR});
}

int	pt_equal(t_tuple a, t_tuple b)
{
	if ((a.w != POINT) || (b.w != POINT))
		dbg_write_code("Error:\nThis is NOT a point!\n", RED);
	if (fl_equal(a.x, b.x) && fl_equal(a.y, b.y) && fl_equal(a.z, b.z))
		return (TRUE);
	return (FALSE);
}

int	vc_equal(t_tuple a, t_tuple b)
{
	if ((a.w != VECTOR) || (b.w != VECTOR))
		dbg_write_code("Error:\nThis is NOT a vector!\n", RED);
	if (fl_equal(a.x, b.x) && fl_equal(a.y, b.y) && fl_equal(a.z, b.z))
		return (TRUE);
	return (FALSE);
}

void	tuple_print(t_tuple data)
{
	if (fl_equal(data.w, POINT))
		ft_printf("point:  ");
	else if (fl_equal(data.w, VECTOR))
		ft_printf("vector: ");
	else
		ft_printf("Type: %i  ", (int)data.w);
	ft_printf("(% 3i.%02i, % 3i.%02i, % 3i.%02i)\n",
		(int)data.x, (((int)(fabs(data.x) * 100)) % 100),
		(int)data.y, (((int)(fabs(data.y) * 100)) % 100),
		(int)data.z, (((int)(fabs(data.z) * 100)) % 100));
}
