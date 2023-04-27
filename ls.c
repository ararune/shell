#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ls.h"

int lsh_ls(char **args) {
  DIR *dir;
  struct dirent *entry;
  if (args[1] == NULL) {
    dir = opendir(".");
  } else {
    dir = opendir(args[1]);
  }
  if (dir == NULL) {
    perror("lsh");
    return 1;
  } else {
    while ((entry = readdir(dir)) != NULL) {
      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
        continue; // skip over "." and ".."
      }
      printf("%s  ", entry->d_name);
    }
    printf("\n");
    closedir(dir);
    return 1;
  }
}

