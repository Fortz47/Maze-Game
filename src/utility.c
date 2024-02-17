#include "../headers/maze.h"

/**
 * cal_R - calculate the distance between two points
 * @x1: x coordinate of first point
 * @x2: x coordinate of second point
 * @y1: y coordinate of first point
 * @y2: y coordinate of second point
 * Return: distance between two points
*/
double cal_R(int x1, int x2, int y1, int y2)
{
	int dx = x2 - x1;
	int dy = y1 - y2;
	double res = 0.0;

	int _pow = dx * dx + dy * dy;

	res = sqrt((double)_pow);
	return (res);
}

/**
 * _abs - return the absolute value of a number
 * @n: number to be checked
 * Return: absolute value of val
*/
int _abs(int n)
{
	int res = 0;

	res = (n < 0) ? n * -1 : n;
	return (res);
}

/**
 * _absf - return the absolute value of a float
 * @n: value to be checked
 * Return: absolute value of val
*/
float _absf(float n)
{
	float res = 0;

	res = (n < 0) ? n * -1 : n;
	return (res);
}

/**
 * invert - invert sign of a value
 * @n: value to be inverted
 * Return: inverted value
*/
int invert(int n)
{
	if (n == 1)
		n = -1;
	else if (n == -1)
		n = 1;
	else
		n = 0;
	return (n);
}

/**
 * getDir - get direction based on an angle
 * @angle: angle
 * Return: direction
 */
SDL_Point getDir(float angle)
{
	SDL_Point dir;

	if (angle >= 0 && angle <= 90)
	{
		dir.x = (angle == 90) ? 0 : 1;
		dir.y = (angle == 0) ? 0 : 1;
	}
	else if (angle > 90 && angle <= 180)
	{
		dir.x = -1;
		dir.y = (angle == 180) ? 0 : 1;
	}
	else if (angle > 180 && angle <= 270)
	{
		dir.x = (angle == 270) ? 0 : -1;
		dir.y = -1;
	}
	else if (angle > 270 && angle < 360)
	{
		dir.x = 1;
		dir.y = -1;
	}

	return dir;
}