/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:10:46 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 03:36:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray get_horizontal_ray(t_vector origin, double ray_angle, t_map map);
static t_ray get_vertical_ray(t_vector origin, double ray_angle, t_map map);

t_ray raycast(t_vector origin, double ray_angle, t_map map)
{
	t_ray vertical_ray;
	t_ray horizontal_ray;

	horizontal_ray = get_horizontal_ray(origin, ray_angle, map);
	vertical_ray = get_vertical_ray(origin, ray_angle, map);
	if (vertical_ray.distance < horizontal_ray.distance)
		return (vertical_ray);
	return (horizontal_ray);
}

static t_ray get_horizontal_ray(t_vector origin, double ray_angle, t_map map)
{
	t_ray	 ray;
	t_vector intercept;
	t_vector step;

	ray = ray_new(origin, ray_angle);
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
	ray = get_horizontal_hit(ray, map, step);
	return (ray);
}

static t_ray get_vertical_ray(t_vector origin, double ray_angle, t_map map)
{
	t_ray	 ray;
	t_vector intercept;
	t_vector step;

	ray = ray_new(origin, ray_angle);
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
	ray = get_vertical_hit(ray, map, step);
	return (ray);
}
