#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  t_map map;
  void *mlx;

  (void)map;
  if (check_args(argc, argv))
    return (0);
  if (check_map(argv[1]))
    return (0);
  mlx = mlx_init();
  map = create_data(argv[1], mlx);
  mlx_destroy_display(mlx);
  free(mlx);
  free_map(map.grid);
  return (0);
}
