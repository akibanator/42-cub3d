#include "cub3d.h"
#include "mlx.h"

int update(void *data)
{
	update_player(data);
	render_canvas(data);
	return (0);
}
