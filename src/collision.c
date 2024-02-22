#include "../headers/maze.h"

/**
 * collision - check for collision
 * @player: player structure
 */
void collision(Player *player)
{
	updatePlayer(player);
	if (player->pos.x <= CC)
		player->pos.x += CC;
	else if (player->pos.x >= (mapW - 1) * CC)
		player->pos.x -= CC;
	if (player->pos.y <= CC)
		player->pos.y += CC;
	else if (player->pos.y >= (mapH - 1) * CC)
		player->pos.y -= CC;

}

/**
 * isWall - check if wall
 * @x: x-coordinate
 * @y: y-coordinate
 * @dir: direction of ray
 * @map: 2D array of map
 * 
 * Return: true if wall, false otherwise
*/
bool isWall(int x, int y, SDL_Point dir, const int map[mapH][mapW])
{
	int wall_x = 0;
	int wall_y = 0;

	wall_x = (dir.x < 0) ? (x / CC) - 1 : x / CC;
	wall_y = (dir.y < 0) ? (y / CC) - 1 : y / CC;
	if (x > 0 && x < mapW * CC && y > 0 && y < mapH * CC)
	{
		if (map[wall_y][wall_x] != 0)
			return (true);
	}
	return (false);
}

/**
 * HitWall - check if player hit wall
 * @x: x-coordinate
 * @y: y-coordinate
 * @dir: direction of the player
 * @map: 2D array of map
 * 
 * Return: value greater than 0 if hit wall, 0 otherwise
*/
int HitWall(int x, int y, SDL_Point dir, const int map[mapH][mapW])
{
	int wall_x = 0;
	int wall_y = 0;
	int step = CC * speed;
	int upperX = (mapW * CC) - CC + step;
	int upperY = (mapH * CC) - CC + step;

	wall_x = x / CC;
	wall_y = y / CC;
	step += CC;
	if (x >= step && x <= upperX && y >= step && y <= upperY)
	{
		if (map[wall_y][wall_x] > 0)
			return (map[wall_y][wall_x]);
	}
	return (map[wall_y][wall_x]);
}