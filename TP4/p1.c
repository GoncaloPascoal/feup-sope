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
    if (signal(SIGINT, sigint_handler) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler.\n");
        exit(1);
    }

    if (signal(SIGUSR1, sigusr1_handler) < 0) {
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
