#include "../headers/maze.h"
#include <limits.h>

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

	for (i = 0; i <= NUM_RAYS; i++)
	{
		angle = player.angle - 30 + (FOV * i);
		if (angle < 0)
			angle += 360;
		else if (angle > 360)
			angle -= 360;
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
		else if (angle > 270 && angle <= 360)
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
			kx = 1e30;
			ky = 0.0;
			mY = 0;
		}
		else if (angle == 0 || angle == 180)
		{
			ky = 1e30;
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
		if (x1 % CC == 0)
			cx = CC;
		else
			cx = (dirX > 0) ? CC - (x1 % CC) : x1 % CC;
		/* initial distance to vertical grid*/
		if (y1 % CC == 0)
			cy = CC;
		else
			cy = (dirY > 0) ? CC - (y1 % CC) : y1 % CC;
		while (true)
		{
			/* displacement along x-axis */
			if (kx <= ky && inMapX && wallHitX == false && !(angle == 90 || angle == 270))
			{
				dx += cx;
				cx = CC;
				x2 = x1 + dx * dirX;
				y2 = (mX * dx) * dirY + y1;
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
							break;
						}
					}
				}
				else
				{
					inMapX = false;
					kx = 1e30; /* out of bounds */
				}
			}
			else if (ky <= kx && inMapY && wallHitY == false && !(angle == 180 || angle == 0))
			{
				/* displacement along y-axis */
				dy += cy;
				cy = CC;
				y2 = y1 + dy * dirY;
				x2 = (dy * mY) * dirX + x1;
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
							break;
						}
					}
				}
				else
				{
					inMapY = false;
					ky = 1e30; /* out of bounds */
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
			rays[i].color = (kx < ky) ? 128 : 211;
		}
		SDL_RenderDrawLine(instance.renderer, rays[i].start.x, rays[i].start.y, rays[i].end.x, rays[i].end.y);
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
		rays[i].correctedlength = rays[i].actualLength * cos(rad(angle));
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

	SDL_SetRenderDrawColor(instance.renderer, 135, 206, 235, 255);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		dy = rays[i].ds_to_proj_wall_top;
		SDL_RenderDrawLine(instance.renderer, i, dy, i, 0);
	}
}


/**
 * setupRay - setup ray
 * @angle: angle of ray
 * 
 * Return: singleRay structure
*/
singleRay setupRay(float angle)
{
	singleRay ray;
	
	
	if (angle < 0)
		angle += 360;
	else if (angle > 360)
		angle -= 360;
	
	ray.angle = angle;
	ray.dir = getDir(angle);

	return (ray);
}


/**
 * cast_rays - cast rays in map
 * @instance: SDL_Instance structure
 * @player: player structure
 * @rays: array of rays
 * @map: 2D array of map
 * 
*/

/***
void cast_rays(SDL_Instance instance, Player player, Ray *rays, const int map[mapH][mapW])
{
	singleRay ray;
	float angle = 0.0;
	int i;
	SDL_Point offset = {0, 0};
	int x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	float mX = 0.0, mY = 0.0;
	double rayDist_x = 0.0;
	double rayDist_y = 0.0;
	bool wallHit = false;
	int side;

	for (i = 0; i <= NUM_RAYS; i++)
	{
		angle = player.angle - 33 + (FOV * i);
		ray = setupRay(angle);
		rays[i].start.x = player.pos.x;
		rays[i].start.y = player.pos.y;
		rays[i].angle = ray.angle;
		x1 = rays[i].start.x;
		y1 = rays[i].start.y;
		offset = get_Offset(ray, x1, y1);
		mX = _absf(tan(rad(ray.angle)));
		mY = 1 / mX;
		rayDist_x = (angle == 90) ? 1e30 : cal_hyp(offset.x, mX);
		rayDist_y = (angle == 0) ? 1e30 : cal_hyp(offset.y, mY);
		wallHit = false;
		while (wallHit == false)
		{
			// displacement along x-axis
			if (rayDist_x < rayDist_y)
			{
				x2 = x1 + (offset.x * ray.dir.x);
				y2 = y1 + (mX * offset.x * ray.dir.y);
				offset.x += CC;
				if (isWall(x2, y2, ray, map))
				{
					wallHit = true;
					side = 0;
					rays[i].actualLength = rayDist_x;
				}
				rayDist_x = cal_hyp(offset.x, mX);
			}
			else
			{
				// displacement along y-axis
				x2 = x1 + (mY * offset.y * ray.dir.x);
				y2 = y1 + (offset.y * ray.dir.y);
				offset.y += CC;
				if (isWall(x2, y2, ray, map))
				{
					wallHit = true;
					side = 1;
					rays[i].actualLength = rayDist_y;
				}
				rayDist_y = cal_hyp(offset.y, mY);
			}
		}

		rays[i].end.x = x2;
		rays[i].end.y = y2;
		rays[i].color = (side == 0) ? 128 : 211;
		SDL_RenderDrawLine(instance.renderer, rays[i].start.x, rays[i].start.y, rays[i].end.x, rays[i].end.y);
	}
}

***/