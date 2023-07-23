#ifndef CONSTANTS_H
#define CONSTANTS_H

#define PI 3.14159265
#define TWO_PI 6.28318530

#define GAME_WIDTH 320
#define GAME_HEIGHT 200
#define TILE_SIZE 64
#define FOV_ANGLE (60 * (PI / 180))
#define NUM_RAYS GAME_WIDTH

#define UPSCALE 4

#define WINDOW_WIDTH (GAME_WIDTH * UPSCALE)
#define WINDOW_HEIGHT (GAME_HEIGHT * UPSCALE)

// Player
#define WALK_SPEED 2
#define TURN_SPEED 0.02
#define SENSIBILITY 0.00003
#define MOUSE_DEADZONE 200

#endif
