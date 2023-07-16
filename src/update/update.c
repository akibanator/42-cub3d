#include "cub3d.h"

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
	update_player(data);
	render_canvas(data);
	return (0);
}

// TODO: Pass map as a parameter to check collisions
void update_player(t_data *data)
{
	t_player *player;
	double	  move_step;
	t_vector  new_pos;

	player = data->player;
	player->rotation_angle += player->rotation_input * player->turn_speed;
	move_step = player->walk_direction * player->walk_speed;
	new_pos.x = player->pos.x + cos(player->rotation_angle) * move_step;
	new_pos.y = player->pos.y + sin(player->rotation_angle) * move_step;
	if (map_has_wall_at(new_pos))
		return;
	player->pos.x = new_pos.x;
	player->pos.y = new_pos.y;
}
