/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 21:09:29 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/14 21:09:29 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <math.h>

static t_vector ray_get_dir(double ray_angle);
static double	normalize_angle(double angle);

t_ray ray_new(double angle)
{
	t_ray ray;

	ray.angle = normalize_angle(angle);
	ray.dir = ray_get_dir(ray.angle);
	ray.hit_tag = '0';
	ray.distance = INT_MAX;
	ray.was_hit_vertical = FALSE;
	return (ray);
}

double ray_get_distance(t_vector origin, t_ray ray)
{
	double distance;
	double adjacent;
	double opposite;

	adjacent = pow((ray.hit.x - origin.x), 2);
	opposite = pow((ray.hit.y - origin.y), 2);
	distance = sqrt(adjacent + opposite);
	return (distance);
}

static t_vector ray_get_dir(double ray_angle)
{
	t_vector dir;

	if (ray_angle < 0.5 * PI || ray_angle > 1.5 * PI)
		dir.x = 1;
	else
		dir.x = -1;
	if (ray_angle > 0 && ray_angle < PI)
		dir.y = 1;
	else
		dir.y = -1;
	return (dir);
}

static double normalize_angle(double angle)
{
	angle = remainder(angle, TWO_PI);
	if (angle < 0)
		angle = TWO_PI + angle;
	return (angle);
}
