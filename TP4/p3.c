#define _XOPEN_SOURCE 700   // Allows usage of some GNU/Linux standard functions and structures

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <wait.h>

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
    // Initialize random number generator with time seed
    srand(time(NULL));

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

    pid_t pid = fork();

    if (pid > 0) { // Parent
        while (waitpid(pid, NULL, WNOHANG) == 0) {
            bool usr1 = rand() % 2;
            if (usr1)
                kill(pid, SIGUSR1);
            else
                kill(pid, SIGUSR2);
            sleep(1);
        }
    }
    else if (pid == 0) { // Child
        unsigned int numbersPrinted = 0;

        while (numbersPrinted < 50) {
            printf("%d\n", v);
            if (increasing)
                ++v;
            else
                --v;
            sleep(1);
            ++numbersPrinted;
        }
    }
    else { // Error occurred
        perror("Fork");
        exit(1);
    }

    exit(0);
}
