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

/* ***** Structs ***** */
typedef struct s_vector {
  double x;
  double y;
} t_vector;

typedef struct s_assets {
  char *north_texture;
  char *south_texture;
  char *west_texture;
  char *east_texture;
  int floor_color;
  int ceiling_color;
} t_assets;

typedef struct s_map {
  t_vector start_dir;
  t_vector start_pos;
  size_t height;
  size_t width;
  char **grid;
  t_assets assets;
} t_map;

typedef struct s_data {
  t_map map;
} t_data;

// Parse
void check_args(int argc, char *argv[]);
int check_valid_ext(char *map, char *ext);
t_map create_map_data(char *file);
size_t get_nbr_lines(char *map);

char *skip_spaces(char *line);

// Cardinal
int handle_cardinal(char *line, char *info, t_args *args, int cord);

// RGB
int handle_rgb(char *line, char *info, t_args *args, int floor);

// MAP
int handle_map(t_args *args, char **map, int nbr_lines);

// Free
void free_file(char **file, int nbr_lines);
void free_on_error(t_args *args, int num);
void free_all(t_args *args);
void free_split(char **split);

#endif
