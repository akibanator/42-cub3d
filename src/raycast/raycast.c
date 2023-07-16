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

#define MAP_WIDTH 12
#define MAP_HEIGHT 24

char map[MAP_HEIGHT][MAP_WIDTH] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'}, {'1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1'}, {'1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'}, {'1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1'}, {'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

// TODO: map parameter
int map_has_wall_at(t_vector point)
{
	int grid_x;
	int grid_y;

	grid_x = (int) floor(point.x / TILE_SIZE);
	grid_y = (int) floor(point.y / TILE_SIZE);
	if (map[grid_y][grid_x] > '0')
		return (TRUE);
	return (FALSE);
}

char map_get_tile_tag(t_ray ray)
{
	int grid_x;
	int grid_y;
	int offset;

	grid_x = (int) floor(ray.hit.x / TILE_SIZE);
	if (ray.dir.y < 0)
		offset = 1;
	else
		offset = 0;
	grid_y = (int) floor((ray.hit.y - offset) / TILE_SIZE);
	if (grid_x < 0 || grid_x > MAP_WIDTH)
		return ('1');
	else if (grid_y < 0 || grid_y > MAP_HEIGHT)
		return ('1');
	return (map[grid_y][grid_x]);
}

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

int is_ray_inside_map(t_ray ray)
{
	if (ray.hit.x < 0 && ray.hit.x > MAP_WIDTH * TILE_SIZE)
		return (FALSE);
	else if (ray.hit.y < 0 && ray.hit.y > MAP_HEIGHT * TILE_SIZE)
		return (FALSE);
	return (TRUE);
}

char get_horz_hit_tag(t_ray ray)
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
	if (map_x < 0 || map_x > MAP_WIDTH)
		return ('1');
	else if (map_y < 0 || map_y > MAP_HEIGHT)
		return ('1');
	return (map[map_y][map_x]);
}

char get_vert_hit_tag(t_ray ray)
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
	if (map_x < 0 || map_x > MAP_WIDTH)
		return ('1');
	else if (map_y < 0 || map_y > MAP_HEIGHT)
		return ('1');
	return (map[map_y][map_x]);
}

t_ray get_horizontal_hit(t_vector origin, double ray_angle)
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
	while (is_ray_inside_map(ray))
	{
		// ray.hit_tag = map_get_tile_tag(ray);
		ray.hit_tag = get_horz_hit_tag(ray);
		if (ray.hit_tag != '0')
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

t_ray get_vertical_hit(t_vector origin, double ray_angle)
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
	while (is_ray_inside_map(ray))
	{
		// ray.hit_tag = map_get_tile_tag(ray);
		ray.hit_tag = get_vert_hit_tag(ray);
		if (ray.hit_tag != '0')
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

t_ray raycast(t_vector origin, double ray_angle)
{
	t_ray vertical_ray;
	t_ray horizontal_ray;

	horizontal_ray = get_horizontal_hit(origin, ray_angle);
	vertical_ray = get_vertical_hit(origin, ray_angle);
	if (vertical_ray.distance < horizontal_ray.distance)
		return (vertical_ray);
	return (horizontal_ray);
}
