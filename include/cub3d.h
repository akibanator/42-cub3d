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
#include <X11/X.h>		// Used for KeyPress, KeyRelease macros
#include <X11/keysym.h> // Keyboard Key Symbols Macros
#include <errno.h>
#include <float.h>	// DBL_MAX
#include <limits.h> // INT_MAX
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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

typedef struct s_assets
{
	t_img north_texture;
	t_img south_texture;
	t_img west_texture;
	t_img east_texture;
	int	  floor_color;
	int	  ceiling_color;
} t_assets;

typedef struct s_map
{
	t_vector start_dir;
	t_vector start_pos;
	t_vector size;
	char   **grid;
	t_assets assets;
} t_map;

typedef struct s_player
{
	t_vector pos;
	int		 radius;
	double	 rotation_input;
	double	 mouse_rotation;
	t_vector walk_direction;
	double	 rotation_angle;
	int		 mouse_mode;
} t_player;

typedef struct s_data
{
	void	 *mlx;
	void	 *window;
	t_img	 *canvas;
	t_player *player;
	t_map	  map;
} t_data;

// TODO: Add origin vector when creating the ray (Maybe???)
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

// Setup
void	  hooks_setup(t_data *data);
t_img	 *create_new_canvas(t_data *data, int width, int height);
t_player *player_init(void);
t_data	 *data_init(void);
// Check map grid
int map_has_wall_at(t_map map, t_vector point);
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
t_ray  raycast(t_vector origin, double ray_angle, t_map map);
// Input
int	 handle_keypress(int keysym, t_data *data);
int	 handle_keyrelease(int keysym, t_data *data);
int	 handle_close(t_data *data);
int	 handle_mouse(int x, int y, void *data);
int	 handle_window_leave(t_data *data);
void update_mouse(t_data *data);
void exit_game(t_data *data);
// Utils
int get_color_value(int red, int green, int blue);
// Parse
int	   check_args(int argc, char *argv[]);
int	   check_valid_ext(char *map, char *ext);
int	   check_map(char *file);
t_map  create_data(char *file, void *mlx);
char  *trimm_line(char *line);
size_t count_spaces(char *line);

#endif
