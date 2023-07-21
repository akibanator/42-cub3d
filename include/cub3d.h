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

#include "libft.h"
#include "mlx.h"
#include "stdio.h"
#include "unistd.h"
#include <errno.h>
#include <stdlib.h>

#define TILE_SIZE 64

/* ***** Structs ***** */
typedef struct s_img {
  void *mlx_img;
  char *addr;
  int bits_per_pixel;
  int line_length;
  int endian;
} t_img;

typedef struct s_vector {
  double x;
  double y;
} t_vector;

typedef struct s_assets {
  t_img north_texture;
  t_img south_texture;
  t_img west_texture;
  t_img east_texture;
  int floor_color;
  int ceiling_color;
} t_assets;

typedef struct s_map {
  t_vector start_dir;
  t_vector start_pos;
  t_vector size;
  char **grid;
  t_assets assets;
} t_map;

typedef struct s_data {
  t_map map;
} t_data;

// Parse
int check_args(int argc, char *argv[]);
int check_valid_ext(char *map, char *ext);
int check_map(char *file);
t_map create_data(char *file, void *mlx);
char *trimm_line(char *line);
size_t count_spaces(char *line);
void free_map(char **grid);
int check_valid_grid(char **grid, t_vector size);

#endif
