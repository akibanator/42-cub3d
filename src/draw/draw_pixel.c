/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcorrea- <bruuh.cor@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 02:37:04 by bcorrea-          #+#    #+#             */
/*   Updated: 2023/07/23 02:37:04 by bcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
