#include "../headers/maze.h"


/**
 * LoadFromFile - Load image at specified path
 * @instance: SDL_Instance structure
 * @path: path to image
 * Return: Texture structure
*/
Texture loadTextureFromFile(SDL_Instance instance, const char *path)
{
	/* The final texture */
	Texture newTexture;

	/* Load image at specified path */
	SDL_Surface *loadedSurface = IMG_Load(path);
	if (loadedSurface == NULL)
		printf("Unable to load image %s! SDL_image Error: %s\n", path, IMG_GetError());
	else
	{
		/* Color key image
		SDL_SetColorkey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) ); */

		/* Create texture from surface pixels */
		newTexture.texture = SDL_CreateTextureFromSurface(instance.renderer, loadedSurface);
		if (newTexture.texture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path, SDL_GetError());
		}
		else
		{
			/* Get image dimensions */
			newTexture.w = loadedSurface->w;
			newTexture.h = loadedSurface->h;
		}

		/* Get rid of old loaded surface */
		SDL_FreeSurface(loadedSurface);
		loadedSurface = NULL;
	}

	return newTexture;
}

/**
 * loadTextures - load textures
 * @instance: SDL_Instance structure
 * @arr: array of paths to textures
 * Return: array of textures
*/
Texture *loadTextures(SDL_Instance instance, const char **arr)
{
	Texture *ptxt = malloc(sizeof(Texture) * TOTAL);

	for (int i = 0; i < TOTAL; i++)
	{
		ptxt[i] = loadTextureFromFile(instance, arr[i]);
	}
	return ptxt;
}

/**
 * Close - Free loaded image and destroy window and renderer
 * @instance: SDL_Instance structure
 * @texture: Texture structure
*/
void Close(SDL_Instance *instance, Texture *texture)
{
	int i;

	for (i = 0; i < TOTAL; i++)
	{
		if (texture[i].texture != NULL)
		{
			SDL_DestroyTexture(texture[i].texture);
			texture[i].texture = NULL;
		}
	}
	free(texture);

	SDL_DestroyRenderer(instance->renderer);
	SDL_DestroyWindow(instance->window);
	instance->renderer = NULL;
	instance->window = NULL;

	IMG_Quit();
	SDL_Quit();
}

/**
 * Update_Status - Update status of the game
 * @e: SDL_Event structure
 * @running: check if game is running
*/
void Update_Status(SDL_Event e, bool *running)
{
	if (e.type == SDL_QUIT)
		*running = false;
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_ESCAPE)
			*running = false;
	}
}

/**
 * draw_map - draw map
 * @instance: SDL_Instance structure
*/
void draw_map(SDL_Instance instance)
{
	SDL_Rect map_viwer = {
	(SCREEN_WIDTH - (CC * mapW)) / 2,
	SCREEN_HEIGHT - (CC * mapH),
	CC * mapW,
	CC * mapH};


	SDL_RenderSetViewport(instance.renderer, &map_viwer);
	SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 60);
	for (int i = 0; i < mapH; i++)
	{
		for (int j = 0; j < mapW; j++)
		{
			if (map[i][j] > 0)
			{
				SDL_Rect rect = {
					j * CC,
					i * CC,
					CC,
					CC};
				SDL_RenderFillRect(instance.renderer, &rect);
			}
		}
	}
}
