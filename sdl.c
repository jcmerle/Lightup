// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h> // required to load transparent texture from PNG
#include <SDL_ttf.h>   // required to use TTF fonts

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "sdl.h"
#include "game.h"

/* **************************************************************** */

#define FIRE "fire.png"

/* **************************************************************** */

struct Env_t
{
  SDL_Texture *fire;
  int fire_x, fire_y;
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

  /* init fire texture from PNG image */
  env->fire = IMG_LoadTexture(ren, FIRE);
  if (!env->fire)
    ERROR("IMG_LoadTexture: %s\n", FIRE);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env, game g)
{
  SDL_Rect rect;
  SDL_Rect game_grid;
  SDL_Rect square;

  /* set some colors */
  SDL_Color blue_color = {25, 75, 240, SDL_ALPHA_OPAQUE};
  SDL_Color green_color = {40, 175, 60, SDL_ALPHA_OPAQUE};

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* get padding and size of the grid to be centered */
  game_grid.x = w / 10;
  game_grid.y = h / 10;
  game_grid.w = w - (2 * game_grid.x);
  game_grid.h = h - (2 * game_grid.y);

  // SDL_SetRenderDrawColor(ren, green_color.r, green_color.g, green_color.b, green_color.a);

  /* get size of a square depending of the window's size */
  SDL_QueryTexture(env->fire, NULL, NULL, NULL, NULL);
  square.w = game_grid.w / DEFAULT_SIZE;
  square.h = game_grid.h / DEFAULT_SIZE;

  for (square.y = game_grid.y; square.y < game_grid.h + game_grid.y - square.h; square.y += square.h)
  {
    for (square.x = game_grid.x; square.x < game_grid.w + game_grid.x - square.w; square.x += square.w)
    {

      int i = (square.y - game_grid.y) / square.h;
      int j = (square.x - game_grid.x) / square.w;
      if (game_is_blank(g, i, j))
      {
        if (game_is_lighted(g, i, j))
        {
          SDL_SetRenderDrawColor(ren, 255, 0, 0, SDL_ALPHA_OPAQUE);
          SDL_RenderFillRect(ren, &square);
        }
      }

      else if (game_is_lightbulb(g, i, j))
      {
        SDL_RenderCopy(ren, env->fire, NULL, &square);
      }

      else if (game_is_black(g, i, j))
      {
        SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(ren, &square);
      }

      /* draw the grid */
      SDL_SetRenderDrawColor(ren, green_color.r, green_color.g, green_color.b, green_color.a);
      SDL_RenderDrawRect(ren, &square);
    }
  }
  /* draw the grid */
  SDL_SetRenderDrawColor(ren, blue_color.r, blue_color.g, blue_color.b, blue_color.a);
  SDL_RenderDrawRect(ren, &game_grid);
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

  free(env);
}

/* **************************************************************** */
