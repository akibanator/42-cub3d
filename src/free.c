#include "cub3d.h"

void free_all(t_args *args) {
  free(args->north_texture);
  free(args->south_texture);
  free(args->west_texture);
  free(args->east_texture);
}
