#include "cub3d.h"

t_args *init_struct(void) {
  t_args *args;

  args = malloc(sizeof(t_args));
  if (args == NULL)
    return (NULL);
  args->north_texture = NULL;
  args->south_texture = NULL;
  args->west_texture = NULL;
  args->east_texture = NULL;
  args->player_direction = 0;
  args->player_position = NULL;
  args->map_height = 0;
  args->map_width = 0;
  args->floor_color = 0;
  args->ceiling_color = 0;
  args->map = NULL;
  return (args);
}
