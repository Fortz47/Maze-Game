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