/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:19:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 03:34:23 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char get_horz_hit_tag(t_ray ray, t_map map);
static char get_vert_hit_tag(t_ray ray, t_map map);

t_ray get_horizontal_hit(t_ray ray, t_map map, t_vector step)
{
	while (is_ray_inside_map(ray, map))
	{
		ray.hit_tag = get_horz_hit_tag(ray, map);
		if (ray.hit_tag == '1')
		{
			ray.was_hit_vertical = FALSE;
			ray.distance = ray_get_distance(ray);
			break;
		}
		ray.hit.x += step.x;
		ray.hit.y += step.y;
	}
	return (ray);
}

t_ray get_vertical_hit(t_ray ray, t_map map, t_vector step)
{
	while (is_ray_inside_map(ray, map))
	{
		ray.hit_tag = get_vert_hit_tag(ray, map);
		if (ray.hit_tag == '1')
		{
			ray.was_hit_vertical = TRUE;
			ray.distance = ray_get_distance(ray);
			break;
		}
		ray.hit.x += step.x;
		ray.hit.y += step.y;
	}
	return (ray);
}

static char get_horz_hit_tag(t_ray ray, t_map map)
{
	int map_x;
	int map_y;
	int offset;

	map_x = (int) floor(ray.hit.x / TILE_SIZE);
	if (ray.dir.y < 0)
		offset = 1;
	else
		offset = 0;
	map_y = (int) floor((ray.hit.y - offset) / TILE_SIZE);
	if (map_x < 0 || map_x >= map.size.x)
		return ('1');
	else if (map_y < 0 || map_y >= map.size.y)
		return ('1');
	return (map.grid[map_y][map_x]);
}

static char get_vert_hit_tag(t_ray ray, t_map map)
{
	int map_x;
	int map_y;
	int offset;

	if (ray.dir.x < 0)
		offset = 1;
	else
		offset = 0;
	map_x = (int) floor((ray.hit.x - offset) / TILE_SIZE);
	map_y = (int) floor(ray.hit.y / TILE_SIZE);
	if (map_x < 0 || map_x >= map.size.x)
		return ('1');
	else if (map_y < 0 || map_y >= map.size.y)
		return ('1');
	return (map.grid[map_y][map_x]);
}
