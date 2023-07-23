/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_player.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:42:46 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/20 19:42:46 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double get_move_angle(t_player *player)
{
	const t_vector dir = player->walk_direction;
	const double   angle = player->rotation_angle;

	if (dir.x > 0 && dir.y > 0)
		return (angle + (PI / 4));
	else if (dir.x < 0 && dir.y > 0)
		return (angle - (PI / 4));
	else if (dir.x > 0 && dir.y < 0)
		return (angle + (3 * PI / 4));
	else if (dir.x < 0 && dir.y < 0)
		return (angle - (3 * PI / 4));
	else if (dir.x > 0 && dir.y == 0)
		return (angle + (PI / 2));
	else if (dir.x < 0 && dir.y == 0)
		return (angle - (PI / 2));
	else if (dir.x == 0 && dir.y > 0)
		return (angle);
	else
		return (angle - PI);
}

void update_player(t_data *data)
{
	t_player *player;
	t_vector  new_pos;
	double	  move_angle;

	player = data->player;
	player->rotation_angle += player->mouse_rotation;
	player->rotation_angle += player->rotation_input;
	move_angle = get_move_angle(player);
	new_pos.x = player->pos.x;
	new_pos.y = player->pos.y;
	if (player->walk_direction.x != 0 || player->walk_direction.y != 0)
	{
		new_pos.x += cos(move_angle) * WALK_SPEED;
		new_pos.y += sin(move_angle) * WALK_SPEED;
		t_ray ray = raycast(new_pos, move_angle, data->map);
		if (ray.distance <= player->radius)
			return;
	}
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
}
