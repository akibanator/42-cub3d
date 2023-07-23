/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/20 19:21:37 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/20 19:21:37 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void hooks_setup(t_data *data)
{
	mlx_hook(data->window, MotionNotify, PointerMotionMask, &handle_mouse, data);
	mlx_hook(data->window, KeyPress, KeyPressMask, &handle_keypress, data);
	mlx_hook(data->window, KeyRelease, KeyReleaseMask, &handle_keyrelease, data);
	mlx_hook(data->window, DestroyNotify, NoEventMask, &handle_close, data);
	mlx_hook(data->window, LeaveNotify, LeaveWindowMask, &handle_window_leave, data);
	mlx_loop_hook(data->mlx, &update, data);
}
