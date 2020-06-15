#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "p8_shared.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s username\n", argv[0]);
        exit(1);
    }

    int fd = open(FIFO_PATH, O_WRONLY | O_APPEND | O_NONBLOCK);

    if (fd < 0) {
        perror("open");
        exit(1);
    }

    write(fd, argv[1], strlen(argv[1]) + 1);

    close(fd);
    exit(0);
}