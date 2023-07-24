/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 03:48:13 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 20:23:05 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall	get_wall(t_data *data, t_ray ray, t_img texture);
static int		get_wall_height(t_ray ray, t_player *player,
					double dist_proj_plane);
static int		draw_wall_texture(t_img *canvas, t_wall wall, int row, int col);
static void		draw_wall(t_img *canvas, int x, t_wall wall);

void	draw_walls(t_data *data)
{
	t_ray	ray;
	double	ray_angle;
	int		col;
	t_img	wall_tex;
	t_wall	wall;

	col = 0;
	while (col < NUM_RAYS)
	{
		ray_angle = data->player->rotation_angle + atan((col - NUM_RAYS / 2.0)
				/ data->dist_proj_plane);
		ray = raycast(data->player->pos, ray_angle, data->map);
		if (ray.was_hit_vertical && ray.dir.x > 0)
			wall_tex = data->map.assets.east_texture;
		else if (ray.was_hit_vertical && ray.dir.x < 0)
			wall_tex = data->map.assets.west_texture;
		else if (!ray.was_hit_vertical && ray.dir.y < 0)
			wall_tex = data->map.assets.north_texture;
		else
			wall_tex = data->map.assets.south_texture;
		wall = get_wall(data, ray, wall_tex);
		draw_wall(data->canvas, col, wall);
		ray_angle += (FOV_ANGLE * (PI / 180)) / NUM_RAYS;
		col++;
	}
}

static t_wall	get_wall(t_data *data, t_ray ray, t_img texture)
{
	t_wall	wall;

	wall.height = get_wall_height(ray, data->player, data->dist_proj_plane);
	wall.height *= UPSCALE;
	wall.texture = texture;
	wall.top = (WINDOW_HEIGHT / 2) - (wall.height / 2);
	if (wall.top < 0)
		wall.top = 0;
	wall.bot = (WINDOW_HEIGHT / 2) + (wall.height / 2);
	if (wall.bot > 0)
		wall.bot = WINDOW_HEIGHT;
	wall.floor_color = data->map.assets.floor_color;
	wall.ceiling_color = data->map.assets.ceiling_color;
	if (ray.was_hit_vertical)
		wall.tex_x = (int)ray.hit.y % TILE_SIZE;
	else
		wall.tex_x = (int)ray.hit.x % TILE_SIZE;
	return (wall);
}

static int	get_wall_height(t_ray ray, t_player *player, double dist_proj_plane)
{
	double	perp_distance;
	double	projected_wall_height;
	int		wall_height;

	perp_distance = ray.distance * cos(ray.angle - player->rotation_angle);
	projected_wall_height = (TILE_SIZE / perp_distance) * dist_proj_plane;
	wall_height = (int)projected_wall_height;
	return (wall_height);
}

static int	draw_wall_texture(t_img *canvas, t_wall wall, int row, int col)
{
	int	color;
	int	dist_from_top;

	while (row < wall.bot)
	{
		dist_from_top = row + (wall.height / 2) - (WINDOW_HEIGHT / 2);
		wall.tex_y = dist_from_top * ((double)TILE_SIZE / wall.height);
		if (wall.tex_y >= TILE_SIZE)
			break ;
		color = get_tex_color(wall.texture, wall.tex_x, wall.tex_y);
		draw_pixel(canvas, col, row, color);
		row++;
	}
	return (row);
}

static void	draw_wall(t_img *canvas, int x, t_wall wall)
{
	int	row;
	int	col;

	col = x * UPSCALE;
	while (col < x * UPSCALE + UPSCALE)
	{
		row = 0;
		while (row < wall.top)
		{
			draw_pixel(canvas, col, row, wall.ceiling_color);
			row++;
		}
		row = draw_wall_texture(canvas, wall, row, col);
		while (row < WINDOW_HEIGHT)
		{
			draw_pixel(canvas, col, row, wall.floor_color);
			row++;
		}
		col++;
	}
}
