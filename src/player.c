#include "../headers/maze.h"

/**
 * setupPlayer - set up player
 * @player: player structure
 */
void setupPlayer(Player *player)
{
	player->pos.x = 70;
	player->pos.y = 70;
	player->angle = 0.0;
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
	else if (angle > 270 && angle <= 360)
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
 * movePlayer - move player
 * @e: SDL_Event structure
 * @player: player structure
 */
void movePlayer(SDL_Event e, Player *player)
{
	float angle;
	int dy, k, x = 0, y = 0;
	SDL_Point dir = {0, 0};
	const Uint8 *state = SDL_GetKeyboardState(NULL);

	updatePlayer(player);
	dy = CC * speed;
	k = CC * speed;
	angle = player->angle;
	dir.x = player->dir.x;
	dir.y = player->dir.y;

	if (state[SDL_SCANCODE_W])
	{
		y = player->pos.y;
		x = player->pos.x;
		player->pos.y += (k * _absf(sin(rad(angle))) * dir.y);
		player->pos.x += (k * _absf(cos(rad(angle))) * dir.x);
		if (HitWall(player->pos.x, player->pos.y, dir, map))
		{
			player->pos.y = y;
			player->pos.x = x;
		}
	}
	else if (state[SDL_SCANCODE_S])
	{
		y = player->pos.y;
		x = player->pos.x;
		player->pos.y += (k * _absf(sin(rad(angle))) * invert(dir.y));
		player->pos.x += (k * _absf(cos(rad(angle))) * invert(dir.x));
		if (HitWall(player->pos.x, player->pos.y, dir, map))
		{
			player->pos.y = y;
			player->pos.x = x;
		}
	}
	else if (state[SDL_SCANCODE_D])
	{
		angle += 90;
		if (angle > 360)
			angle -= 360;
		dir = getDir(angle);
		y = player->pos.y;
		x = player->pos.x;
		player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
		player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
		if (HitWall(player->pos.x, player->pos.y, dir, map))
		{
			player->pos.y = y;
			player->pos.x = x;
		}
	}
	else if (state[SDL_SCANCODE_A])
	{
		angle -= 90;
		if (angle < 0)
			angle += 360;
		dir = getDir(angle);
		y = player->pos.y;
		x = player->pos.x;
		player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
		player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
		if (HitWall(player->pos.x, player->pos.y, dir, map))
		{
			player->pos.y = y;
			player->pos.x = x;
		}
	}

	/**
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			y = player->pos.y;
			x = player->pos.x;
			player->pos.y += (k * _absf(sin(rad(angle)))) * dir.y;
			player->pos.x += (k * _absf(cos(rad(angle)))) * dir.x;
			if (HitWall(player->pos.x, player->pos.y, dir, map))
			{
				player->pos.y = y;
				player->pos.x = x;
			}
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			y = player->pos.y;
			x = player->pos.x;
			player->pos.y += (k * _absf(sin(rad(angle)))) * invert(dir.y);
			player->pos.x += (k * _absf(cos(rad(angle)))) * invert(dir.x);
			if (HitWall(player->pos.x, player->pos.y, dir, map))
			{
				player->pos.y = y;
				player->pos.x = x;
			}
		}
		if (e.key.keysym.sym == SDLK_d)
		{
			angle += 90;
			if (angle > 360)
				angle -= 360;
			dir = getDir(angle);
			y = player->pos.y;
			x = player->pos.x;
			player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
			player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
			if (HitWall(player->pos.x, player->pos.y, dir, map))
			{
				player->pos.y = y;
				player->pos.x = x;
			}
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			angle -= 90;
			if (angle < 0)
				angle += 360;
			dir = getDir(angle);
			y = player->pos.y;
			x = player->pos.x;
			player->pos.x += (_absf(cos(rad(angle))) * k) * dir.x;
			player->pos.y += (_absf(sin(rad(angle))) * k) * dir.y;
			if (HitWall(player->pos.x, player->pos.y, dir, map))
			{
				player->pos.y = y;
				player->pos.x = x;
			}
		}
	}
	**/
}

/**
 * moveCamera - move camera
 * @e: SDL_Event structure
 * @player: player structure
 */
void moveCamera(SDL_Event e, Player *player)
{
	const Uint8 *state = SDL_GetKeyboardState(NULL);
	updatePlayer(player);

	if (state[SDL_SCANCODE_LEFT])
	{
		player->angle -= 5;
		if (player->angle < 0)
			player->angle = 355;
	}
	else if (state[SDL_SCANCODE_RIGHT])
	{
		player->angle += 5;
		if (player->angle > 355)
			player->angle = 0;
	}

	/**
	if (e.key.keysym.sym == SDLK_LEFT)
	{
		movePlayer(e, player);
		player->angle -= 5;
		if (player->angle < 0)
			player->angle = 355;
	}
	else if (e.key.keysym.sym == SDLK_RIGHT)
	{
		movePlayer(e, player);
		player->angle += 5;
		if (player->angle > 355)
			player->angle = 0;
	}
	**/
}

/**
 * moveCameraAndPlayer - move camera and player
 * @e: SDL_Event structure
 * @player: player structure
 */
void moveCameraAndPlayer(SDL_Event e, Player *player)
{
	movePlayer(e, player);
	moveCamera(e, player);
}