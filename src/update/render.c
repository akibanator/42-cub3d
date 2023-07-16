/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:51:03 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/14 16:51:03 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void render_canvas(t_data *data)
{
	if (data->window == NULL)
		return;
	draw_walls(data);
	mlx_put_image_to_window(data->mlx, data->window, data->canvas->mlx_img, 0, 0);
}
