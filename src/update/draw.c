/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:01:39 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/14 17:01:39 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int get_wall_strip_height(t_ray ray, t_player *player, double dist_proj_plane)
{
	double perp_distance;
	double projected_wall_height;
	int	   wall_strip_height;

	perp_distance = ray.distance * cos(ray.angle - player->rotation_angle);
	projected_wall_height = (TILE_SIZE / perp_distance) * dist_proj_plane;
	wall_strip_height = (int) projected_wall_height;
	return (wall_strip_height);
}

void draw_wall(t_img *canvas, int x, int height, t_img wall_tex, t_assets assets, t_ray ray)
{
	int col;
	int row;
	int wall_top;
	int wall_bot;
	int tex_offset_x;
	int tex_offset_y;
	int color;
	int dist_from_top;

	height = height * UPSCALE;
	col = x * UPSCALE;
	wall_top = (WINDOW_HEIGHT / 2) - (height / 2);
	if (wall_top < 0)
		wall_top = 0;
	wall_bot = (WINDOW_HEIGHT / 2) + (height / 2);
	if (wall_bot > 0)
		wall_bot = WINDOW_HEIGHT;
	if (ray.was_hit_vertical)
		tex_offset_x = (int) ray.hit.y % TILE_SIZE;
	else
		tex_offset_x = (int) ray.hit.x % TILE_SIZE;
	while (col < x * UPSCALE + UPSCALE)
	{
		row = 0;
		while (row < wall_top)
		{
			draw_pixel(canvas, col, row, assets.ceiling_color);
			row++;
		}
		while (row < wall_bot)
		{
			dist_from_top = row + (height / 2) - (WINDOW_HEIGHT / 2);
			tex_offset_y = dist_from_top * ((double) TILE_SIZE / height);
			if (tex_offset_y >= TILE_SIZE)
				break;
			color = get_tex_color(wall_tex, tex_offset_x, tex_offset_y);
			draw_pixel(canvas, col, row, color);
			row++;
		}
		while (row < WINDOW_HEIGHT)
		{
			draw_pixel(canvas, col, row, 0x707070);
			row++;
		}
		col++;
	}
}

void draw_walls(t_data *data)
{
	t_ray  ray;
	double ray_angle;
	int	   wall_strip_height;
	int	   col;
	t_img  wall_tex;

	col = 0;
	while (col < NUM_RAYS)
	{
		ray_angle = data->player->rotation_angle + atan((col - NUM_RAYS / 2.0) / data->dist_proj_plane);
		ray = raycast(data->player->pos, ray_angle, data->map);
		wall_strip_height = get_wall_strip_height(ray, data->player, data->dist_proj_plane);
		if (ray.was_hit_vertical && ray.dir.x > 0)
			wall_tex = data->map.assets.east_texture;
		else if (ray.was_hit_vertical && ray.dir.x < 0)
			wall_tex = data->map.assets.west_texture;
		else if (!ray.was_hit_vertical && ray.dir.y < 0)
			wall_tex = data->map.assets.north_texture;
		else
			wall_tex = data->map.assets.south_texture;
		draw_wall(data->canvas, col, wall_strip_height, wall_tex, data->map.assets, ray);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		col++;
	}
}
