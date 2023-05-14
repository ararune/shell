#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "cdir.h"

int lsh_cdir(char **args) {
  mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
  if (mkdir(args[1], mode) == -1) {
    perror("lsh");
    return 1;
  } 
  else if (chdir(args[1]) == -1) {
    perror("lsh");
    return 1;
  }
  return 1;
}

