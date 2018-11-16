/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractols.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/13 15:41:44 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/13 15:41:47 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		ft_fractol_view(t_view *v)
{
	v->xmin = -2.5f;
	v->xmax = 2.0f;
	v->ymin = -1.0f;
	v->ymax = 1.0f;
}

t_pixel		ft_view_to_pixel(int x, int y, t_view *v)
{
	t_pixel	p;

	p.i = 0;
	p.x = (((double)x / WIN_W) * (v->xmax - v->xmin)) * v->zoom \
		+ v->xmin + v->offx;
	p.y = (((double)y / WIN_H) * (v->ymax - v->ymin)) * v->zoom \
		+ v->ymin + v->offy;
	return (p);
}

t_pixel		ft_burningship(int x, int y, t_view *v)
{
	t_pixel		p;
	t_pixel		c;
	t_pixel		tmp;

	p.i = 0;
	p = ft_view_to_pixel(x, y, v);
	c = ft_view_to_pixel(x, y, v);
	while (p.x * p.x + p.y * p.y < (1 << 4) && p.i < v->max)
	{
		p.x = fabs(p.x);
		p.y = fabs(p.y);
		tmp.x = p.x * p.x - p.y * p.y + c.x;
		tmp.y = p.x * p.y * 2 + c.y;
		/*if (p.x == tmp.x && p.y == tmp.y)
		{
			p.i = v->max;
			break ;
		}*/
		p.x = tmp.x;
		p.y = tmp.y;
		p.i++;
	}
	return (p);
}

t_pixel		ft_julia(int x, int y, t_view *v)
{
	t_pixel		p;
	t_pixel		c;
	t_pixel		tmp;

	p.i = 0;
	c = v->mouse;
	p = ft_view_to_pixel(x, y, v);
	while (p.x * p.x + p.y * p.y < (1 << 4) && p.i < v->max)
	{
		tmp.x = p.x * p.x - p.y * p.y + c.x;
		tmp.y = p.x * p.y * 2 + c.y;
		/*if (p.x == tmp.x && p.y == tmp.y)
		{
			p.i = v->max;
			break ;
		}*/
		p.x = tmp.x;
		p.y = tmp.y;
		p.i++;
	}
	return (p);
}

t_pixel		ft_mandelbrot(int x, int y, t_view *v)
{
	t_pixel		p;
	t_pixel		c;
	t_pixel		tmp;

	p.i = 0;
	p = ft_view_to_pixel(x, y, v);
	c = ft_view_to_pixel(x, y, v);
	while (p.x * p.x + p.y * p.y < (1 << 4) && p.i < v->max)
	{
		tmp.x = p.x * p.x - p.y * p.y + c.x;
		tmp.y = p.x * p.y * 2 + c.y;
		/*if (p.x == tmp.x && p.y == tmp.y)
		{
			p.i = v->max;
			break ;
		}*/
		p.x = tmp.x;
		p.y = tmp.y;
		p.i++;
	}
	return (p);
}
