#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // void *mlx;
  // void *mlx_win;
  //
  // mlx = mlx_init();
  // mlx_win = mlx_new_window(mlx, 320, 240, "Cub3d");
  // (void)mlx_win;
  // mlx_loop(mlx);
  t_args *args;

  argc = 2;
  *argv = "map/simple.cub";
  check_args(argc, argv);
  args = init_struct();
  if (args == NULL)
    return (0);
  if (create_map_data(argv[1], args)) {
    free(args);
    printf("Program will be closed\n");
    return (0);
  }

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
