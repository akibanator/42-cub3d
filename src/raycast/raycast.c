/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:10:46 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/14 15:10:46 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

double normalize_angle(double angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}

t_vector get_ray_dir(double ray_angle)
{
	t_vector dir;

	if (ray_angle < 0.5f * PI || ray_angle > 1.5 * PI)
		dir.x = 1;
	else
		dir.x = -1;
	if (ray_angle > 0 && ray_angle < PI)
		dir.y = -1;
	else
		dir.y = 1;
	return (dir);
}

char get_horz_hit_tag(t_ray ray, t_map map)
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

char get_vert_hit_tag(t_ray ray, t_map map)
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

t_ray get_horizontal_hit(t_vector origin, double ray_angle, t_map map)
{
	t_ray	 ray;
	t_vector intercept;
	t_vector step;

	ray = ray_new(ray_angle);
	intercept.y = floor(origin.y / TILE_SIZE) * TILE_SIZE;
	if (ray.dir.y > 0)
		intercept.y += TILE_SIZE;
	intercept.x = origin.x + (intercept.y - origin.y) / tan(ray.angle);
	step.y = TILE_SIZE;
	if (ray.dir.y < 0)
		step.y *= -1;
	step.x = TILE_SIZE / tan(ray.angle);
	if (ray.dir.x < 0 && step.x > 0)
		step.x *= -1;
	if (ray.dir.x > 0 && step.x < 0)
		step.x *= -1;
	ray.hit = intercept;
	while (is_ray_inside_map(ray, map))
	{
		ray.hit_tag = get_horz_hit_tag(ray, map);
		if (ray.hit_tag == '1')
		{
			ray.was_hit_vertical = FALSE;
			ray.distance = ray_get_distance(origin, ray);
			break;
		}
		ray.hit.x += step.x;
		ray.hit.y += step.y;
	}
	return (ray);
}

t_ray get_vertical_hit(t_vector origin, double ray_angle, t_map map)
{
	t_ray	 ray;
	t_vector intercept;
	t_vector step;

	ray = ray_new(ray_angle);
	intercept.x = floor(origin.x / TILE_SIZE) * TILE_SIZE;
	if (ray.dir.x > 0)
		intercept.x += TILE_SIZE;
	intercept.y = origin.y + (intercept.x - origin.x) * tan(ray.angle);
	step.x = TILE_SIZE;
	if (ray.dir.x < 0)
		step.x *= -1;
	step.y = TILE_SIZE * tan(ray.angle);
	if (ray.dir.y < 0 && step.y > 0)
		step.y *= -1;
	if (ray.dir.y > 0 && step.y < 0)
		step.y *= -1;
	ray.hit = intercept;
	while (is_ray_inside_map(ray, map))
	{
		ray.hit_tag = get_vert_hit_tag(ray, map);
		if (ray.hit_tag == '1')
		{
			ray.was_hit_vertical = TRUE;
			ray.distance = ray_get_distance(origin, ray);
			break;
		}
		ray.hit.x += step.x;
		ray.hit.y += step.y;
	}
	return (ray);
}

t_ray raycast(t_vector origin, double ray_angle, t_map map)
{
	t_ray vertical_ray;
	t_ray horizontal_ray;

	horizontal_ray = get_horizontal_hit(origin, ray_angle, map);
	vertical_ray = get_vertical_hit(origin, ray_angle, map);
	if (vertical_ray.distance < horizontal_ray.distance)
		return (vertical_ray);
	return (horizontal_ray);
}
