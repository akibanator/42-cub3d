// #include "cub3d.h"
// #include <math.h>
// #include <stdio.h>

// void raycast(t_data *data, t_player *player)
// {
// 	int		 x;
// 	double	 cameraX;
// 	t_vector rayDir;
//
// 	x = 0;
// 	while (x < WINDOW_WIDTH)
// 	{
// 		cameraX = (double) (2 * x) / WINDOW_WIDTH - 1;
// 		rayDir.x = player->dir.x + player->plane.x * cameraX;
// 		rayDir.y = player->dir.y + player->plane.y * cameraX;
// 		int mapX;
// 		int mapY;
// 		mapX = floor(player->pos.x);
// 		mapY = floor(player->pos.y);
// 		// length of ray from current position to next x or y-side
// 		t_vector sideDist;
//
// 		// length of ray from one x or y-side to next x or y-side
// 		double deltaDistX;
// 		if (rayDir.x == 0)
// 			deltaDistX = DBL_MAX;
// 		else
// 			deltaDistX = fabs(1 / rayDir.x);
// 		double deltaDistY;
// 		if (rayDir.y == 0)
// 			deltaDistY = DBL_MAX;
// 		else
// 			deltaDistY = fabs(1 / rayDir.y);
// 		double perpWallDist;
//
// 		int stepX;
// 		int stepY;
//
// 		int hit = 0; // was there a wall hit?
// 		int side;	 // was a NS or a EW wall hit?
//
// 		// calculate step and initial sideDist
// 		if (rayDir.x < 0)
// 		{
// 			stepX = -1;
// 			sideDist.x = (player->pos.x - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDist.x = (mapX + 1 - player->pos.x) * deltaDistX;
// 		}
// 		if (rayDir.y < 0)
// 		{
// 			stepY = -1;
// 			sideDist.y = (player->pos.y - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDist.y = (mapY + 1 - player->pos.y) * deltaDistY;
// 		}
//
// 		while (hit == 0)
// 		{
// 			if (sideDist.x < sideDist.y)
// 			{
// 				sideDist.x += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDist.y += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			// Check if ray has hit a wall
// 			if (map[mapX][mapY] > '0')
// 				hit = 1;
// 		}
//
// 		if (side == 0)
// 			perpWallDist = (sideDist.x - deltaDistX);
// 		else
// 			perpWallDist = (sideDist.y - deltaDistY);
//
// 		int lineHeight = (int) (WINDOW_HEIGHT / perpWallDist);
//
// 		int drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		int drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
// 		if (drawEnd >= WINDOW_HEIGHT)
// 			drawEnd = WINDOW_HEIGHT - 1;
//
// 		int wallColor;
// 		wallColor = 0xFF0000;
// 		if (side == 1)
// 			wallColor = 0xBB0000;
// 		render_wall_line(data->canvas, x, drawStart, lineHeight, wallColor);
// 		x++;
// 	}
// }
