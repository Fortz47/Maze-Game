#ifndef MAZE_H
#define MAZE_H

#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <SDL.h>
#include <SDL_image.h>
#include "../headers/structs.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define NUM_RAYS 800
#define CC 8   /* cell size */
#define wH CC   /* wall height */
#define pH wH / 2   /* player height */
#define mapW 24   /* map width */
#define mapH 24   /* map height */
#define FOV 66.0 / 800.0 /* Field of view */
/* distance from player to projection plane */
#define Player_2_ProjP (SCREEN_WIDTH / 2) / tan(33 * (M_PI / 180))


/***** Global variables *****/

/* Map of the game */
extern const int map[mapH][mapW];

/***** Function prototypes by files *****/

/* collision handling */
void collision(Player *player);

/* player handling */
void setupPlayer(Player *player);
void updatePlayer(Player *player);
void move_player(SDL_Event e, Player *player);
void moveCamera(SDL_Event e, Player *player);

/* setup handling */
Texture loadTextureFromFile(SDL_Instance instance, const char *path);
void Close(SDL_Instance *instance, Texture *texture);
void Update_Status(SDL_Event e, bool *running);
void draw_map(SDL_Instance instance);

/* rays handling */
void cast_rays(SDL_Instance instance, Player player, Ray *rays, const int map[mapH][mapW]);
void castWall(SDL_Instance *instance, Ray *rays, Player player);
void castFloor(SDL_Instance instance, Ray *rays);
void castCeiling(SDL_Instance instance, Ray *rays);

/* initialization */
int init_sdl(SDL_Instance *instance);

/* utility functions */
double cal_R(int x1, int x2, int y1, int y2);
float _absf(float n);
int _abs(int n);
int invert(int n);
SDL_Point getDir(float angle);

/* utility2 functions */
float rad(float angle);

#endif