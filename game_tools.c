#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "assert.h"
#include "game.h"
#include "game_aux.h"
#include "game_ext.h"
#include "game_private.h"
#include "game_test.h"

game game_load(char *filename)
{
  FILE *file = fopen(filename, "r");
  if (file == NULL)
  {
    fprintf(stderr, "no file\n");
    exit(EXIT_FAILURE);
  }
  int nb_rows;
  int nb_cols;
  int wrapping;
  char c;

  fscanf(file, "%d %d %d ", &nb_rows, &nb_cols, &wrapping);
  game g = game_new_empty_ext(nb_rows, nb_cols, wrapping);

  for (int i = 0; i < nb_rows; i++)
  {
    for (int j = 0; j < nb_cols; j++)
    {
      fscanf(file, "%c [^\n]", &c);
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
      else
      {
        fprintf(stderr, "Wrong state\n");
        exit(EXIT_FAILURE);
      }
    }
    // fscanf(file, "%c", &c); //We ignore the /n
  }
  fclose(file);
  game_update_flags(g);
  return g;
}

void game_save(cgame g, char *filename)
{
  if (g == NULL)
  {
    fprintf(stderr, "g null\n");
    exit(EXIT_FAILURE);
  }
  if (filename == NULL)
  {
    fprintf(stderr, "file null\n");
    exit(EXIT_FAILURE);
  }
  FILE *file = fopen(filename, "w");

  fprintf(file, "%u %u %d\n", g->nb_rows, g->nb_cols, g->wrapping);
  for (uint i = 0; i < (g->nb_rows); i++)
  {
    for (uint j = 0; j < (g->nb_cols); j++)
    {
      // if blank print b
      if (game_get_state(g, i, j) == S_BLANK)
        fprintf(file, "%c", 'b');
      // if lightbulb print *
      if (game_get_state(g, i, j) == S_LIGHTBULB)
        fprintf(file, "%c", '*');
      // if mark print m
      if (game_get_state(g, i, j) == S_MARK)
        fprintf(file, "%c", '-');
      // if unnumbered wall print w
      if (game_get_state(g, i, j) == S_BLACKU)
        fprintf(file, "%c", 'w');
      // else print wall number (0,1,2,3 or 4)
      else if (game_is_black(g, i, j))
      {
        char num = game_get_black_number(g, i, j) + '0';
        fprintf(file, "%c", num);
      }
    }
    fprintf(file, "\n");
  }
  fclose(file);
}

bool game_solve_aux(int nb_rows, int nb_cols, int coord_i, int coord_j, game g)
{
  // Recurrence stop condition
  if (coord_i == nb_rows && coord_j == 0)
  {
    return game_is_over(g);
  }

<<<<<<< HEAD
  // Double loop to see if the game has an error and so if it is necessary to continue
  // if the game has an error we stop and return false.
  // It is a really effective optimisation
  for (int y = 0; y < nb_rows; y++)
  {
    for (int x = 0; x < nb_cols; x++)
    {
      if (game_has_error(g, y, x))
      {
=======
  // Double loop to see if the game has an error and so if it is necessary to
  // continue if the game has an error we stop and return false. It is a really
  // effective optimisation
  for (int y = 0; y < nb_rows; y++) {
    for (int x = 0; x < nb_cols; x++) {
      if (game_has_error(g, y, x)) {
>>>>>>> 89f2ac09235418604fb617224269cb35d783526b
        return false;
      }
    }
  }

<<<<<<< HEAD
  // We put a lightbulb in the squares which are not lighted (optimisation of the algorithm)
  if (game_check_move(g, coord_i, coord_j, S_LIGHTBULB) && !game_is_lighted(g, coord_i, coord_j))
  {
    game_play_move(g, coord_i, coord_j, S_LIGHTBULB);
  }

  // we call the function on the next square which depends of the current position
  if (coord_j == nb_cols - 1)
  {
    if (game_solve_aux(nb_rows, nb_cols, coord_i + 1, 0, g))
    {
=======
  // We put a lightbulb in the squares which are not lighted (optimisation of
  // the algorithm)
  if (game_check_move(g, coord_i, coord_j, S_LIGHTBULB) && !game_is_lighted(g, coord_i, coord_j)) {
    game_play_move(g, coord_i, coord_j, S_LIGHTBULB);
  }

  // we call the function on the next square which depends of the current
  // position
  if (coord_j == nb_cols - 1) {
    if (game_solve_aux(nb_rows, nb_cols, coord_i + 1, 0, g)) {
>>>>>>> 89f2ac09235418604fb617224269cb35d783526b
      return true;
    }
  }
  else
  {
    if (game_solve_aux(nb_rows, nb_cols, coord_i, coord_j + 1, g))
    {
      return true;
    }
  }

  // And we do the same but not with a lightbulb but with a blank state.
  // It is necessary to go through all the different possible combinations.

  if (game_check_move(g, coord_i, coord_j, S_BLANK))
  {
    game_play_move(g, coord_i, coord_j, S_BLANK);
  }

  if (coord_j == nb_cols - 1)
  {
    if (game_solve_aux(nb_rows, nb_cols, coord_i + 1, 0, g))
    {
      return true;
    }
  }
  else
  {
    if (game_solve_aux(nb_rows, nb_cols, coord_i, coord_j + 1, g))
    {
      return true;
    }
  }

  // If we don't find a solution then we return false
  // and we go back to the previous square

  return false;
}

bool game_solve(game g)
{
  assert(g);
  game copy = game_copy(g);

  if (game_solve_aux(game_nb_rows(g), game_nb_cols(g), 0, 0, g))
  {
    return true;
  }

  // On renvoie g à l'état initial si on a pas trouvé
  else
  {
    g = game_copy(copy);
    return false;
  }
}

<<<<<<< HEAD
game exact_copy_of(game g)
{
  game copy = game_new_empty_ext(g->nb_rows, g->nb_cols, g->wrapping);

  for (uint i = 0; i < g->nb_rows; i++)
  {
    for (uint j = 0; j < g->nb_cols; j++)
    {
      if (game_is_blank(g, i, j))
      {
        game_play_move(copy, i, j, S_BLANK);
      }
      else if (game_is_lightbulb(g, i, j))
      {
        game_play_move(copy, i, j, S_LIGHTBULB);
      }
      else if (game_is_black(g, i, j))
      {
        game_set_square(copy, i, j, game_get_square(g, i, j));
      }
    }
  }

  game_update_flags(copy);

  return copy;
}

uint game_nb_solutions_aux(uint coord_i, uint coord_j, uint *nb_sol, game g, game copy, bool *is_solution)
{
  if (coord_i == game_nb_rows(g) && coord_j == 0)
  {
    if (game_is_over(g))
    {
      *is_solution = true;
      char string[10];
      char filename[10] = "sol_";

      if (*nb_sol > 0)
      {
        for (uint k = 1; k <= *nb_sol; k++)
        {
          sprintf(string, "%u", k);
          strcat(filename, strcat(string, ".txt"));
          copy = game_load(filename);

          if (game_equal(g, copy))
          {
            *is_solution = false;
          }
        }
      }
      if (*is_solution)
      {
        (*nb_sol)++;
        sprintf(string, "%u", *nb_sol);
        strcat(filename, strcat(string, ".txt"));
        game_save(g, filename);
      }
=======
uint game_nb_solutions_aux(uint coord_i, uint coord_j, uint* nb_sol, game g)
{
  if (coord_i == game_nb_rows(g)) {
    if (game_is_over(g)) {
      (*nb_sol)++;
>>>>>>> 89f2ac09235418604fb617224269cb35d783526b
    }
    return (*nb_sol);
  }

<<<<<<< HEAD
  if (game_check_move(g, coord_i, coord_j, S_LIGHTBULB) && !game_is_lighted(g, coord_i, coord_j))
  {
    game_play_move(g, coord_i, coord_j, S_LIGHTBULB);
  }

  if (coord_j == game_nb_cols(g) - 1)
  {
    game_nb_solutions_aux(coord_i + 1, 0, nb_sol, g, copy, is_solution);
  }
  else
  {
    game_nb_solutions_aux(coord_i, coord_j + 1, nb_sol, g, copy, is_solution);
  }

  if (game_check_move(g, coord_i, coord_j, S_BLANK))
  {
    if (!game_is_blank(g, coord_i, coord_j))
    {
      game_play_move(g, coord_i, coord_j, S_BLANK);
    }
  }

  if (coord_j == game_nb_cols(g) - 1)
  {
    game_nb_solutions_aux(coord_i + 1, 0, nb_sol, g, copy, is_solution);
  }
  else
  {
    game_nb_solutions_aux(coord_i, coord_j + 1, nb_sol, g, copy, is_solution);
=======
  if (coord_j == game_nb_cols(g)) {
    return game_nb_solutions_aux(coord_i + 1, 0, nb_sol, g);
  }

  if (game_is_black(g, coord_i, coord_j)) {
    return game_nb_solutions_aux(coord_i, coord_j + 1, nb_sol, g);
>>>>>>> 89f2ac09235418604fb617224269cb35d783526b
  }

  game_play_move(g, coord_i, coord_j, S_BLANK);
  game_nb_solutions_aux(coord_i, coord_j + 1, nb_sol, g);
  game_play_move(g, coord_i, coord_j, S_LIGHTBULB);
  return game_nb_solutions_aux(coord_i, coord_j + 1, nb_sol, g);
}

uint game_nb_solutions(cgame g)
{
  assert(g);
<<<<<<< HEAD
  game copy1 = game_copy(g);
  game copy2 = game_copy(g);
  uint nb_sol = 0;
  bool boolean = false;
  bool *is_solution = &boolean;

  game_nb_solutions_aux(0, 0, &nb_sol, copy1, copy2, is_solution);

  for (uint k = 1; k <= nb_sol; k++)
  {
    char string[10];
    char filename[10] = "sol_";
    sprintf(string, "%u", k);
    strcat(filename, strcat(string, ".txt"));
    remove(filename);
  }

  return nb_sol;
=======
  game copy = game_copy(g);
  // game copy2 = game_copy(g);
  uint nb_sol = 0;
  // int* change = 0;

  return game_nb_solutions_aux(0, 0, &nb_sol, copy);
>>>>>>> 89f2ac09235418604fb617224269cb35d783526b
}
