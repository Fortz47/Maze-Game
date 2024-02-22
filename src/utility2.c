#include "../headers/maze.h"


/**
 * rad - converts degree to radians
 * angle: angle in degrees
 * return: radians
*/
float rad(float angle)
{
	float rad = 0.0;

	rad = angle * (M_PI / 180);
	return (rad);
}

/**
 * get_Offset - get offset
 * @ray: singleRay structure
 * @x1: x-coordinate
 * @y1: y-coordinate
 * 
 * Return: SDL_Point structure
*/
SDL_Point get_Offset(singleRay ray, int x1, int y1)
{
	SDL_Point offset = {0, 0};

	if (ray.dir.x > 0)
		offset.x = (x1 % CC == 0) ? CC : CC - (x1 % CC);
	else
		offset.x = (x1 % CC == 0) ? CC : x1 % CC;

	if (ray.dir.y > 0)
		offset.y = (y1 % CC == 0) ? CC : CC - (y1 % CC);
	else
		offset.y = (y1 % CC == 0) ? CC : y1 % CC;

	return (offset);
}

double cal_hyp(int dis, float slope)
{
	double opp;
	double adj;
	double res = 0.0;

	opp = (double)(dis * slope);
	adj = (double)dis;

	res = sqrt((opp * opp) + (adj * adj));
	return (res);
}