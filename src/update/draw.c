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
#include <stdio.h>

void draw_pixel(t_img *canvas, int x, int y, int color)
{
	char *pixel;
	int	  pixel_x;
	int	  pixel_y;

	pixel_y = y * canvas->line_length;
	pixel_x = x * (canvas->bits_per_pixel / 8);
	pixel = canvas->addr + (pixel_y + pixel_x);
	*(int *) pixel = color;
}

void draw_rect(t_img *canvas, int x, int y, int width, int height, int color)
{
	int row;
	int col;

	if (x + width > WINDOW_WIDTH || y + height > WINDOW_HEIGHT)
		return;
	else if (x + width < 0 || y + height < 0)
		return;
	row = y;
	while (row < y + height)
	{
		col = x;
		while (col < x + width)
		{
			draw_pixel(canvas, col, row, color);
			col++;
		}
		row++;
	}
}

static int get_wall_strip_height(t_ray ray, t_player *player)
{
	double dist_proj_plane;
	double perp_distance;
	double projected_wall_height;
	int	   wall_strip_height;

	perp_distance = ray.distance * cos(ray.angle - player->rotation_angle);
	dist_proj_plane = (GAME_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	projected_wall_height = (TILE_SIZE / perp_distance) * dist_proj_plane;
	wall_strip_height = (int) projected_wall_height;
	return (wall_strip_height);
}

void draw_wall_strip(t_img *canvas, int x, int height, int wallColor)
{
	int col;
	int row;
	int wall_top_pixel;
	int wall_bot_pixel;

	height = height * UPSCALE;
	if (height > WINDOW_HEIGHT || height < 0)
		height = WINDOW_HEIGHT;
	col = x * UPSCALE;
	row = 0;
	wall_top_pixel = (WINDOW_HEIGHT / 2) - (height / 2);
	wall_bot_pixel = (WINDOW_HEIGHT / 2) + (height / 2);
	while (col < x * UPSCALE + UPSCALE)
	{
		row = 0;
		while (row < wall_top_pixel)
		{
			draw_pixel(canvas, col, row, 0x0);
			row++;
		}
		while (row < wall_bot_pixel)
		{
			draw_pixel(canvas, col, row, wallColor);
			row++;
		}
		while (row < WINDOW_HEIGHT)
		{
			draw_pixel(canvas, col, row, 0xBBBBBB);
			row++;
		}
		col++;
	}
}

// TODO: Refactor color
void draw_walls(t_data *data)
{
	t_ray  ray;
	double ray_angle;
	int	   wall_strip_height;
	int	   game_x;
	double dist_proj_plane;

	dist_proj_plane = (GAME_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	game_x = 0;
	while (game_x < NUM_RAYS)
	{
		ray_angle = data->player->rotation_angle + atan((game_x - NUM_RAYS / 2.0) / dist_proj_plane);
		ray = raycast(data->player->pos, ray_angle);
		wall_strip_height = get_wall_strip_height(ray, data->player);
		int color;
		if (ray.was_hit_vertical && ray.dir.x > 0)
			color = 0x0000FF;
		else if (ray.was_hit_vertical && ray.dir.x < 0)
			color = 0x0000AA;
		else if (!ray.was_hit_vertical && ray.dir.y < 0)
			color = 0xFF0000;
		else if (!ray.was_hit_vertical && ray.dir.y > 0)
			color = 0xAA0000;
		else
			color = 0xFFFFFF;
		draw_wall_strip(data->canvas, game_x, wall_strip_height, color);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		game_x++;
	}
}
