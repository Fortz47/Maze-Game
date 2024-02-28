#include "../headers/maze.h"


int main(int argc, char *argv[])
{
	SDL_Instance instance;
	SDL_Event event;
	bool running = true;
	Texture *ptxt;
	Player player;
	setupPlayer(&player);
	Ray rays[NUM_RAYS];

	/* Initialize SDL */
	if (init_sdl(&instance) == 0)
	{
		ptxt = loadTextures(instance, array);
		/* Main loop */
		while (running)
		{
			while (SDL_PollEvent(&event) != 0)
			{
				Update_Status(event, &running);
				current_time = SDL_GetTicks();
				previous_time = current_time;
				moveCameraAndPlayer(event, &player);
			}

			/* clear the screen */
			SDL_SetRenderDrawColor(instance.renderer, 0, 0, 0, 255);
			SDL_RenderClear(instance.renderer);

			/* draw walls */
			SDL_RenderSetViewport(instance.renderer, NULL);
			castWall(&instance, rays, player);
			mapTextureToWall(instance, rays, &ptxt[COLORSTONE]);

			/* draw floor */
			castFloor(instance, rays);
			/*mapTextureToFloor(instance, rays, &ptxt[STONE_FLOOR]);*/

			/* draw ceiling */
			castCeiling(instance, rays);

			draw_map(instance);

			/*player texture setting
			SDL_Rect dst = {
				player.pos.x,
				player.pos.y,
				ptxt.w,
				ptxt.h};


			SDL_RenderCopyEx(instance.renderer, ptxt.texture, NULL, &dst, player.angle, NULL, SDL_FLIP_NONE); */

			/* cast rays */
			SDL_SetRenderDrawBlendMode(instance.renderer, SDL_BLENDMODE_BLEND);
			SDL_SetRenderDrawColor(instance.renderer, 255, 255, 255, 10);
			cast_rays(instance, player, rays, map);

			/* Update the screen */
			SDL_RenderPresent(instance.renderer);
		}
		/* Cleanup */
		Close(&instance, ptxt);
	}

	return 0;
}