#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "ls.h"

#define COLOR_DIR "\033[38;5;39m"  // Blue
#define COLOR_FILE "\033[0m"  // Reset color

int compare_names(const void *a, const void *b) {
  const struct dirent **entry1 = (const struct dirent **)a;
  const struct dirent **entry2 = (const struct dirent **)b;
  return strcmp((*entry1)->d_name, (*entry2)->d_name);
}

int lsh_ls(char **args) {
  DIR *dir;
  struct dirent **entries;
  char *pattern;
  int num_entries;
  int show_hidden = 0;

  // Check for -a flag
  if (args[1] != NULL && strcmp(args[1], "-a") == 0) {
    show_hidden = 1;
    if (args[2] == NULL) {
      pattern = "*";
    } else {
      pattern = args[2];
    }
  } else {
    if (args[1] == NULL) {
      pattern = "*";
    } else {
      pattern = args[1];
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
      if (entries[i]->d_type == DT_DIR) {
        printf(COLOR_DIR "%s  " COLOR_FILE, entries[i]->d_name);
      } else {
        printf("%s  ", entries[i]->d_name);
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

