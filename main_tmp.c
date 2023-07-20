#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  t_map map;

  check_args(argc, argv);
  if (check_valid_map(argv[1]))
    ;
  return (0);
  map = create_map_data(argv[1]);

  printf("args->north_texture: [%s]\n", args->north_texture);
  printf("args->south_texture: [%s]\n", args->south_texture);
  printf("args->west_texture: [%s]\n", args->west_texture);
  printf("args->east_texture: [%s]\n", args->east_texture);
  printf("args->floor_color: [%d]\n", args->floor_color);
  printf("args->ceiling_color: [%d]\n", args->ceiling_color);
  printf("args->map_height: [%zu]\n", args->map_height);
  printf("args->map_width: [%zu]\n", args->map_width);
  size_t i = 0;
  while (i < args->map_height) {
    printf("map line[%zu]: [%s]\n", i, args->map[i]);
    i++;
  }

  free_all(args);
  free(args);
  return (0);
}
