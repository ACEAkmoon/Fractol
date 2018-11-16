/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:16:56 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:16:58 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <math.h>
# include <stdint.h>
# include "structs.h"
# include "libft/libft.h"
# include <minilibx/mlx.h>

# define NAME			"Project - Fract'ol"
# define INF_CLR		0xFFFFFF

# define WIN_W 			800
# define WIN_H 			600
# define TOP_MRGN		5
# define LFT_MRGN		10
# define ZOOM 			1.1f

# define ESC			53
# define LOCK			37
# define UP				126
# define DOWN			125
# define LEFT			123
# define RIGHT			124
# define P_UP			116
# define P_DOWN			121
# define NUM_0			82
# define NUM_1			83
# define NUM_PLUS		69
# define NUM_MINUS		78
# define NUM_ENTER		76
# define SCROLL_UP		4
# define SCROLL_DOWN	5

# define ERROR(x) 			if (x) ft_error("");
# define MAP_DELL(x, map)	if (x) ft_mlxdel(map);

t_pixel				ft_julia(int x, int y, t_view *v);
t_pixel				ft_mandelbrot(int x, int y, t_view *v);
t_pixel				ft_burningship(int x, int y, t_view *v);
t_pixel				ft_view_to_pixel(int x, int y, t_view *v);

t_map				*ft_init(char *str);
t_palette			*ft_color_palettes();
void				ft_solver(t_map *map);
void				ft_draw(t_map *map);
void				ft_error(char *err_str);
void				ft_display_controls(void);
void				ft_fractol_view(t_view *v);
void				ft_zooming(int x, int y, t_view *v, double z);
int					ft_get_color(t_pixel p, t_map *map);
int					ft_mouse_scroll(int button, int x, int y, t_map *map);
int					ft_mouse_bind(int button, int x, int y, t_map *map);
int					ft_mouse_move(int x, int y, t_map *map);
int					ft_key_hook(int key, t_map *map);

#endif
