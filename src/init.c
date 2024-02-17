#include "../headers/maze.h"

/**
 * init_sdl - Initialize SDL
 * @instance: SDL_Instance structure
 * Return: 0 on success, 1 on failure
 */
int init_sdl(SDL_Instance *instance)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		printf("Failed to initialize SDL: %s\n", SDL_GetError());
		return 1;
	}

	instance->window = SDL_CreateWindow("SDL Demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (instance->window == NULL)
	{
		printf("Failed to create window: %s\n", SDL_GetError());
		return 1;
	}

	instance->renderer = SDL_CreateRenderer(instance->window, -1, SDL_RENDERER_ACCELERATED);
	if (instance->renderer == NULL)
	{
		printf("Failed to create renderer: %s\n", SDL_GetError());
		SDL_DestroyWindow(instance->window);
		return 1;
	}

	/* Initialize PNG loading */
	int Img_flags = IMG_INIT_PNG;
	if (!(IMG_Init(Img_flags) & IMG_INIT_PNG))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		SDL_DestroyRenderer(instance->renderer);
		SDL_DestroyWindow(instance->window);
		return 1;
	}

	return 0;
}