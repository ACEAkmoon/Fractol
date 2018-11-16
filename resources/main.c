/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akrushin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 18:20:44 by akrushin          #+#    #+#             */
/*   Updated: 2018/10/23 18:20:45 by akrushin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	exit_x(void)
{
	exit(EXIT_SUCCESS);
}

int			main(int ac, char **av)
{
	t_map	*map;

	if (ac == 2)
	{
		ERROR(!(map = ft_init(av[1])));
		ERROR(!map->fractol->name);
		ft_display_controls();
		ft_solver(map);
		mlx_key_hook(map->win, ft_key_hook, map);
		mlx_hook(map->win, 5, 1L << 3, ft_mouse_bind, map);
		mlx_hook(map->win, 4, 1L << 3, ft_mouse_scroll, map);
		mlx_hook(map->win, 6, 1L << 7, ft_mouse_move, map);
		mlx_hook(map->win, 17, 1L << 17, exit_x, map);
		mlx_loop(map->mlx);
	}
	ft_error("usage: ./fractol Name_fractal");
	return (1);
}
