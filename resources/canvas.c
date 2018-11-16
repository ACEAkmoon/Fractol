/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:19:07 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:19:09 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_image			*ft_del_image(t_map *map, t_image *img)
{
	if (img)
	{
		if (img->image)
			mlx_destroy_image(map->mlx, img->image);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

static t_map			*ft_mlxdel(t_map *map)
{
	if (map->win)
		mlx_destroy_window(map->mlx, map->win);
	if (map->image)
		ft_del_image(map, map->image);
	ft_memdel((void **)&map);
	return (NULL);
}

static t_image			*ft_new_image(t_map *map)
{
	t_image				*img;

	RETURN_NULL(!(img = ft_memalloc(sizeof(t_image))));
	if (!(img->image = mlx_new_image(map->mlx, WIN_W, WIN_H)))
		return (ft_del_image(map, img));
	img->ptr = mlx_get_data_addr(img->image, &img->bt_px, \
		&img->size_line, &img->endian);
	img->bt_px /= 8;
	return (img);
}

t_map					*ft_init(char *str)
{
	int					i;
	t_map				*map;
	static t_fractol	arr[4] = {
		{"Julia", ft_julia},
		{"Mandelbrot", ft_mandelbrot},
		{"Burningship", ft_burningship},
		{NULL, NULL}
	};

	i = 0;
	while (arr[i].name && ft_strcmp(arr[i].name, str))
		i++;
	RETURN_NULL(!(map = ft_memalloc(sizeof(t_map))));
	MAP_DELL(!(map->mlx = mlx_init()), map);
	MAP_DELL(!(map->image = ft_new_image(map)), map);
	MAP_DELL(!(map->data = ft_memalloc(sizeof(t_pixel) * WIN_W * WIN_H)), map);
	MAP_DELL(!(map->win = mlx_new_window(map->mlx, WIN_W, WIN_H, NAME)), map);
	map->palette = ft_color_palettes();
	map->mouselock = 1 - map->mouselock;
	map->mouse.isdown = 0;
	map->fractol = &arr[i];
	map->smoothing = 1;
	return (map);
}
