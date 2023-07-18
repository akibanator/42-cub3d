#include "cub3d.h"

static void free_omap(t_args *args) {
  size_t i;
  char **omap;

  i = 0;
  omap = args->map;
  while (i < args->map_height) {
    free(omap[i]);
    i++;
  }
  free(omap);
}

void free_all(t_args *args) {
  free(args->north_texture);
  free(args->south_texture);
  free(args->west_texture);
  free(args->east_texture);
  free_omap(args);
}

void free_file(char **file, int nbr_lines) {
  while (nbr_lines--) {
    free(*file);
    file++;
  }
}

void free_on_error(t_args *args, int num) {
  if (num > 0)
    free(args->north_texture);
  if (num > 1)
    free(args->south_texture);
  if (num > 2)
    free(args->west_texture);
  if (num > 3)
    free(args->east_texture);
}

void free_split(char **split) {
  int i;

  i = 0;
  while (split[i]) {
    free(split[i]);
    i++;
  }
  free(split);
}
