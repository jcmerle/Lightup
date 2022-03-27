// SDL2 Demo by aurelien.esnard@u-bordeaux.fr

#include <SDL.h>
#include <SDL_image.h> // required to load transparent texture from PNG
#include <SDL_ttf.h>   // required to use TTF fonts

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "sdl.h"
#include "game.h"
#include "game_aux.h"
#include "game_tools.h"
#include "game_ext.h"

/* **************************************************************** */
struct Env_t
{
  SDL_Texture *pacman;
  SDL_Texture *pacmanred;
  SDL_Texture *dot;
  SDL_Texture *cross;
  SDL_Texture *marked;
  SDL_Texture *back_arrow;
  SDL_Texture *forward_arrow;
  SDL_Texture *repeat_arrow;
  SDL_Texture *save_button;
  SDL_Texture *solve_button;
  SDL_Texture *quit_button;
  SDL_Texture *number0;
  SDL_Texture *number1;
  SDL_Texture *number2;
  SDL_Texture *number3;
  SDL_Texture *number4;
  SDL_Texture *text;
};

/* **************************************************************** */
void GetGameGridSize(int w, int h, SDL_Rect *game_grid)
{
  game_grid->x = w / 10;
  game_grid->y = h / 10;
  game_grid->w = w - (2 * game_grid->x);
  game_grid->h = h - (2 * game_grid->y);
}

/* **************************************************************** */

void GetTopButtonSize(SDL_Rect *game_grid, SDL_Rect *top_buttons_rect)
{
  top_buttons_rect->w = game_grid->w / 6;
  top_buttons_rect->h = game_grid->y / 2;
  top_buttons_rect->x = game_grid->x;
  top_buttons_rect->y = (game_grid->y - top_buttons_rect->h) / 2;
}

/* **************************************************************** */

void GetBottomButtonSize(SDL_Rect *game_grid, SDL_Rect *top_buttons_rect, SDL_Rect *bottom_buttons_rect)
{
  bottom_buttons_rect->w = top_buttons_rect->w;
  bottom_buttons_rect->h = top_buttons_rect->h;
  bottom_buttons_rect->x = game_grid->x;
  bottom_buttons_rect->y = game_grid->y + game_grid->h + top_buttons_rect->y;
}

/* **************************************************************** */

void GetSquareSize(game g, SDL_Rect *game_grid, SDL_Rect *square)
{
  square->x = game_grid->x;
  square->y = game_grid->y;
  square->w = game_grid->w / game_nb_cols(g);
  square->h = game_grid->h / game_nb_rows(g);
}

/* **************************************************************** */

void LeftClickActions(game g, uint i, uint j)
{
  if (!game_is_lightbulb(g, i, j) && game_check_move(g, i, j, S_LIGHTBULB) && !game_is_marked(g,i,j))
  {
    game_play_move(g, i, j, S_LIGHTBULB);
  }
  else if (game_check_move(g, i, j, S_BLANK))
  {
    game_play_move(g, i, j, S_BLANK);
  }
}

/* **************************************************************** */

void RightClickActions(game g, uint i, uint j)
{
  if (!game_is_marked(g, i, j) && game_check_move(g, i, j, S_MARK) && !game_is_lightbulb(g,i,j))
  {
    game_play_move(g, i, j, S_MARK);
  }
  else if (game_check_move(g, i, j, S_BLANK))
  {
    game_play_move(g, i, j, S_BLANK);
  }
}
/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[])
{
  Env *env = malloc(sizeof(struct Env_t));

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* init congratulations text texture using pacman font */
  SDL_Color color = {255, 127, 0, 255};
  TTF_Font *font = TTF_OpenFont(FONT, 40);
  if (!font)
    ERROR("TTF_OpenFont: %s\n", FONT);
  SDL_Surface *cong = TTF_RenderText_Blended(font, "Congratulations!", color);
  env->text = SDL_CreateTextureFromSurface(ren, cong);
  SDL_FreeSurface(cong);
  TTF_CloseFont(font);

  /* init pacman texture from PNG image */
  env->pacman = IMG_LoadTexture(ren, PACMAN);
  if (!env->pacman)
    ERROR("IMG_LoadTexture: %s\n", PACMAN);

  /* init pacmanred texture from PNG image */
  env->pacmanred = IMG_LoadTexture(ren, PACMANRED);
  if (!env->pacmanred)
    ERROR("IMG_LoadTexture: %s\n", PACMANRED);

  /* init dot texture from PNG image */
  env->dot = IMG_LoadTexture(ren, DOT);
  if (!env->dot)
    ERROR("IMG_LoadTexture: %s\n", DOT);

  /* init cross texture from PNG image */
  env->cross = IMG_LoadTexture(ren, CROSS);
  if (!env->cross)
    ERROR("IMG_LoadTexture: %s\n", CROSS);

  /* init marked texture from PNG image */
  env->marked = IMG_LoadTexture(ren, MARKED);
  if (!env->marked)
    ERROR("IMG_LoadTexture: %s\n", MARKED);

  /* init back arrow texture from PNG image */
  env->back_arrow = IMG_LoadTexture(ren, BACK_ARROW);
  if (!env->back_arrow)
    ERROR("IMG_LoadTexture: %s\n", BACK_ARROW);

  /* init forward_arrow texture from PNG image */
  env->forward_arrow = IMG_LoadTexture(ren, FORWARD_ARROW);
  if (!env->forward_arrow)
    ERROR("IMG_LoadTexture: %s\n", FORWARD_ARROW);

  /* init repeat arrow texture from PNG image */
  env->repeat_arrow = IMG_LoadTexture(ren, REPEAT_ARROW);
  if (!env->repeat_arrow)
    ERROR("IMG_LoadTexture: %s\n", REPEAT_ARROW);

  /* init save_button texture from PNG image */
  env->save_button = IMG_LoadTexture(ren, SAVE_BUTTON);
  if (!env->save_button)
    ERROR("IMG_LoadTexture: %s\n", SAVE_BUTTON);

  /* init solve_button texture from PNG image */
  env->solve_button = IMG_LoadTexture(ren, SOLVE_BUTTON);
  if (!env->solve_button)
    ERROR("IMG_LoadTexture: %s\n", SOLVE_BUTTON);

  /* init quit_button texture from PNG image */
  env->quit_button = IMG_LoadTexture(ren, QUIT_BUTTON);
  if (!env->quit_button)
    ERROR("IMG_LoadTexture: %s\n", QUIT_BUTTON);

  /* init number 0 texture from PNG image */
  env->number0 = IMG_LoadTexture(ren, NUMBER0);
  if (!env->number0)
    ERROR("IMG_LoadTexture: %s\n", NUMBER0);

  /* init number 1 texture from PNG image */
  env->number1 = IMG_LoadTexture(ren, NUMBER1);
  if (!env->number1)
    ERROR("IMG_LoadTexture: %s\n", NUMBER1);

  /* init number 2 texture from PNG image */
  env->number2 = IMG_LoadTexture(ren, NUMBER2);
  if (!env->number2)
    ERROR("IMG_LoadTexture: %s\n", NUMBER2);

  /* init number 3 texture from PNG image */
  env->number3 = IMG_LoadTexture(ren, NUMBER3);
  if (!env->number3)
    ERROR("IMG_LoadTexture: %s\n", NUMBER3);

  /* init number 4 texture from PNG image */
  env->number4 = IMG_LoadTexture(ren, NUMBER4);
  if (!env->number4)
    ERROR("IMG_LoadTexture: %s\n", NUMBER4);

  return env;
}

/* **************************************************************** */

void render(SDL_Window *win, SDL_Renderer *ren, Env *env, game g)
{
  SDL_Rect rect;
  SDL_Rect game_grid;
  SDL_Rect square;
  SDL_Rect top_buttons_rect;
  SDL_Rect bottom_buttons_rect;
  SDL_Rect sq_aux;

  /* set some colors */
  SDL_Color blue_color = {25, 75, 240, SDL_ALPHA_OPAQUE};
  SDL_Color green_color = {40, 175, 60, SDL_ALPHA_OPAQUE};

  /* get current window size */
  int w, h;
  SDL_GetWindowSize(win, &w, &h);

  /* get scaling and size of the grid to be centered */
  GetGameGridSize(w, h, &game_grid);

  /* get scaling and size of the buttons at top of the grid*/
  GetTopButtonSize(&game_grid, &top_buttons_rect);

  /* get scaling and size of the buttons at the bottom of the grid*/
  GetBottomButtonSize(&game_grid, &top_buttons_rect, &bottom_buttons_rect);

  /* get size of a square depending of the window's size */
  GetSquareSize(g, &game_grid, &square);

  /* display the menu at the top of the grid */
  SDL_RenderCopy(ren, env->back_arrow, NULL, &top_buttons_rect);
  top_buttons_rect.x = (game_grid.x + game_grid.w) / 2;
  SDL_RenderCopy(ren, env->repeat_arrow, NULL, &top_buttons_rect);
  top_buttons_rect.x = (game_grid.x + game_grid.w) - top_buttons_rect.w;
  SDL_RenderCopy(ren, env->forward_arrow, NULL, &top_buttons_rect);

  /* display the menu at the bottom of the grid */
  SDL_RenderCopy(ren, env->save_button, NULL, &bottom_buttons_rect);
  bottom_buttons_rect.x = (game_grid.x + game_grid.w) / 2;
  SDL_RenderCopy(ren, env->solve_button, NULL, &bottom_buttons_rect);
  bottom_buttons_rect.x = (game_grid.x + game_grid.w) - bottom_buttons_rect.w;
  SDL_RenderCopy(ren, env->quit_button, NULL, &bottom_buttons_rect);

  for (uint case_y = 0; case_y < game_nb_rows(g); case_y += 1, square.y += square.h)
  {
    if (case_y == game_nb_rows(g) - 1)
    {
      square.h += game_grid.h % game_nb_rows(g);
    }

    square.x = game_grid.x;
    square.w = game_grid.w / game_nb_cols(g);
    square.h = game_grid.h / game_nb_rows(g);

    for (uint case_x = 0; case_x < game_nb_cols(g); case_x += 1, square.x += square.w)
    {
      if (case_x == game_nb_cols(g) - 1)
      {
        square.w += game_grid.w % game_nb_cols(g);
      }

      uint i = case_y;
      uint j = case_x;
      if (game_is_blank(g, i, j))
      {
        if (game_is_lighted(g, i, j))
        {
          SDL_SetRenderDrawColor(ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
          SDL_RenderFillRect(ren, &square);
        }
        else
        {
          sq_aux.x = square.x + game_grid.x / 2;
          sq_aux.y = square.y + game_grid.y / 2;
          sq_aux.w = square.w / 7;
          sq_aux.h = square.h / 7;
          SDL_RenderCopy(ren, env->dot, NULL, &sq_aux);
        }
      }

      else if (game_is_marked(g, i, j))
      {
        sq_aux.x = square.x + game_grid.x / 7;
        sq_aux.y = square.y + game_grid.y / 7;
        sq_aux.w = square.w / 1.3;
        sq_aux.h = square.h / 1.3;
        SDL_RenderCopy(ren, env->marked, NULL, &sq_aux);
      }

      else if (game_is_lightbulb(g, i, j))
      {
        SDL_RenderCopy(ren, env->pacman, NULL, &square);
      }

      else if (game_is_black(g, i, j))
      {
        SDL_SetRenderDrawColor(ren, 25, 75, 240, SDL_ALPHA_OPAQUE); // color of walls
        SDL_RenderDrawRect(ren, &square);
        int black_number = game_get_black_number(g, i, j);
        if (black_number != -1)
        {
          sq_aux.x = square.x + game_grid.x / 7;
          sq_aux.y = square.y + game_grid.y / 7;
          sq_aux.w = square.w / 1.3;
          sq_aux.h = square.h / 1.3;
          if (black_number == 0)
            SDL_RenderCopy(ren, env->number0, NULL, &sq_aux);
          if (black_number == 1)
            SDL_RenderCopy(ren, env->number1, NULL, &sq_aux);
          if (black_number == 2)
            SDL_RenderCopy(ren, env->number2, NULL, &sq_aux);
          if (black_number == 3)
            SDL_RenderCopy(ren, env->number3, NULL, &sq_aux);
          if (black_number == 4)
            SDL_RenderCopy(ren, env->number4, NULL, &sq_aux);
        }
      }
      if (game_has_error(g, i, j))
      {
        if (game_is_black(g, i, j))
        {
          SDL_RenderCopy(ren, env->cross, NULL, &square);
        }
        else
        {
          SDL_RenderCopy(ren, env->pacmanred, NULL, &square);
        }
      }
    }
  }
  /* draw the external outline */
  SDL_SetRenderDrawColor(ren, blue_color.r, blue_color.g, blue_color.b, blue_color.a);
  SDL_RenderDrawRect(ren, &game_grid);

  if (game_is_over(g))
  {
    SDL_QueryTexture(env->text, NULL, NULL, &rect.w, &rect.h);
    rect.x = w / 2 - rect.w / 2;
    rect.y = h / 2 - rect.h / 2;
    SDL_RenderCopy(ren, env->text, NULL, &rect);
    SDL_RenderPresent(ren);
    SDL_Delay(5000);
  }
}

/* **************************************************************** */

bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e, game g)
{
  int w, h;
  uint i, j;

  SDL_Rect rect;
  SDL_Rect game_grid;
  SDL_Rect square;
  SDL_Rect top_buttons_rect;
  SDL_Rect bottom_buttons_rect;
  /* get current window size */
  SDL_GetWindowSize(win, &w, &h);

  /* get scaling and size of the grid to be centered */
  GetGameGridSize(w, h, &game_grid);

  /* get scaling and size of the buttons at top of the grid*/
  GetTopButtonSize(&game_grid, &top_buttons_rect);

  /* get scaling and size of the buttons at the bottom of the grid*/
  GetBottomButtonSize(&game_grid, &top_buttons_rect, &bottom_buttons_rect);

  /* get size of a square depending of the window's size */
  GetSquareSize(g, &game_grid, &square);

  if (e->type == SDL_QUIT)
  {
    return true;
  }

  else if (e->type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_Point mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    i = (mouse.y - game_grid.y) / square.h;
    j = (mouse.x - game_grid.x) / square.w;

    /* if we click inside the grid */
    if (mouse.y > game_grid.y && mouse.y < game_grid.y + game_grid.h && mouse.x >= game_grid.x && mouse.x < game_grid.x + game_grid.w)
    {
      if (e->button.button == SDL_BUTTON_LEFT)
      {
        LeftClickActions(g, i, j);
      }
      else if (e->button.button == SDL_BUTTON_RIGHT)
      {
        RightClickActions(g, i, j);
      }
    }

    /* else if we click at the top of the grid */
    else if (mouse.y >= top_buttons_rect.y && mouse.y < game_grid.y - top_buttons_rect.y)
    {
      if (mouse.x >= game_grid.x && mouse.x < game_grid.x + top_buttons_rect.w)
        game_undo(g);
      else if (mouse.x >= (game_grid.x + game_grid.w) / 2 && mouse.x < ((game_grid.x + game_grid.w) / 2) + top_buttons_rect.w)
        game_restart(g);
      else if (mouse.x >= game_grid.x + game_grid.w - top_buttons_rect.w && mouse.x < game_grid.x + game_grid.w)
        game_redo(g);
    }

    /* else if we click at the bottom of the grid */
    else if (mouse.y > bottom_buttons_rect.y && mouse.y < bottom_buttons_rect.y + bottom_buttons_rect.h)
    {
      if (mouse.x >= game_grid.x && mouse.x < game_grid.x + top_buttons_rect.w)
        game_save(g, "game_save");
      else if (mouse.x >= (game_grid.x + game_grid.w) / 2 && mouse.x < ((game_grid.x + game_grid.w) / 2) + top_buttons_rect.w)
        game_solve(g);
      else if (mouse.x >= game_grid.x + game_grid.w - top_buttons_rect.w && mouse.x < game_grid.x + game_grid.w)
        return true; // We quit the game
    }
  }

  if (game_is_over(g))
  {
    return true;
  }

  return false;
}

/* **************************************************************** */

void clean(SDL_Window *win, SDL_Renderer *ren, Env *env)
{
  SDL_DestroyTexture(env->pacman);
  SDL_DestroyTexture(env->dot);
  SDL_DestroyTexture(env->back_arrow);
  SDL_DestroyTexture(env->forward_arrow);
  SDL_DestroyTexture(env->repeat_arrow);
  SDL_DestroyTexture(env->save_button);
  SDL_DestroyTexture(env->solve_button);
  SDL_DestroyTexture(env->quit_button);
  SDL_DestroyTexture(env->number0);
  SDL_DestroyTexture(env->number1);
  SDL_DestroyTexture(env->number2);
  SDL_DestroyTexture(env->number3);
  SDL_DestroyTexture(env->number4);

  free(env);

  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
}

/* **************************************************************** */
