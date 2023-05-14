#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "rmdir.h"

int lsh_rmdir(char **args) {
    struct stat fileStat;
    if (stat(args[1], &fileStat) == -1) {
        perror("lsh");
        return 1;
    }
    if (S_ISDIR(fileStat.st_mode)) {
        if (access(args[1], W_OK) != -1) {
            if (rmdir(args[1]) == -1) {
                perror("lsh");
                return 1;
            }
            return 1;
        }
        else {
            fprintf(stderr, "lsh: cannot remove '%s': Permission denied\n", args[1]);
            return 1;
        }
    }
    else {
        fprintf(stderr, "lsh: '%s' is not a directory\n", args[1]);
        return 1;
    }
}

