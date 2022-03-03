#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "game.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"

game game_load(char* filename)
{
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    fprintf(stderr, "no file\n");
    exit(EXIT_FAILURE);
  }
  int nb_rows;
  int nb_cols;
  int wrapping;
  char c;

  fscanf(file, "%d %d %d ", &nb_rows, &nb_cols, &wrapping);
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping);

  for (int i = 0; i < nb_rows; i++) {
    for (int j = 0; j < nb_cols; j++) {
      fscanf(file, "%c", &c);
      if (c == 'b')
        game_set_square(g, i, j, S_BLANK);
      else if (c == '*')
        game_set_square(g, i, j, S_LIGHTBULB);
      else if (c == '-')
        game_set_square(g, i, j, S_MARK);
      else if (c == '0')
        game_set_square(g, i, j, S_BLACK0);
      else if (c == '1')
        game_set_square(g, i, j, S_BLACK1);
      else if (c == '2')
        game_set_square(g, i, j, S_BLACK2);
      else if (c == '3')
        game_set_square(g, i, j, S_BLACK3);
      else if (c == '4')
        game_set_square(g, i, j, S_BLACK4);
      else if (c == 'w')
        game_set_square(g, i, j, S_BLACKU);
      else {
        fprintf(stderr, "Wrong state\n");
        exit(EXIT_FAILURE);
      }
    }
    fscanf(file, "%c", &c);
  }
  fclose(file);
  game_update_flags(g);
  return g;
}

void game_save(cgame g, char* filename)
{
  if (g == NULL) {
    fprintf(stderr, "g null\n");
    exit(EXIT_FAILURE);
  }
  if (filename == NULL) {
    fprintf(stderr, "file null\n");
    exit(EXIT_FAILURE);
  }
  FILE* file = fopen(filename, "w");

  fprintf(file, "%u %u %d\n", g->nb_rows, g->nb_cols, g->wrapping);
  for (uint i = 0; i < (g->nb_rows); i++) {
    for (uint j = 0; j < (g->nb_cols); j++) {
      // if blank print b
      if (game_get_state(g, i, j) == S_BLANK) fprintf(file, "%c", 'b');
      // if lightbulb print *
      if (game_get_state(g, i, j) == S_LIGHTBULB) fprintf(file, "%c", '*');
      // if mark print m
      if (game_get_state(g, i, j) == S_MARK) fprintf(file, "%c", '-');
      // if unnumbered wall print w
      if (game_get_state(g, i, j) == S_BLACKU) fprintf(file, "%c", 'w');
      // else print wall number (0,1,2,3 or 4)
      else if (game_is_black(g, i, j)) {
        char num = game_get_black_number(g, i, j) + '0';
        fprintf(file, "%c", num);
      }
    }
    fprintf(file, "\n");
  }
  fclose(file);
}


bool game_solve(game g)
{
  return 0;
}

uint game_nb_solutions(cgame g)
{
  return 0;
}

