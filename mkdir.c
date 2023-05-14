#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "mkdir.h"

int lsh_mkdir(char **args) {
    mode_t mode = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;

    if (mkdir(args[1], mode) == -1) {
        perror("lsh");
    }

    return 1;
}

