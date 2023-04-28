#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "ls.h"

#define COLOR_DIR "\033[38;5;39m"  // Blue
#define COLOR_FILE "\033[0m"  // Reset color

int compare_names(const void *a, const void *b) {
  const struct dirent **entry1 = (const struct dirent **)a;
  const struct dirent **entry2 = (const struct dirent **)b;
  return strcmp((*entry1)->d_name, (*entry2)->d_name);
}

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
  DIR *dir;
  struct dirent **entries;
  struct stat filestat;
  char *pattern = "*";
  int num_entries;
  int show_hidden = 0;
  int show_permissions = 0;

  for (int i = 1; args[i] != NULL; i++) {
    if (strcmp(args[i], "-a") == 0 || strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0) {
      show_hidden = 1;
    }
    if (strcmp(args[i], "-l") == 0 || strcmp(args[i], "-al") == 0 || strcmp(args[i], "-la") == 0) {
      show_permissions = 1;
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
      continue; // skip over hidden files and directories
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

