#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "rm.h"

int lsh_rm(char **args) {
    //Checking that the file exists and can be accessed
    struct stat fileStat;
    if (stat(args[1], &fileStat) == -1) {
        perror("lsh");
        return 1;
    }
    // Checking that the file is writable
    if (access(args[1], W_OK) != -1) {
        if (remove(args[1]) == -1) {
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

