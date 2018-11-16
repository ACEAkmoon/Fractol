/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:55:51 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/13 15:55:53 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			ft_mouse_bind(int key, int x, int y, t_map *map)
{
	(void)x;
	(void)y;
	map->mouse.isdown &= ~(1 << key);
	return (0);
}

int			ft_mouse_scroll(int key, int x, int y, t_map *map)
{
	if (key == SCROLL_UP)
		ft_zooming(x, y, &map->view, 1 / ZOOM, map);
	else if (key == SCROLL_DOWN)
		ft_zooming(x, y, &map->view, ZOOM, map);
	map->mouse.isdown |= 1 << key;
	return (0);
}

int			ft_mouse_move(int x, int y, t_map *map)
{
	double	w;
	double	h;

	map->mouse.lastx = map->mouse.x;
	map->mouse.lasty = map->mouse.y;
	map->mouse.x = x;
	map->mouse.y = y;
	if (!map->mouselock)
		map->view.mouse = ft_view_to_pixel(x, y, &map->view);
	if (map->mouse.isdown & (1 << 1))
	{
		w = (map->view.xmax - map->view.xmin) * map->view.zoom;
		h = (map->view.ymax - map->view.ymin) * map->view.zoom;
		map->view.offx += (double)(map->mouse.lastx - map->mouse.x) \
			/ WIN_W * w;
		map->view.offy += (double)(map->mouse.lasty - map->mouse.y) \
			/ WIN_H * h;
	}
	if (map->mouse.isdown || !map->mouselock)
		ft_solver(map);
	return (0);
}
