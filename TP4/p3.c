#define _XOPEN_SOURCE 700   // Allows usage of some GNU/Linux standard functions and structures

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

int v = 0;
bool increasing = true;

void sig_handler(int signo) {
    switch (signo) {
    case SIGUSR1:
        increasing = true;
        break;
    case SIGUSR2:
        increasing = false;
        break;
    default:
        break;
    }
}

int main() {
    struct sigaction action;

    action.sa_handler = sig_handler;

    if (sigaction(SIGUSR1, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGUSR1 handler.\n");
        exit(1);
    }

    if (sigaction(SIGUSR2, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGUSR2 handler.\n");
        exit(1);
    }

    while (true) {
        printf("%d\n", v);

        if (increasing)
            ++v;
        else
            --v;

        sleep(1);
    }
}
