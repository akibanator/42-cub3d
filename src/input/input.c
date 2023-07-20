/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 15:11:19 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/14 15:11:19 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdio.h>

int handle_keypress(int keysym, t_data *data)
{
	t_player *player;

	player = data->player;
	if (keysym == XK_Escape)
		exit_game(data);
	else if (keysym == XK_w)
		player->walk_direction.y = 1;
	else if (keysym == XK_s)
		player->walk_direction.y = -1;
	else if (keysym == XK_d)
		player->walk_direction.x = 1;
	else if (keysym == XK_a)
		player->walk_direction.x = -1;
	else if (keysym == XK_q)
		player->rotation_input = player->turn_speed * -1;
	else if (keysym == XK_e)
		player->rotation_input = player->turn_speed;
	return (0);
}

int handle_keyrelease(int keysym, t_data *data)
{
	t_player *player;

	player = data->player;
	if (keysym == XK_w && player->walk_direction.y == 1)
		player->walk_direction.y = 0;
	else if (keysym == XK_s && player->walk_direction.y == -1)
		player->walk_direction.y = 0;
	else if (keysym == XK_d && player->walk_direction.x == 1)
		player->walk_direction.x = 0;
	else if (keysym == XK_a && player->walk_direction.x == -1)
		player->walk_direction.x = 0;
	else if (keysym == XK_q)
		player->rotation_input = 0;
	else if (keysym == XK_e)
		player->rotation_input = 0;
	return (0);
}

int handle_mouse(int x, int y, void *data)
{
	t_data	 *game_data;
	t_player *player;
	double	  sense;
	int		  deadzone;

	(void) y;
	game_data = (t_data *) data;
	player = game_data->player;
	sense = 0.00002;
	deadzone = 200;
	if (x > WINDOW_WIDTH / 2 + deadzone)
		player->mouse_rotation = (x - WINDOW_WIDTH / 2.0) * sense;
	else if (x < WINDOW_WIDTH / 2 - deadzone)
		player->mouse_rotation = (WINDOW_WIDTH / 2.0 - x) * -sense;
	else if (x > WINDOW_WIDTH / 2 - deadzone && x < WINDOW_WIDTH / 2 + deadzone)
		player->mouse_rotation = 0;
	return (0);
}

// WARNING: Unnecessary hook
int handle_window_enter(t_data *data)
{
	t_player *player;

	player = data->player;
	(void) player;
	return (0);
}

int handle_window_leave(t_data *data)
{
	t_player *player;
	player = data->player;
	player->mouse_rotation = 0;
	return (0);
}

int handle_close(t_data *data)
{
	exit_game(data);
	return (0);
}
