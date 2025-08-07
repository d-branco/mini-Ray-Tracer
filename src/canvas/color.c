/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:26:44 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 08:29:54 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	rgb_ratios(t_rgb pnt, t_rgb amb);

int	pix_smooth4(t_scene *rt, t_cnv *c)
{
	return (
		rgb_merge(
			rgb_merge(
				get_color(rt, get_xs(rt, *c)),
				get_color(rt, get_xs(rt, (t_cnv){c->x + 0.5, c->y}))),
		rgb_merge(
			get_color(rt, get_xs(rt, (t_cnv){c->x + 0.5, c->y + 0.5})),
		get_color(rt, get_xs(rt, (t_cnv){c->x, c->y + 0.5}))))
		);
}

int	get_color(t_scene *rt, t_lst_obj *obj)
{
	t_tuple	xs_to_c;
	t_rgb	pnt;
	t_rgb	amb;
	float	normal;

	if (obj == NULL)
		return (encode_rgb(0, 0, 0));
	normal = vec_inner_product(
			vec_norm(pnt_subtraction_into_vec(obj->center, obj->xs_pnt)),
			vec_norm(pnt_subtraction_into_vec(obj->xs_pnt, rt->l_coo)));
	if (normal <= EPSILON)
		normal = 0;
	amb = (t_rgb){(sqrtf(obj->rgb_rng.r * rt->a_rgb.r) * rt->a_ratio),
		(sqrtf(obj->rgb_rng.g * rt->a_rgb.g) * rt->a_ratio),
		(sqrtf(obj->rgb_rng.b * rt->a_rgb.b) * rt->a_ratio)};
	xs_to_c = pnt_subtraction_into_vec(rt->l_coo, obj->xs_pnt);
	pnt = amb;
	pnt = (t_rgb){sqrtf(pnt.r * obj->rgb_rng.r * rt->l_bri * normal),
		sqrtf(pnt.g * obj->rgb_rng.g * rt->l_bri * normal),
		sqrtf(pnt.b * obj->rgb_rng.b * rt->l_bri * normal)};
	pnt = rgb_ratios(pnt, amb);
	if (!check_obj_xs(rt, obj->xs_pnt, xs_to_c))
		return (encode_rgb((int)pnt.r, (int)pnt.g, (int)pnt.b));
	return (encode_rgb((int)amb.r, (int)amb.g, (int)amb.b));
}

static t_rgb	rgb_ratios(t_rgb pnt, t_rgb amb)
{
	t_rgb	ret;

	ret = (t_rgb){pnt.r, pnt.g, pnt.b};
	if (pnt.r < amb.r - EPSILON)
		ret.r = amb.r;
	if (pnt.g < amb.g - EPSILON)
		ret.g = amb.g;
	if (pnt.b < amb.b - EPSILON)
		ret.b = amb.b;
	return (ret);
}

int	rgb_merge(int rgb1, int rgb2)
{
	int	r;
	int	g;
	int	b;

	r = (((rgb1 >> 16) & 0xFF) + ((rgb2 >> 16) & 0xFF)) / 2;
	g = (((rgb1 >> 8) & 0xFF) + ((rgb2 >> 8) & 0xFF)) / 2;
	b = ((rgb1 & 0xFF) + (rgb2 & 0xFF)) / 2;
	return ((r << 16) | (g << 8) | b);
}
