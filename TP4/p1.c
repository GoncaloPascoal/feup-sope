#define _XOPEN_SOURCE 700   // Allows usage of some GNU/Linux standard functions and structures

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

unsigned int seconds_left = 30;

void sigint_handler(int signo) {
    printf("In SIGINT handler...\n");
}

void sigusr1_handler(int signo) {
    printf("In SIGUSR1 handler...\n");
}

int main() {
    struct sigaction intAct, usr1Act;

    intAct.sa_handler = sigint_handler;
    usr1Act.sa_handler = sigusr1_handler;

    if (sigaction(SIGINT, &intAct, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler.\n");
        exit(1);
    }

    if (sigaction(SIGUSR1, &usr1Act, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGUSR1 handler.\n");
        exit(1);
    }

    printf("Sleeping for 30 seconds...\n");
    while (seconds_left > 0) {
        seconds_left = sleep(seconds_left);
    }
    printf("Waking up...\n");

    exit(0);
}
