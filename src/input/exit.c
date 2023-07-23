/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 02:13:43 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 03:38:43 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void free_assets(void *mlx, t_assets assets);
static void free_map_grid(t_map map);

void exit_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->window);
	mlx_loop_end(data->mlx);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->canvas->mlx_img);
	free(data->canvas);
	free_assets(data->mlx, data->map.assets);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free_map_grid(data->map);
	free(data->player);
	free(data);
	exit(0);
}

static void free_assets(void *mlx, t_assets assets)
{
	mlx_destroy_image(mlx, assets.north_texture.mlx_img);
	mlx_destroy_image(mlx, assets.east_texture.mlx_img);
	mlx_destroy_image(mlx, assets.west_texture.mlx_img);
	mlx_destroy_image(mlx, assets.south_texture.mlx_img);
}

static void free_map_grid(t_map map)
{
	int i;

	i = 0;
	while (i < map.size.y)
	{
		free(map.grid[i]);
		i++;
	}
	free(map.grid);
}
