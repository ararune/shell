#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "mkdir.h"

int lsh_mkdir(char **args) {
  if (mkdir(args[1], 0777) == -1) {
    perror("lsh");
  }
  return 1;
}

