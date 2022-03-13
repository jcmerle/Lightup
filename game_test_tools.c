#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "game_aux.h"
#include "game_examples.h"
#include "game_ext.h"
#include "game_test.h"
#include "game_tools.h"


/* ************************************************************************** */
/*                           GAME_TOOLS TESTS                         */
/* ************************************************************************** */

int test_game_save(void)
{
  game g0 = game_default();
  game_play_move(g0, 0, 0, S_LIGHTBULB);
  game_play_move(g0, 1, 1, S_LIGHTBULB);
  game_play_move(g0, 2, 2, S_LIGHTBULB);
  game_play_move(g0, 0, 3, S_LIGHTBULB);
  game_play_move(g0, 1, 6, S_LIGHTBULB);
  game_play_move(g0, 3, 6, S_LIGHTBULB);
  game_play_move(g0, 4, 4, S_LIGHTBULB);
  game_play_move(g0, 5, 0, S_LIGHTBULB);
  game_play_move(g0, 5, 5, S_LIGHTBULB);
  game_play_move(g0, 6, 1, S_LIGHTBULB);
  game_save(g0, "save0");
  game g1 = game_load("save0");
  bool test0 = game_equal(g0, g1);
  game_delete(g0);
  game_delete(g1);
  if (test0)
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

int test_game_load(void)
{
  game g0 = game_default();
  game_play_move(g0, 0, 0, S_LIGHTBULB);
  game_play_move(g0, 1, 1, S_LIGHTBULB);
  game_play_move(g0, 2, 2, S_LIGHTBULB);
  game_play_move(g0, 0, 3, S_LIGHTBULB);
  game_play_move(g0, 1, 6, S_LIGHTBULB);
  game_play_move(g0, 3, 6, S_LIGHTBULB);
  game_play_move(g0, 4, 4, S_LIGHTBULB);
  game_play_move(g0, 5, 0, S_LIGHTBULB);
  game_play_move(g0, 5, 5, S_LIGHTBULB);
  game_play_move(g0, 6, 1, S_LIGHTBULB);
  game_save(g0, "save0");
  game g1 = game_load("save0");
  bool test0 = game_equal(g0, g1);
  game_delete(g0);
  game_delete(g1);
  if (test0)
    return EXIT_SUCCESS;
  return EXIT_FAILURE;
}

int test_game_solve(void)
{
  // We load a 3x10 game which is huge
  // to really see the performance
  // of the game_solve function
  game g = game_load("../examples/game_3x10.txt");
  game_solve(g);

  if (!game_is_over(g))
  {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int test_game_nb_solution(void)
{
  // We load a 3x10 game which is huge
  // to really see the performance
  // of the game_nb_solution function
  game g = game_load("../examples/blank_4x4.txt");
  uint sol = game_nb_solutions(g);
  printf("Number of solutions: %u\n", sol);

  return EXIT_SUCCESS;
}
