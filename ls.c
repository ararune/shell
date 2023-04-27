#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fnmatch.h>
#include "ls.h"

// This function is used to compare two `dirent` structures by name
// It is passed as a parameter to the `qsort` function, which will use it to sort an array of `dirent` pointers
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
  // Call `scandir` to get an array of `dirent` structures for the current       directory
  // The `alphasort` function is used to sort the entries alphabetically
  num_entries = scandir(".", &entries, NULL, alphasort);
  if (num_entries == -1) {
    perror("lsh");
    return 1;
  }

  // Loop through each entry in the array and print the name if it matches the specified pattern and is not hidden
  for (int i = 0; i < num_entries; i++) {
    if (!show_hidden && entries[i]->d_name[0] == '.') {
      continue; // skip over hidden files and directories
    }
    if (fnmatch(pattern, entries[i]->d_name, FNM_PATHNAME) == 0) {
      printf("%s  ", entries[i]->d_name);
    }
  }
  printf("\n");

  // Free the memory allocated for the `dirent` structures and the array
  for (int i = 0; i < num_entries; i++) {
    free(entries[i]);
  }
  free(entries);
  return 1;
}

