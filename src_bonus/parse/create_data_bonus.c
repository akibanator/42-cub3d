/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_data_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:21:02 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:18:26 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

t_map	create_data(char *file, void *mlx)
{
	t_map	map;
	char	**map_data;

	map_data = get_map_data(file);
	map = get_assets(map_data, mlx);
	map.size = get_size(map_data);
	map.grid = get_grid(map_data, map.size);
	map.start_dir = get_start_dir(map.grid);
	map.start_pos = get_start_pos(map.grid);
	free_split(map_data);
	return (map);
}
