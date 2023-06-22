#include "cub3d.h"
#include "mlx.h"

int main(void) {
  void *mlx;
  void *mlx_win;

  mlx = mlx_init();
  mlx_win = mlx_new_window(mlx, 320, 240, "Cub3d");
  (void)mlx_win;
  mlx_loop(mlx);
  return (0);
}
