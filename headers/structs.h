#ifndef STRUCTS_H
#define STRUCTS_H
#include "../headers/maze.h"

enum texture
{
	WOOD,
	COLORSTONE,
	GREYSTONE,
	EAGLE,
	TOTAL,
};

/**
 * struct SDL_Instance - Struct for SDL window and renderer
 * @window: SDL window
 * @renderer: SDL renderer
*/
typedef struct SDL_Instance
{
	SDL_Window *window;
	SDL_Renderer *renderer;
} SDL_Instance;


/**
 * struct Player - Struct for player position and direction
 * @pos: player position
 * @dir: player direction
 * @angle: player angle
 * @mY: mouse Y
 * @mX: mouse X
*/
typedef struct Player
{
	SDL_Point pos;
	SDL_Point dir;
	float angle;
	float mY;
	float mX;
} Player;


/**
 * struct Ray - Struct for raycasting
 * @start: start point of ray
 * @end: end point of ray
 * @correctedlength: corrected length of ray
 * @actualLength: actual length of ray
 * @angle: angle of ray
 * @ds_to_wall: distance to wall
 * @ds_to_proj_wall_top: distance to projected wall top
 * @ds_to_proj_wall_bottom: distance to projected wall bottom
 * @ds_to_plane: distance to plane
 * @color: color of ray
 */
typedef struct Ray
{
	SDL_Point start;
	SDL_Point end;
	float correctedlength;
	float actualLength;
	float angle;
	float ds_to_wall;
	float ds_to_proj_wall_top;
	float ds_to_proj_wall_bottom;
	float ds_to_plane;
	int color;
	int side; /* 0 for x, 1 for y */
} Ray;

/**
 * struct Texture - Struct for texture
 * @texture: SDL texture
 * @w: width of texture
 * @h: height of texture
 */
typedef struct Texture
{
	SDL_Texture *texture;
	int w;
	int h;
} Texture;

/**
 * struct singleRay - Struct for raycasting
 * @radDir: ray direction
 * @angle: ray angle
 * @alpha: angle inclination to x-axis
 * @beta: angle inclination to y-axis
 */
typedef struct singleRay
{
	SDL_Point dir;
	float angle; /*ray angle*/
	float alpha; /*angle inclination to x-axis*/
	float beta; /*angle inclination to y-axis*/
} singleRay;

typedef struct textureMap
{
	SDL_Point pos; /* position of texture strip */
	int side; /* side of wall, 0 for x, 1 for y */
} textureMap;

#endif