/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_wall.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:45:11 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/20 19:45:11 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int map_has_wall_at(t_map map, t_vector point)
{
	int grid_x;
	int grid_y;

	grid_x = (int) floor(point.x / TILE_SIZE);
	grid_y = (int) floor(point.y / TILE_SIZE);
	// printf("grid_x:%d grid_y:%d tag: %c\n", grid_x, grid_y, map.grid[grid_y][grid_x]);
	if (grid_x >= map.size.x || grid_x <= 0)
		return (TRUE);
	else if (grid_y >= map.size.y || grid_y <= 0)
		return (TRUE);
	if (map.grid[grid_y][grid_x] == '1')
		return (TRUE);
	return (FALSE);
}
