#include <dirent.h>
#include <fnmatch.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ls.h"

#define COLOR_DIR "\033[1;36m"  // Cyan
#define COLOR_FILE "\033[0m"  // Reset color
#define COLOR_EXEC "\033[1;33m"  // Yellow

void print_permissions(mode_t mode) {
  printf((mode & S_IRUSR) ? "r" : "-");
  printf((mode & S_IWUSR) ? "w" : "-");
  printf((mode & S_IXUSR) ? "x" : "-");
  printf((mode & S_IRGRP) ? "r" : "-");
  printf((mode & S_IWGRP) ? "w" : "-");
  printf((mode & S_IXGRP) ? "x" : "-");
  printf((mode & S_IROTH) ? "r" : "-");
  printf((mode & S_IWOTH) ? "w" : "-");
  printf((mode & S_IXOTH) ? "x" : "-");
}

int lsh_ls(char **args) {
  bool show_hidden = false;
  bool show_permissions = false;
  char *pattern = "*";
  struct dirent **entries;
  struct stat filestat;
  int num_entries;

  for (int i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], "-a") == 0 || strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0) {
      show_hidden = true;
    }
    if (strcmp(args[i], "-l") == 0 || strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0) {
      show_permissions = true;
    }
    if (args[i][0] != '-') {
      pattern = args[i];
    }
  }

  num_entries = scandir(".", &entries, NULL, alphasort);
  if (num_entries == -1) {
    perror("lsh");
    return 1;
  }

  for (int i = 0; i < num_entries; i++) {
    if (!show_hidden && entries[i]->d_name[0] == '.') {
      continue;
    }
    if (fnmatch(pattern, entries[i]->d_name, FNM_PATHNAME) == 0) {
      if (show_permissions) {
        if (stat(entries[i]->d_name, &filestat) == -1) {
          perror("lsh");
          continue;
        }
        print_permissions(filestat.st_mode);
        printf(" ");
      }
      if (entries[i]->d_type == DT_DIR) {
        printf(COLOR_DIR "%s  " COLOR_FILE, entries[i]->d_name);
      } else if (access(entries[i]->d_name, X_OK) == 0) {
        printf(COLOR_EXEC "%s  " COLOR_FILE, entries[i]->d_name);
      } else {
        printf("%s  ", entries[i]->d_name);
      }

      if (show_permissions) {
        printf("\n");
      }
    }
  }

  printf("\n");

  for (int i = 0; i < num_entries; i++) {
    free(entries[i]);
  }

  free(entries);

  return 1;
}

