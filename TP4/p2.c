#define _XOPEN_SOURCE 700   // Allows usage of some GNU/Linux standard functions and structures

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

void sigint_handler(int signo) {
    printf("Entering SIGINT handler ...\n");
    sleep(10);
    printf("Exiting SIGINT handler ...\n"); 
}

void sigterm_handler(int signo)  {
    printf("Entering SIGTERM handler...\n");
    printf("Exiting SIGTERM handler...\n");
}

int main() {
    struct sigaction action;

    action.sa_handler = sigint_handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;

    if (sigaction(SIGINT, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGINT handler.\n");
        exit(1);
    }

    action.sa_handler = sigterm_handler;

    if (sigaction(SIGTERM, &action, NULL) < 0) {
        fprintf(stderr, "Unable to install SIGTERM handler.\n");
        exit(1);
    }

    printf("Try me with CTRL-C...\n");
    while (true) pause();

    exit(0);
}