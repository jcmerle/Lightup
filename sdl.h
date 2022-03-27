// SDL2 Model by aurelien.esnard@u-bordeaux.fr

#ifndef MODEL_H
#define MODEL_H

#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

#include "game.h"

typedef struct Env_t Env;

/* **************************************************************** */

#ifdef __ANDROID__
#define PRINT(STR, ...)          \
  do                             \
  {                              \
    SDL_Log(STR, ##__VA_ARGS__); \
  } while (0)
#define ERROR(STR, ...)          \
  do                             \
  {                              \
    SDL_Log(STR, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);          \
  } while (0)
#else
#define PRINT(STR, ...)         \
  do                            \
  {                             \
    printf(STR, ##__VA_ARGS__); \
  } while (0)
#define ERROR(STR, ...)                  \
  do                                     \
  {                                      \
    fprintf(stderr, STR, ##__VA_ARGS__); \
    exit(EXIT_FAILURE);                  \
  } while (0)
#endif

/* **************************************************************** */

#define APP_NAME "Lightup TM01A"
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600
#define DELAY 100

/* **************************************************************** */

#define PACMAN "pacman.png"
#define PACMANRED "pacmanred.png"
#define DOT "dot.png"
#define MARKED "marked.png"
#define BACK_ARROW "back_arrow.png"
#define FORWARD_ARROW "forward_arrow.png"
#define REPEAT_ARROW "repeat_arrow.png"
#define SAVE_BUTTON "save_button.png"
#define SOLVE_BUTTON "solve_button.png"
#define QUIT_BUTTON "quit_button.png"
#define NUMBER0 "number0.png"
#define NUMBER1 "number1.png"
#define NUMBER2 "number2.png"
#define NUMBER3 "number3.png"
#define NUMBER4 "number4.png"
#define RED0 "red0.png"
#define RED1 "red1.png"
#define RED2 "red2.png"
#define RED3 "red3.png"
#define RED4 "red4.png"
#define FONT "pacman.ttf"

/* **************************************************************** */

Env *init(SDL_Window *win, SDL_Renderer *ren, int argc, char *argv[]);
void render(SDL_Window *win, SDL_Renderer *ren, Env *env, game g);
void clean(SDL_Window *win, SDL_Renderer *ren, Env *env);
bool process(SDL_Window *win, SDL_Renderer *ren, Env *env, SDL_Event *e, game g);

/* **************************************************************** */

#endif
