#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rmdir.h"

int lsh_rmdir(char **args) {
  if (rmdir(args[1]) == -1) {
    perror("lsh");
  }
  return 1;
}

