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

int get_tex_color(t_img tex, int x, int y)
{
	int color;
	int pixel_x;
	int pixel_y;

	pixel_y = y * tex.line_length;
	pixel_x = x * (tex.bits_per_pixel / 8);
	color = *(int *) (tex.addr + (pixel_y + pixel_x));
	return (color);
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

// WARNING: Changed GAME_WIDTH to WINDOW_WIDTH
static int get_wall_strip_height(t_ray ray, t_player *player)
{
	double dist_proj_plane;
	double perp_distance;
	double projected_wall_height;
	int	   wall_strip_height;

	perp_distance = ray.distance * cos(ray.angle - player->rotation_angle);
	dist_proj_plane = (WINDOW_WIDTH / 2.0) / tan(FOV_ANGLE / 2);
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
	// if (height > WINDOW_HEIGHT || height < 0)
	// 	height = WINDOW_HEIGHT;
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

void draw_wall_tex(t_img *canvas, int x, int height, t_img wall_tex, t_assets assets, t_ray ray)
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
	// if (height > WINDOW_HEIGHT)
	// 	printf("Height :%d\n", height);
	// if (height > WINDOW_HEIGHT || height < 0)
	// 	height = WINDOW_HEIGHT;
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
			if (row < 0 || row >= WINDOW_HEIGHT)
				printf("CRASH!! row: %d\n", row);
			draw_pixel(canvas, col, row, assets.ceiling_color);
			row++;
		}
		while (row < wall_bot)
		{
			dist_from_top = row + (height / 2) - (WINDOW_HEIGHT / 2);
			tex_offset_y = dist_from_top * ((double) TILE_SIZE / height);
			// tex_offset_y = (row - wall_top) * ((double) TILE_SIZE / height);
			// if (tex_offset_y >= TILE_SIZE)
			// 	tex_offset_y = 64;
			if (tex_offset_y >= TILE_SIZE)
				break;
			color = get_tex_color(wall_tex, tex_offset_x, tex_offset_y);
			if (row < 0 || row >= WINDOW_HEIGHT)
				printf("CRASH!! row: %d\n", row);
			draw_pixel(canvas, col, row, color);
			row++;
		}
		while (row < WINDOW_HEIGHT)
		{
			if (row < 0 || row >= WINDOW_HEIGHT)
				printf("CRASH!! row: %d\n", row);
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
	double dist_proj_plane;
	t_img  wall_tex;

	dist_proj_plane = (GAME_WIDTH / 2.0) / tan(FOV_ANGLE / 2.0);
	col = 0;
	t_ray test_ray = raycast(data->player->pos, data->player->rotation_angle, data->map);
	int grid_hit_x = (int) floor(test_ray.hit.x / TILE_SIZE);
	int grid_hit_y = (int) floor(test_ray.hit.y / TILE_SIZE);
	printf("HitX: %d HitY %d Distance %f\n", grid_hit_x, grid_hit_y, test_ray.distance);
	int px = (int) floor(data->player->pos.x / TILE_SIZE);
	int py = (int) floor(data->player->pos.y / TILE_SIZE);
	printf("PX: %d PY: %d\n", px, py);
	int wall_height = get_wall_strip_height(test_ray, data->player);
	printf("Wall Height %d\n", wall_height);
	while (col < NUM_RAYS)
	{
		ray_angle = data->player->rotation_angle + atan((col - NUM_RAYS / 2.0) / dist_proj_plane);
		ray = raycast(data->player->pos, ray_angle, data->map);
		wall_strip_height = get_wall_strip_height(ray, data->player);
		// int color;
		// if (ray.was_hit_vertical && ray.dir.x > 0)
		// 	color = 0x0000FF;
		// else if (ray.was_hit_vertical && ray.dir.x < 0)
		// 	color = 0x0000AA;
		// else if (!ray.was_hit_vertical && ray.dir.y < 0)
		// 	color = 0xFF0000;
		// else if (!ray.was_hit_vertical && ray.dir.y > 0)
		// 	color = 0xAA0000;
		// else
		// 	color = 0xFFFFFF;
		if (ray.was_hit_vertical && ray.dir.x > 0)
			wall_tex = data->map.assets.east_texture;
		else if (ray.was_hit_vertical && ray.dir.x < 0)
			wall_tex = data->map.assets.west_texture;
		else if (!ray.was_hit_vertical && ray.dir.y < 0)
			wall_tex = data->map.assets.north_texture;
		else
			wall_tex = data->map.assets.south_texture;
		// draw_wall_strip(data->canvas, game_x, wall_strip_height, color);
		draw_wall_tex(data->canvas, col, wall_strip_height, wall_tex, data->map.assets, ray);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		col++;
	}
}
