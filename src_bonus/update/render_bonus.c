/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 16:51:03 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/24 02:22:24 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	render_canvas(t_data *data)
{
	if (data->window == NULL)
		return ;
	draw_walls(data);
	mlx_clear_window(data->mlx, data->window);
	mlx_put_image_to_window(data->mlx, data->window, data->canvas->mlx_img, 0,
		0);
}
