#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <limits.h>
#include "find.h"

void search_directory(const char *dir_path, const char *file_name) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        fprintf(stderr, "Failed to open directory: %s\n", dir_path);
        return;
    }

    char path[PATH_MAX];
    char *full_path = NULL;
    struct dirent *entry;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(entry->d_name, file_name) == 0) {
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
            full_path = realpath(path, NULL);
            if (!full_path) {
                fprintf(stderr, "Failed to resolve path: %s\n", path);
                continue;
            }
            printf("%s\n", full_path);
        }

        if (entry->d_type == DT_DIR) {
            snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
            search_directory(path, file_name);
        }
    }

    if (full_path) {
        free(full_path);
    }
    closedir(dir);
}

int lsh_find(char **args) {
    if (!args[1]) {
        fprintf(stderr, "lsh: expected one argument to \"find\"\n");
        return 1;
    }

    char *home_dir = getenv("HOME");
    if (!home_dir) {
        fprintf(stderr, "Failed to get HOME directory\n");
        return 1;
    }

    search_directory(home_dir, args[1]);
    return 1;
}

