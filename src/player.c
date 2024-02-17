#include "../headers/maze.h"

/**
 * setupPlayer - set up player
 * @player: player structure
 */
void setupPlayer(Player *player)
{
	player->pos.x = 16;
	player->pos.y = 16;
	player->angle = 30.0;
}

/**
 * updatePlayer - update player direction
 * @player: player structure
 */
void updatePlayer(Player *player)
{
	float angle = player->angle;

	if (angle >= 0 && angle <= 90)
	{
		player->dir.x = (angle == 90) ? 0 : 1;
		player->dir.y = (angle == 0) ? 0 : 1;
	}
	else if (angle > 90 && angle <= 180)
	{
		player->dir.x = -1;
		player->dir.y = (angle == 180) ? 0 : 1;
	}
	else if (angle > 180 && angle <= 270)
	{
		player->dir.x = (angle == 270) ? 0 : -1;
		player->dir.y = -1;
	}
	else if (angle > 270 && angle < 360)
	{
		player->dir.x = 1;
		player->dir.y = -1;
	}

	player->mX = _absf(tan(angle * (M_PI / 180)));
	player->mY = 1 / player->mX;
	if (angle == 90 || angle == 270)
		player->mY = 0;
}

/**
 * move_player - move player
 * @e: SDL_Event structure
 * @player: player structure
 */
void move_player(SDL_Event e, Player *player)
{
	float angle;
	const float speed = 0.125;
	int dy;
	int k;
	SDL_Point dir = {0, 0};

	updatePlayer(player);
	dy = CC * speed;
	k = CC * speed;
	angle = player->angle;

	if (e.type == SDL_KEYDOWN)
	{
		// player movement
		if (e.key.keysym.sym == SDLK_w)
		{
			player->pos.y += dy * player->dir.y;
			player->pos.x += dy * player->mY * player->dir.x;
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			player->pos.y += dy * invert(player->dir.y);
			player->pos.x += dy * player->mY * invert(player->dir.x);
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			angle += 90;
			if (angle > 360)
				angle -= 360;
			dir = getDir(angle);
			player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
			player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
		}
		if (e.key.keysym.sym == SDLK_d)
		{
			angle -= 90;
			if (angle < 0)
				angle += 360;
			dir = getDir(angle);
			player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
			player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
		}
	}
}

/**
 * moveCamera - move camera
 * @e: SDL_Event structure
 * @player: player structure
 */
void moveCamera(SDL_Event e, Player *player)
{
	updatePlayer(player);

	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_LEFT)
		{
			player->angle -= 2;
			if (player->angle < 0)
				player->angle = 358;
		}
		else if (e.key.keysym.sym == SDLK_RIGHT)
		{
			player->angle += 2;
			if (player->angle > 358)
				player->angle = 0;
		}
	}
}