#include "../headers/maze.h"

/**
 * mapTextureToWall - map texture to wall
 * @instance: SDL_Instance structure
 * @rays: array of rays
 * @texture: texture structure
*/
void mapTextureToWall(SDL_Instance instance, Ray *rays, Texture *texture)
{
	SDL_Rect dst = {0, 0, 1, 1};
	SDL_Rect txt = {0, 0, 1, CC};
	textureMap txtMap;

	SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(texture->texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(texture->texture, 200);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		txtMap = getTextureMapping(rays[i]);
		txt.x = txtMap.pos.x;
		dst.x = i;
		dst.y = rays[i].ds_to_proj_wall_top;
		dst.h = rays[i].ds_to_proj_wall_bottom - rays[i].ds_to_proj_wall_top;
		SDL_RenderCopy(instance.renderer, texture->texture, &txt, &dst);
	}
}

/**
 * mapTextureToFloor - map texture to floor
 * @instance: SDL_Instance structure
 * @rays: array of rays
 * @texture: texture structure
*/
void mapTextureToFloor(SDL_Instance instance, Ray *rays, Texture *texture)
{
	SDL_Rect dst = {0, 0, 1, 1};
	SDL_Rect txt = {0, 0, 1, CC};
	textureMap txtMap;

	SDL_SetTextureBlendMode(texture->texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureColorMod(texture->texture, 255, 255, 255);
	SDL_SetTextureAlphaMod(texture->texture, 200);
	for (int i = 0; i < NUM_RAYS; i++)
	{
		txtMap = getTextureMapping(rays[i]);
		txt.x = txtMap.pos.x;
		dst.x = i;
		dst.y = rays[i].ds_to_proj_wall_bottom;
		dst.h = SCREEN_HEIGHT - rays[i].ds_to_proj_wall_bottom;
		SDL_RenderCopy(instance.renderer, texture->texture, &txt, &dst);
	}
}