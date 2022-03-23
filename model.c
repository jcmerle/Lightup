// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h> // required to load transparent texture from PNG
#include <SDL_ttf.h>   // required to use TTF fonts

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game_sdl.h"

/* **************************************************************** */

#define FIRE "fire.png"
#define WALL_0 "digit0.png"
#define WALL_1 "digit1.png"
#define WALL_2 "digit2.png"
#define WALL_3 "digit3.png"
#define WALL_4 "digit4.png"
#define WALL_U "colon.png"

/* **************************************************************** */

struct Env_t
{
  SDL_Texture *fire;
  SDL_Texture *wall0;
  SDL_Texture *wallu;
  int fire_x, fire_y;
  int wall0_x, wall0_y;
  int wallu_x, wallu_y;
};

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[])
{
  Env *env = malloc(sizeof(struct Env_t));

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init positions */
  env->fire_x = w / 2;
  env->fire_y = h / 4;
  env->wall0_x = w / 2;
  env->wall0_y = 3 * h / 4;
  env->wallu_x = 0;
  env->wallu_y = 0;

  /* init fire texture from PNG image */
  env->fire = IMG_LoadTexture(ren, FIRE);
  if (!env->fire)
    ERROR("IMG_LoadTexture: %s\n", FIRE);

  /* init wall0 texture from PNG image */
  env->wall0 = IMG_LoadTexture(ren, WALL_0);
  if (!env->wall0)
    ERROR("IMG_LoadTexture: %s\n", WALL_0);

  /* init wallu texture from PNG image */
  env->wallu = IMG_LoadTexture(ren, WALL_U);
  if (!env->wallu)
    ERROR("IMG_LoadTexture: %s\n", WALL_U);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
  SDL_Rect rect;

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* render fire texture */
  SDL_QueryTexture(env->fire, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->fire_x - rect.w / 2;
  rect.y = env->fire_y - rect.h / 2;
  SDL_RenderCopy(ren, env->fire, NULL, &rect);

  /* render wall0 texture */
  SDL_QueryTexture(env->wall0, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->wall0_x - rect.w / 2;
  rect.y = env->wall0_y - rect.h / 2;
  SDL_RenderCopy(ren, env->wall0, NULL, &rect);

  /* render wallu texture */
  SDL_QueryTexture(env->wallu, NULL, NULL, &rect.w, &rect.h);
  rect.x = env->wallu_x - rect.w / 2;
  rect.y = env->wallu_y - rect.h / 2;
  SDL_RenderCopy(ren, env->wallu, NULL, &rect);
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e)
{
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  if (e->type == SDL_QUIT)
  {
    return true;
  }

  else if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    env->fire_x = mouse.x;
    env->fire_y = mouse.y;
  }
  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
  SDL_DestroyTexture(env->fire);
  SDL_DestroyTexture(env->wall0);
  SDL_DestroyTexture(env->wallu);

  free(env);
}

/* **************************************************************** */
