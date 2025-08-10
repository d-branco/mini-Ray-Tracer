/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abessa-m <abessa-m@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 16:26:44 by abessa-m          #+#    #+#             */
/*   Updated: 2025/08/07 16:39:16 by abessa-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_rgb	rgb_ratios(t_rgb pnt, t_rgb amb);
static int		pix_smooth4(t_scene *rt, t_cnv c);

static int	pix_smooth4(t_scene *rt, t_cnv c)
{
	return (
		rgb_merge(
			rgb_merge(
				get_color(rt, get_xs(rt, (t_cnv){c.x + 0.00f, c.y})),
			get_color(rt, get_xs(rt, (t_cnv){c.x + 0.25f, c.y}))),
		rgb_merge(
			get_color(rt, get_xs(rt, (t_cnv){c.x + 0.50f, c.y})),
			get_color(rt, get_xs(rt, (t_cnv){c.x + 0.75f, c.y})))));
}

int	pix_smooth16(t_scene *rt, t_cnv *c)
{
	return (
		rgb_merge(
			rgb_merge(
				pix_smooth4(rt, (t_cnv){c->x + 0.125, c->y + 0.125}),
			pix_smooth4(rt, (t_cnv){c->x + 0.125, c->y + 0.375})),
		rgb_merge(
			pix_smooth4(rt, (t_cnv){c->x + 0.125, c->y + 0.625}),
			pix_smooth4(rt, (t_cnv){c->x + 0.125, c->y + 0.875}))));
}

int	get_color(t_scene *rt, t_lst_obj *obj)
{
	t_rgb	pnt;
	t_rgb	amb;
	float	normal;

	if (obj == NULL)
		return (encode_rgb(0, 0, 0));
	amb = (t_rgb){(sqrtf(obj->rgb_rng.r * rt->a_rgb.r) * rt->a_ratio),
		(sqrtf(obj->rgb_rng.g * rt->a_rgb.g) * rt->a_ratio),
		(sqrtf(obj->rgb_rng.b * rt->a_rgb.b) * rt->a_ratio)};
	if (check_obj_xs(rt, obj->xs_pnt, pnt_subtr_to_vec(rt->l_coo, obj->xs_pnt)))
		return (encode_rgb((int)amb.r, (int)amb.g, (int)amb.b));
	if (obj->id == e_SPHERE)
		normal = vec_inner_product(
				vec_norm(pnt_subtr_to_vec(obj->center, obj->xs_pnt)),
				vec_norm(pnt_subtr_to_vec(obj->xs_pnt, rt->l_coo)));
	if (obj->id == e_PLANE)
		normal = fabsf(vec_inner_product(vec_norm(obj->vec_uni),
					vec_norm(pnt_subtr_to_vec(rt->l_coo, obj->xs_pnt))));
	if (normal <= EPSILON)
		normal = 0;
	pnt = (t_rgb){sqrtf(obj->rgb_rng.r * rt->l_rgb.r * rt->l_bri) * normal,
		sqrtf(obj->rgb_rng.g * rt->l_rgb.g * rt->l_bri) * normal,
		sqrtf(obj->rgb_rng.b * rt->l_rgb.b * rt->l_bri) * normal};
	pnt = rgb_ratios(pnt, amb);
	return (encode_rgb((int)pnt.r, (int)pnt.g, (int)pnt.b));
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
