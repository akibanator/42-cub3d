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

int handle_keypress(int keysym, t_data *data)
{
	t_player *player;

	player = data->player;
	if (keysym == XK_Escape)
		exit_game(data);
	else if (keysym == XK_w)
		player->walk_direction = 1;
	else if (keysym == XK_s)
		player->walk_direction = -1;
	else if (keysym == XK_d)
		player->rotation_input = 1;
	else if (keysym == XK_a)
		player->rotation_input = -1;
	return (0);
}

int handle_keyrelease(int keysym, t_data *data)
{
	t_player *player;

	player = data->player;
	if (keysym == XK_w || keysym == XK_s)
		player->walk_direction = 0;
	if (keysym == XK_a || keysym == XK_d)
		player->rotation_input = 0;
	return (0);
}

int handle_close(t_data *data)
{
	exit_game(data);
	return (0);
}
