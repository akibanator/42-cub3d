#include "cub3d.h"

void	exit_game(t_data *data)
{
	mlx_clear_window(data->mlx, data->window);
	mlx_loop_end(data->mlx);
	mlx_destroy_window(data->mlx, data->window);
	mlx_destroy_image(data->mlx, data->canvas->mlx_img);
	free(data->canvas);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
	exit(0);
}
