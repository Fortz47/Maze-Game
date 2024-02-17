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