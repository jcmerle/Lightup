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
  //the executable must have 3 or 4 parameters
  if (argc <= 2 || argc > 4)
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }
  
  g = game_load(argv[2]);
  assert(g);

  //the -s option means to give the first solution of a game
  if(strcmp("-s", argv[1]) == 0)
  {
    if(game_solve(g))
    {
      
      if(argc == 3)
      {
        game_print(g); //We print the game solution in the standard output
      }
      else
      {
        game_save(g, argv[3]); //Or in a file
      }
    }
    else
    {
      return EXIT_FAILURE; //There is no solution for the game
    }
  }

  //the -c option means to give the number of solution for a game
  else if(strcmp("-c", argv[1]) == 0)
  {
    return EXIT_SUCCESS;
  }

  else //Not a correct option
  {
    usage(argv[0]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}