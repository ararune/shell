#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "touch.h"

int lsh_touch(char **args)
{
    // Open the file with O_CREAT flag to create a new file if it does not exist.
    int fd = open(args[1], O_CREAT, S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IROTH);

    if (fd == -1) {
        perror("lsh");
    } else {
        close(fd); 
    }

    return 1; 
}

