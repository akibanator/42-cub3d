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
  char *player_direction;
  char *player_position;
  int floor_color;
  int ceiling_color;
  char **map;
} t_args;

void check_args(int argc, char *argv[]);
int create_map_data(char *map, t_args *args);
int check_valid_ext(char *map, char *ext);
void free_all(t_args *args);

#endif
