/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:21:48 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:21:50 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			ft_error(char *err_str)
{
	*err_str ? ft_putendl(err_str) : ft_putendl("error");
	exit(EXIT_FAILURE);
}

void			ft_display_controls(void)
{
	ft_putstr("\
_______________________________\n\
CONTROLS:\n\
Translation:\n\
	Y: Key: UP, DOWN\n\
	X: Key: LEFT, RIGHT\n\
\n\
Zoom:\n\
	IN: Keypad: +\n\
	OUT: Keypad: -\n\
	RESET: Keypad: ENTER\n\
	Lock mouse: Keypad: L\n\
\n\
Recount:\n\
	IN: Keypad: P_UP\n\
	OUT: Keypad: P_DOWN\n\
\n\
Color:\n\
	Keypad: num 1-4\n\
	Smoothing: Keypad: 0\n\
\n\
Exit:\n\
	IN: Key: Esc\n\
_______________________________\n\
");
}

void		ft_zooming(int x, int y, t_view *v, double z, t_map *map)
{
	double		w;
	double		h;
	double		nw;
	double		nh;

	v->zoom *= z;
	w = (v->xmax - v->xmin) * (v->zoom);
	h = (v->ymax - v->ymin) * (v->zoom);
	nw = (v->xmax - v->xmin) * (v->zoom * z);
	nh = (v->ymax - v->ymin) * (v->zoom * z);
	v->offx -= ((double)x / WIN_W) * (nw - w);
	v->offy -= ((double)y / WIN_H) * (nh - h);
	ft_solver(map);
}

void			ft_draw(t_map *map)
{
	int			x;
	int			y;
	char		*name;

	y = 0;
	while (y < WIN_H)
	{
		x = 0;
		while (x < WIN_W)
		{
			if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
				return ;
			*(int *)(map->image->ptr + ((x + y * WIN_W) * map->image->bt_px)) =
				ft_get_color(*(map->data + y * WIN_W + x), map);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(map->mlx, map->win, map->image->image, 0, 0);
	name = ft_strjoin("The chosen fractal is : ", map->fractol->name);
	mlx_string_put(map->mlx, map->win, LFT_MRGN, TOP_MRGN, INF_CLR, NAME);
	mlx_string_put(map->mlx, map->win, LFT_MRGN, TOP_MRGN * 5, INF_CLR, name);
	mlx_string_put(map->mlx, map->win, LFT_MRGN, WIN_H - TOP_MRGN * 6, \
		INF_CLR, "Please select a palette, press keypad 1-5 and click Enter");
	free(name);
}
