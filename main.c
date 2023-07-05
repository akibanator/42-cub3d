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

  check_args(argc, argv);
  args = malloc(sizeof(t_args));
  if (create_map_data(argv[1], args)) {
    free(args);
    printf("Program will be closed\n");
    return (0);
  }

  printf("%s\n", args->north_texture);
  printf("%s\n", args->south_texture);
  printf("%s\n", args->west_texture);
  printf("%s\n", args->east_texture);
  free_all(args);
  free(args);
  return (0);
}
