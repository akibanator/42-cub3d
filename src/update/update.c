#include "cub3d.h"
#include "mlx.h"

#define MAP_WIDTH 12
#define MAP_HEIGHT 24

char improvised_map[MAP_HEIGHT][MAP_WIDTH] = {{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '1', '1', '1', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'}, {'1', '1', '0', '0', '0', '0', '1', '0', '1', '0', '0', '1'}, {'1', '1', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'}, {'1', '1', '0', '1', '1', '1', '1', '1', '1', '0', '0', '1'}, {'1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '1'}, {'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}};

static int map_has_wall_at(t_vector point)
{
	int grid_x;
	int grid_y;

	grid_x = (int) floor(point.x / TILE_SIZE);
	grid_y = (int) floor(point.y / TILE_SIZE);
	if (improvised_map[grid_y][grid_x] > '0')
		return (TRUE);
	return (FALSE);
}

int update(void *data)
{
	// update_mouse(data);
	update_player(data);
	render_canvas(data);
	return (0);
}

// TODO: Pass map as a parameter to check collisions
double get_move_angle(t_player *player)
{
	const t_vector dir = player->walk_direction;
	const double   angle = player->rotation_angle;

	if (dir.x > 0 && dir.y > 0)
		return (angle + (PI / 4));
	else if (dir.x < 0 && dir.y > 0)
		return (angle - (PI / 4));
	else if (dir.x > 0 && dir.y < 0)
		return (angle + (3 * PI / 4));
	else if (dir.x < 0 && dir.y < 0)
		return (angle - (3 * PI / 4));
	else if (dir.x > 0 && dir.y == 0)
		return (angle + (PI / 2));
	else if (dir.x < 0 && dir.y == 0)
		return (angle - (PI / 2));
	else if (dir.x == 0 && dir.y > 0)
		return (angle);
	else
		return (angle - PI);
}

// void update_mouse(t_data *data)
// {
// 	t_player *player;
// 	int		  x;
// 	int		  y;
// 	double	  sense;
// 	int		  deadzone;
//
// 	player = data->player;
// 	sense = 0.00001;
// 	deadzone = 2;
// 	mlx_mouse_get_pos(data->mlx, data->window, &x, &y);
// 	if (x > WINDOW_WIDTH / 2 + deadzone)
// 		player->mouse_rotation = (x - WINDOW_WIDTH / 2.0) * sense;
// 	else if (x < WINDOW_WIDTH / 2 - deadzone)
// 		player->mouse_rotation = (WINDOW_WIDTH / 2.0 - x) * -sense;
// 	mlx_mouse_move(data->mlx, data->window, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
// }

void update_player(t_data *data)
{
	t_player *player;
	t_vector  new_pos;
	double	  move_angle;

	player = data->player;
	player->rotation_angle += player->mouse_rotation;
	player->rotation_angle += player->rotation_input;
	move_angle = get_move_angle(player);
	new_pos.x = player->pos.x;
	new_pos.y = player->pos.y;
	if (player->walk_direction.x != 0 || player->walk_direction.y != 0)
	{
		new_pos.x += cos(move_angle) * player->walk_speed;
		new_pos.y += sin(move_angle) * player->walk_speed;
	}
	if (map_has_wall_at(new_pos))
		return;
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
}
