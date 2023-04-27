#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "rm.h"

int lsh_rm(char **args) {
  if (remove(args[1]) == -1) {
    perror("lsh");
  }
  return 1;
}

