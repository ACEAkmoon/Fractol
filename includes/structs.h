/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/06 19:46:43 by akrushin          #+#    #+#             */
/*   Updated: 2018/11/06 19:46:44 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <pthread.h>

# define THREADS 	4

typedef struct		s_argb
{
	uint8_t		r;
	uint8_t		g;
	uint8_t		b;
	uint8_t		a;
}					t_argb;

typedef union		u_color
{
	int			value;
	t_argb		argb;
}					t_color;

typedef struct		s_palette
{
	uint8_t		count;
	int			colors[5];
}					t_palette;

typedef struct		s_mouse
{
	char		isdown;
	int			x;
	int			y;
	int			lastx;
	int			lasty;
}					t_mouse;

typedef struct		s_image
{
	void		*image;
	char		*ptr;
	int			bt_px;
	int			size_line;
	int			endian;
}					t_image;

typedef struct		s_pixel
{
	double		x;
	double		y;
	long		i;
}					t_pixel;

typedef struct		s_view
{
	double		xmin;
	double		xmax;
	double		ymin;
	double		ymax;
	double		zoom;
	double		offx;
	double		offy;
	long		max;
	t_pixel		mouse;
}					t_view;

typedef struct		s_fractol
{
	char		*name;
	t_pixel		(*ft_fractol)(int x, int y, t_view *v);
}					t_fractol;

typedef struct s_map	t_map;

typedef struct		s_thread
{
	int			id;
	t_map		*map;
}					t_thread;

struct				s_map
{
	void		*mlx;
	void		*win;
	t_view		view;
	t_pixel		*data;
	t_image		*image;
	t_mouse		mouse;
	t_fractol	*fractol;
	t_palette	*palette;
	int			smoothing;
	int			mouselock;
	pthread_t	pthread[THREADS];
	t_thread	threads[THREADS];
};

#endif
