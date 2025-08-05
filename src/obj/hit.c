/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 10:54:58 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/05 10:55:00 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// Returns the lowest positiv distant element of the intersection list or NULL
t_lst_xs	*obj_hit(t_lst_xs *xs)
{
	t_lst_xs	*ptr;
	float		distance;

	ptr = NULL;
	distance = MAX_FLOAT;
	while (xs)
	{
		if ((xs->dst > 0) && (xs->dst < distance))
		{
			distance = xs->dst;
			ptr = xs;
		}
		xs = xs->next;
	}
	return (ptr);
}

/*typedef struct s_lst_xs
{
	float					dst;
	t_lst_obj				*obj;
	struct s_lst_xs			*next;
}							t_lst_xs;

typedef struct s_lst_obj
{
	int						id;
	struct s_tuple			center;
	float					diameter;
	struct s_rgb			rgb_rng;
	struct s_tuple			vec_uni;
	float					height;
	struct s_intersect		intersect;
	struct s_lst_obj		*next;
}							t_lst_obj;
*/

/*static void	temp_testing(t_scene *rt)
{
	t_lst_xs	a;
	t_lst_xs	b;
	t_lst_xs	c;
	t_lst_xs	d;

	(void) rt;
	ft_printf("\n TEST starts\n ");
	b = (t_lst_xs){2, rt->lst_obj, NULL};
	a = (t_lst_xs){1, rt->lst_obj, &b};
	if (obj_hit(&a) == &a)
		ft_printf("[1] ");
	else
		ft_printf(" ERROR 1! ");

	b = (t_lst_xs){1, rt->lst_obj, NULL};
	a = (t_lst_xs){-1, rt->lst_obj, &b};
	if (obj_hit(&a) == &b)
		ft_printf("[2] ");
	else
		ft_printf(" ERROR 2! ");

	b = (t_lst_xs){-1, rt->lst_obj, NULL};
	a = (t_lst_xs){-2, rt->lst_obj, &b};
	if (obj_hit(&a) == NULL)
		ft_printf("[3] ");
	else
		ft_printf(" ERROR 3! ");

	d = (t_lst_xs)(t_lst_xs){2, rt->lst_obj, NULL};
	c = (t_lst_xs)(t_lst_xs){-3, rt->lst_obj, &d};
	b = (t_lst_xs){7, rt->lst_obj, &c};
	a = (t_lst_xs){5, rt->lst_obj, &b};
	if (obj_hit(&a) == &d)
		ft_printf("[4] ");
	else
		ft_printf(" ERROR 4! ");

	ft_printf("\n TEST ends\n\n");

}*/
