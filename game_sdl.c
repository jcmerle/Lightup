// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h> // required to load transparent texture from PNG
#include <SDL_ttf.h>   // required to use TTF fonts
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "game.h"
#include "game_aux.h"
#include "game_tools.h"
#include "sdl.h"

/* **************************************************************** */

int main(int argc, char *argv[])
{
  /* initialize SDL2 and some extensions */
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
    ERROR("Error: SDL_Init VIDEO (%s)", SDL_GetError());
  if (IMG_Init(IMG_INIT_PNG & IMG_INIT_PNG) != IMG_INIT_PNG)
    ERROR("Error: IMG_Init PNG (%s)", SDL_GetError());
  if (TTF_Init() != 0)
    ERROR("Error: TTF_Init (%s)", SDL_GetError());

  /* create window and renderer */
  SDL_Window *win = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
  if (!win)
    ERROR("Error: SDL_CreateWindow (%s)", SDL_GetError());
  SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!ren)
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_SOFTWARE);
  if (!ren)
    ERROR("Error: SDL_CreateRenderer (%s)", SDL_GetError());

  /* initialize your environment */
  game g = NULL;
  if (argc == 2)
    g = game_load(argv[1]);
  else
    g = game_default();
  assert(g);
  Env *env = init(win, ren);

  /* main render loop */
  SDL_Event e;
  bool quit = false;
  while (!quit)
  {
    /* manage events */
    while (SDL_PollEvent(&e))
    {
      /* process your events */
      quit = process(win, &e, g);
      if (quit)
      {
        break;
      }
    }

    /* background in black */
    SDL_SetRenderDrawColor(ren, 0, 0, 0, 255);
    SDL_RenderClear(ren);

    /* render all what you want */
    render(win, ren, env, g);
    SDL_RenderPresent(ren);
    SDL_Delay(DELAY);
  }

  /* clean your environment */
  clean(win, ren, env);

  IMG_Quit();
  TTF_Quit();
  SDL_Quit();

  return EXIT_SUCCESS;
}
