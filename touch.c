#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "touch.h"

int lsh_touch(char **args)
{
  int fd = open(args[1], O_CREAT, 0644);
  if (fd == -1) {
    perror("lsh");
  } else {
    close(fd);
  }
  return 1;
}
