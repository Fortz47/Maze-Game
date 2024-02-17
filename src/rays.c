#include "../headers/maze.h"

/**
 * cast_rays - cast rays in map
 * @instance: SDL_Instance structure
 * @player: player structure
 * @rays: array of rays
 * @map: 2D array of map
 * 
*/
void cast_rays(SDL_Instance instance, Player player, Ray *rays, const int map[mapH][mapW])
{
	float angle = 0.0;
	int dirX = 1, dirY = 1;
	float mX, mY;
	int x1, x2 = 0, y1, y2 = 0, i;
	int cx = 0, cy = 0;
	double kx, ky, k = 0;
	SDL_Point X_quad = {0, 0};
	SDL_Point Y_quad = {0, 0};
	SDL_Point end = {0, 0};

	for (i = 0; i < NUM_RAYS; i++)
	{
		angle = player.angle - 33 + (FOV * i);
		if (angle < 0)
			angle += 360;
		rays[i].angle = angle;
		rays[i].start.x = player.pos.x;
		rays[i].start.y = player.pos.y;
		if (angle >= 0 && angle <= 90)
		{
			dirX = (angle == 90) ? 0 : 1;
			dirY = (angle == 0) ? 0 : 1;
		}
		else if (angle > 90 && angle <= 180)
		{
			dirX = -1;
			dirY = (angle == 180) ? 0 : 1;
		}
		else if (angle > 180 && angle <= 270)
		{
			dirX = (angle == 270) ? 0 : -1;
			dirY = -1;
		}
		else if (angle > 270 && angle < 360)
		{
			dirX = 1;
			dirY = -1;
		}
		x1 = rays[i].start.x;
		y1 = rays[i].start.y;
		mX = _absf(tan(angle * (M_PI / 180)));
		mY = 1 / mX;
		if (angle == 90 || angle == 270)
		{
			kx = INFINITY;
			ky = 0.0;
			mY = 0;
		}
		else if (angle == 0 || angle == 180)
		{
			ky = INFINITY;
			kx = 0.0;
		}
		else
		{
			kx = 0.0;
			ky = 1.0;
		}
		int dx = 0;
		int dy = 0;
		bool wallHitX = false;
		bool wallHitY = false;
		bool inMapX = true;
		bool inMapY = true;
		int px = 0, py = 0;
		/* initial distance to horizontal grid*/
		cx = (x1 % CC == 0) ? CC : (CC - (x1 % CC));
		/* initial distance to vertical grid*/
		cy = (y1 % CC == 0) ? CC : (CC - (y1 % CC));
		while (true)
		{
			/* displacement along x-axis */
			if (kx <= ky && inMapX && wallHitX == false && !(angle == 90 || angle == 270))
			{
				dx += cx * dirX;
				cx = CC;
				x2 = x1 + dx;
				y2 = (mX * _abs(dx)) * dirY + y1;
				kx = cal_R(x1, x2, y1, y2);
				if (x2 > 0 && x2 < mapW * CC && y2 > 0 && y2 < mapH * CC)
				{
					px = (angle > 90 && angle < 270) ? (x2 / CC) - 1 : x2 / CC;
					if (map[y2 / CC][px])
					{
						wallHitX = true;
						X_quad.x = x2;
						X_quad.y = y2;
						if (wallHitY)
						{
							end.x = (kx < ky) ? X_quad.x : Y_quad.x;
							end.y = (kx < ky) ? X_quad.y : Y_quad.y;
							k = (kx < ky) ? kx : ky;
							rays[i].color = (kx < ky) ? 128 : 211;
							break;
						}
					}
				}
				else
				{
					inMapX = false;
					kx = INFINITY; /* out of bounds */
				}
			}
			else if (ky <= kx && inMapY && wallHitY == false && !(angle == 180 || angle == 0))
			{
				/* displacement along y-axis */
				dy += cy * dirY;
				cy = CC;
				y2 = y1 + dy;
				x2 = (_abs(dy) * mY) * dirX + x1;
				ky = cal_R(x1, x2, y1, y2);
				if (y2 > 0 && y2 < mapH * CC && x2 > 0 && x2 < mapW * CC)
				{
					py = (angle > 180 && angle < 360) ? (y2 / CC) - 1 : y2 / CC;
					if (map[py][x2 / CC])
					{
						Y_quad.x = x2;
						Y_quad.y = y2;
						wallHitY = true;
						if (wallHitX)
						{
							end.x = (kx < ky) ? X_quad.x : Y_quad.x;
							end.y = (kx < ky) ? X_quad.y : Y_quad.y;
							k = (kx < ky) ? kx : ky;
							rays[i].color = (kx < ky) ? 128 : 211;
							break;
						}
					}
				}
				else
				{
					inMapY = false;
					ky = INFINITY; /* out of bounds */
				}
			}
			else
				break;
		}

		if (wallHitX && !wallHitY)
		{
			rays[i].end.x = X_quad.x;
			rays[i].end.y = X_quad.y;
			rays[i].actualLength = kx;
			rays[i].color = 128;
		}
		else if (wallHitY && !wallHitX)
		{
			rays[i].end.x = Y_quad.x;
			rays[i].end.y = Y_quad.y;
			rays[i].actualLength = ky;
			rays[i].color = 211;
		}
		else
		{
			rays[i].end.x = end.x;
			rays[i].end.y = end.y;
			rays[i].actualLength = k;
		}

		// SDL_SetRenderDrawColor(instance.renderer, 255, 225, 255, 255);
		SDL_RenderDrawLine(instance.renderer, rays[i].start.x, rays[i].start.y, rays[i].end.x, rays[i].end.y);
		// SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
		// SDL_SetRenderDrawColor(instance.renderer, 255, 0, 0, 80);
		// SDL_RenderDrawLine(instance.renderer, i * CC, 0, CC * i, mapH * CC);
		// SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
		// SDL_SetRenderDrawColor(instance.renderer, 0, 255, 0, 80);
		// SDL_RenderDrawLine(instance.renderer, 0, i * CC, CC * mapW, CC * i);
	}
}

/**
 * trace_ray - trace rays on projection plane then draw walls
 * @instance: SDL_Instance structure
 * @rays: array of rays
 * @player: player structure
*/
void castWall(SDL_Instance *instance, Ray *rays, Player player)
{
	float ds_to_plane = Player_2_ProjP;
	float ds_to_wall = 0;
	float proj_wall_h = 0;
	float angle = 0.0;
	int wallTop = 0;
	int v = 0;

	for (int i = 0; i < NUM_RAYS; i++)
	{
		angle = rays[i].angle;
		angle = _absf(angle - player.angle);
		rays[i].correctedlength = rays[i].actualLength * cos(angle * (M_PI / 180));
		ds_to_wall = rays[i].correctedlength;
		proj_wall_h = (wH / ds_to_wall) * ds_to_plane;
		wallTop = (SCREEN_HEIGHT - proj_wall_h) / 2;
		rays[i].ds_to_proj_wall_top = wallTop;
		rays[i].ds_to_proj_wall_bottom = wallTop + proj_wall_h;

		v = rays[i].color;

		SDL_SetRenderDrawColor(instance->renderer, v, v, v, 255);
		SDL_RenderDrawLine(instance->renderer, i, wallTop, i, wallTop + proj_wall_h);
	}
}

/**
 * castFloor - cast floor
 * @instance: SDL_Instance structure
 * @rays: array of rays
*/
void castFloor(SDL_Instance instance, Ray *rays)
{
	float dy = 0;

	SDL_SetRenderDrawColor(instance.renderer, 0, 255, 0, 255);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		dy = rays[i].ds_to_proj_wall_bottom;
		SDL_RenderDrawLine(instance.renderer, i, dy, i, SCREEN_HEIGHT);
	}
}

/**
 * castCeiling - cast ceiling
 * @instance: SDL_Instance structure
 * @rays: array of rays
*/
void castCeiling(SDL_Instance instance, Ray *rays)
{
	float dy = 0;

	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 255, 255);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		dy = rays[i].ds_to_proj_wall_top;
		SDL_RenderDrawLine(instance.renderer, i, dy, i, 0);
	}
}