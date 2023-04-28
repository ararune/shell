#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cd.h"

int lsh_cd(char **args)
{
  if (args[1] == NULL) {
    fprintf(stderr, "lsh: expected argument to \"cd\"\n");
  } else {
    if (strcmp(args[1], "~") == 0) {
      char* home_dir = getenv("HOME");
      if (home_dir == NULL) {
        perror("lsh");
        return 1;
      } else {
        if (chdir(home_dir) != 0) {
          perror("lsh");
          return 1;
        }
      }
    } else {
      if (chdir(args[1]) != 0) {
        perror("lsh");
        return 1;
      }
    }
  }
  return 1;
}

