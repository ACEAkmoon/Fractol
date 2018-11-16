/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:19:48 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:19:49 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void		ft_set(int key, t_map *map)
{
	double		w;
	double		h;

	if (key == NUM_ENTER)
	{
		map->view.offx = 0;
		map->view.offy = 0;
		ft_fractol_view(&map->view);
		w = map->view.xmax - map->view.xmin;
		h = map->view.ymax - map->view.ymin;
		if (w / h >= (float)WIN_W / WIN_H)
		{
			map->view.ymin = -(w * WIN_H / WIN_W / 2);
			map->view.ymax = w * WIN_H / WIN_W / 2;
		}
		else
		{
			map->view.xmin = -(h * WIN_W / WIN_H / 2);
			map->view.xmax = (h * WIN_W / WIN_H / 2);
		}
		map->view.max = 32;
		map->view.zoom = 1.0f;
	}
}

static void		ft_depht(int key, t_map *map)
{
	if (key == P_UP)
		map->view.max *= 2;
	if (key == P_DOWN)
		map->view.max /= 2;
}

static void		ft_zoom(int key, t_map *map)
{
	if (key == NUM_PLUS)
		ft_zooming(WIN_W / 2, WIN_H / 2, &map->view, 1 / ZOOM, map);
	if (key == NUM_MINUS)
		ft_zooming(WIN_W / 2, WIN_H / 2, &map->view, ZOOM, map);
}

static void		ft_move(int key, t_map *map)
{
	double		w;
	double		h;

	w = (map->view.xmax - map->view.xmin) * map->view.zoom;
	h = (map->view.ymax - map->view.ymin) * map->view.zoom;
	if (key == UP)
		map->view.offy -= h * 0.05f;
	if (key == DOWN)
		map->view.offy += h * 0.05f;
	if (key == LEFT)
		map->view.offx -= w * 0.05f;
	if (key == RIGHT)
		map->view.offx += w * 0.05f;
}

int				ft_key_hook(int key, t_map *map)
{
	ft_set(key, map);
	ft_zoom(key, map);
	ft_move(key, map);
	ft_depht(key, map);
	key == NUM_0 ? map->smoothing = 1 - map->smoothing : map->smoothing;
	key == LOCK ? map->mouselock = 1 - map->mouselock : map->mouselock;
	key >= NUM_1 && key <= NUM_1 + 4 ? \
		map->palette = &ft_color_palettes()[key - NUM_1] : ft_solver(map);
	if (key == ESC)
	{
		mlx_destroy_window(map->mlx, map->win);
		system("leaks fractol");
		exit(EXIT_SUCCESS);
	}
	return (0);
}
