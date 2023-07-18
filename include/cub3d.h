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
typedef struct s_args {
  char *north_texture;
  char *south_texture;
  char *west_texture;
  char *east_texture;
  char player_direction;
  char *player_position;
  size_t map_height;
  size_t map_width;
  int floor_color;
  int ceiling_color;
  char **map;
} t_args;

int create_map_data(char *map, t_args *args);
int check_valid_ext(char *map, char *ext);

// Init
t_args *init_struct(void);

// Parse
void check_args(int argc, char *argv[]);
int get_nbr_lines(char *map);
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
