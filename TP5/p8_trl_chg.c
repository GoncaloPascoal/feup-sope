#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdbool.h>
#include <signal.h>

#include "p8_shared.h"

#define DURATION_SECONDS 120
#define BUF_INITIAL_SIZE 32

static bool finished = false;

void sigHandler(int signo) {
    finished = true;
}

int main() {
    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_handler = sigHandler;
    action.sa_flags = 0;

    sigaction(SIGALRM, &action, NULL);
    alarm(DURATION_SECONDS);

    if (mkfifo(FIFO_PATH, 0644) < 0) {
        perror("mkfifo");
        exit(1);
    }

    int fd = open(FIFO_PATH, O_RDONLY);

    if (fd < 0) {
        perror("open");
        unlink(FIFO_PATH);
        exit(1);
    }

    bool readCharacter;
    char c;

    size_t bufSize = BUF_INITIAL_SIZE;
    char* buf = malloc(bufSize);
    size_t messageLength = 0;

    while (!finished) {
        readCharacter = (read(fd, &c, 1) > 0);

        if (readCharacter) {
            buf[messageLength++] = c;

            if (messageLength == bufSize) {
                bufSize *= 2;
                buf = realloc(buf, bufSize);
            }

            if (c == '\0') {
                printf("CHEGOU %s", buf);

                free(buf);
                bufSize = BUF_INITIAL_SIZE;
                messageLength = 0;
                buf = malloc(bufSize);
            }
        }
    }

    free(buf);

    unlink(FIFO_PATH);
    exit(0);
}