#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

int main(int argc, char *argv[]) {
  t_map map;
  void *mlx;
  size_t i;

  i = 0;
  if (check_args(argc, argv))
    return (0);
  if (check_map(argv[1]))
    return (0);
  mlx = mlx_init();
  map = create_data(argv[1], mlx);
  if (check_valid_grid(map.grid, map.size))
    return (0);
  printf("map.assets.floor_color: [%d]\n", map.assets.floor_color);
  printf("map.assets.ceiling_color: [%d]\n", map.assets.ceiling_color);
  printf("map.size.x: [%f]\n", map.size.x);
  printf("map.size.y: [%f]\n", map.size.y);
  printf("map.start_dir.x: [%f]\n", map.start_dir.x);
  printf("map.start_dir.y: [%f]\n", map.start_dir.y);
  printf("map.start_pos.x: [%f]\n", map.start_pos.x);
  printf("map.start_pos.y: [%f]\n", map.start_pos.y);
  printf("MAP: \n");
  while (map.grid[i] != NULL) {
    printf("%s\n", map.grid[i]);
    i++;
  }
  mlx_destroy_display(mlx);
  free(mlx);
  free_map(map.grid);
  return (0);
}
