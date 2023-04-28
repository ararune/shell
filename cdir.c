#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "cdir.h"

int lsh_cdir(char **args) {
  if (mkdir(args[1], 0777) == -1) {
    perror("lsh");
  } else {
    if (chdir(args[1]) == -1) {
      perror("lsh");
    }
  }
  return 1;
}
