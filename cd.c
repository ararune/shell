#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "cd.h"

int lsh_cd(char **args) {
    // Check if a directory was provided
    if (args[1] == NULL) {
        fprintf(stderr, "lsh: expected argument to \"cd\"\n");
        return 1;
    }

    // Determine the target directory
    char* target_dir = NULL;
    if (strcmp(args[1], "~") == 0) {
        target_dir = getenv("HOME");
        if (target_dir == NULL) {
            fprintf(stderr, "lsh: failed to get home directory\n");
            return 1;
        }
    } else {
        target_dir = args[1];
    }

    // Attempt to change directory to the target directory
    if (chdir(target_dir) != 0) {
        fprintf(stderr, "lsh: failed to change directory to %s\n", target_dir);
        return 1;
    }

    return 1;
}

