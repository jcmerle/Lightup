#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#include "game_aux.h"
#include "game_tools.h"

void usage(char* string)
{
  fprintf(stderr, "./%s <option> <input> [<output>], the last parameter is optional\n", string);
  fprintf(stderr, "<option> can be -s or -c\n");
}

int main(int argc, char* argv[])
{
  game g = NULL;
  if (argc <= 2 || argc > 4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  
  g = game_load(argv[2]);
  assert(g);

  if(strcmp("-s", argv[1]) == 0)
  {
    if(game_solve(g))
    {
      if(argc == 3)
      {
        game_print(g);
      }
      else
      {
        game_save(g, argv[3]);
      }
    }
    else
    {
      return EXIT_FAILURE;
    }
  }

  else if(strcmp("-c", argv[1]) == 0)
  {
    return EXIT_SUCCESS;
  }

  else
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}