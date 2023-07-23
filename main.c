#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  t_map map;
  void *mlx;

  if (check_args(argc, argv) || check_map(argv[1])) {
    printf("Error\n");
    return (0);
  }
  mlx = mlx_init();
  map = create_data(argv[1], mlx);
  if (check_valid_grid(map.grid, map.size)) {
    printf("Error\n");
    return (0);
  }
  mlx_destroy_display(mlx);
  free(mlx);
  free_split(map.grid);
  return (0);
}
