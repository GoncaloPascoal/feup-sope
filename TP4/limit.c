#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

static pid_t pid;

void intHandler(int signo) {
    kill(pid, SIGKILL);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s t prog [prog_args...]\n", argv[0]);
        exit(1);
    }

    struct sigaction action;

    sigemptyset(&action.sa_mask);
    action.sa_handler = intHandler;
    action.sa_flags = 0;

    sigaction(SIGALRM, &action, NULL);

    pid = fork();

    if (pid == 0) { // Child
        execvp(argv[2], argv + 2);
        perror("execvp");
        exit(1);
    }
    else { // Parent
        alarm(atoi(argv[1]));

        int status;
        wait(&status);
    }

    exit(0);
}