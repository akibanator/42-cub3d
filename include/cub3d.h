/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akenji-a <akenji-a@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 17:45:39 by akenji-a          #+#    #+#             */
/*   Updated: 2023/06/15 17:53:23 by akenji-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

/********** INCLUDES **********/

#include "constants.h"
#include "libft.h"
#include "mlx.h"
#include "stdio.h"
#include "unistd.h"
#include <X11/X.h>		// Used for KeyPress, KeyRelease macros
#include <X11/keysym.h> // Keyboard Key Symbols Macros
#include <errno.h>
#include <float.h>	// DBL_MAX
#include <limits.h> // INT_MAX
#include <math.h>
#include <stdlib.h>

/********** STRUCTS **********/

typedef struct s_img
{
	void *mlx_img;
	char *addr;
	int	  bits_per_pixel;
	int	  line_length;
	int	  endian;
} t_img;

typedef struct s_vector
{
	double x;
	double y;
} t_vector;

typedef struct s_player
{
	t_vector pos;
	int		 radius;
	int		 rotation_input;
	int		 walk_direction;
	double	 rotation_angle;
	double	 walk_speed;
	double	 turn_speed;
} t_player;

typedef struct s_data
{
	void	 *mlx;
	void	 *window;
	t_img	 *canvas;
	t_player *player;
	char	**map;
} t_data;

typedef struct s_ray
{
	double	 angle;
	t_vector hit;
	char	 hit_tag;
	int		 was_hit_vertical;
	double	 distance;
	t_vector dir;
} t_ray;

/********** PROTOTYPES **********/

// Update
int	 update(void *data);
void update_player(t_data *data);
// Render
void   draw_pixel(t_img *canvas, int x, int y, int color);
void   draw_rect(t_img *canvas, int x, int y, int width, int height, int color);
void   draw_walls(t_data *data);
void   draw_wall_strip(t_img *canvas, int x, int height, int wallColor);
void   render_canvas(t_data *data);
t_ray  ray_new(double angle);
double ray_get_distance(t_vector origin, t_ray ray);
t_ray  raycast(t_vector origin, double ray_angle);
// Input
int	 handle_keypress(int keysym, t_data *data);
int	 handle_keyrelease(int keysym, t_data *data);
int	 handle_close(t_data *data);
void exit_game(t_data *data);
// Utils
int get_color_value(int red, int green, int blue);

#endif
