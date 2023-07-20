/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:19:58 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/20 19:19:58 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_img *create_new_canvas(t_data *data, int width, int height)
{
	t_img *canvas;

	canvas = malloc(sizeof(t_img));
	if (canvas == NULL)
		return (NULL);
	canvas->mlx_img = mlx_new_image(data->mlx, width, height);
	canvas->addr = mlx_get_data_addr(canvas->mlx_img, &canvas->bits_per_pixel,
									 &canvas->line_length, &canvas->endian);
	return (canvas);
}

t_player *player_init(void)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	if (player == NULL)
		return (NULL);
	player->pos.x = 2.5 * TILE_SIZE;
	player->pos.y = 2.5 * TILE_SIZE;
	player->radius = 5;
	player->rotation_input = 0;
	player->mouse_rotation = 0;
	player->walk_direction.x = 0;
	player->walk_direction.y = 0;
	player->rotation_angle = PI / 2;
	player->walk_speed = 1;
	player->turn_speed = 0.01;
	return (player);
}

t_data *data_init(void)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (NULL);
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		free(data);
		return (NULL);
	}
	data->window = mlx_new_window(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3d");
	if (data->window == NULL)
	{
		free(data->mlx);
		free(data);
		return (NULL);
	}
	data->player = player_init();
	data->canvas = create_new_canvas(data, WINDOW_WIDTH, WINDOW_HEIGHT);
	return (data);
}