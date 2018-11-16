/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/05 19:23:04 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/05 19:23:06 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_palette		*ft_color_palettes(void)
{
	static t_palette	arr[6];

	arr[0] =
		(t_palette){4, {0x411659, 0x7341F4, 0x9B6E0d, 0xE8E533, 0xC22222}};
	arr[1] =
		(t_palette){4, {0x008000, 0xADFF2F, 0xFFD700, 0xD2691E, 0xA1D700}};
	arr[2] =
		(t_palette){4, {0x002F2F, 0x046380, 0xEFECCA, 0xA7A37E, 0xE6E2AF}};
	arr[3] =
		(t_palette){4, {0x7F1637, 0x17373C, 0x2B6832, 0xA7A37E, 0xE6E2AF}};
	arr[4] =
		(t_palette){4, {0xFF0000, 0xFFFF00, 0x00FF00, 0x00FFFF, 0x0000FF}};
	arr[5] = (t_palette){0, {0}};
	return (arr);
}

static t_color	ft_set_color(double d, int max, t_palette *p)
{
	int			i;
	double		index;
	double		adjust;
	t_color		c1;
	t_color		c2;

	index = d / max;
	i = p->count - 1;
	adjust = fmod(index, 1.0f / i) * i;
	adjust = (int)(adjust + 1) - adjust;
	c1 = (t_color)(p->colors[(int)(index * i) + 1]);
	c2 = (t_color)(p->colors[(int)(index * i)]);
	c1.argb.a = (char)0x00;
	c1.argb.r = c1.argb.r + (c2.argb.r - c1.argb.r) * adjust;
	c1.argb.g = c1.argb.g + (c2.argb.g - c1.argb.g) * adjust;
	c1.argb.b = c1.argb.b + (c2.argb.b - c1.argb.b) * adjust;
	return (c1);
}

int				ft_get_color(t_pixel p, t_map *map)
{
	double		d;
	double		zn;
	double		nu;

	if (p.i >= map->view.max)
		return (0x000000);
	if (map->smoothing)
	{
		zn = log(p.x * p.x + p.y * p.y) / 2.0f;
		nu = log(zn / log(2)) / log(2);
		d = p.i + 1 - nu;
		d < 0 ? d = 0 : d;
		return (ft_set_color(d, map->view.max, map->palette).value);
	}
	return (ft_set_color((double)p.i, map->view.max, map->palette).value);
}
