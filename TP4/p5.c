#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

void handler(int signo) {
    int status;
    pid_t pid = waitpid(-1, &status, WNOHANG);

    while (pid > 0) {
        printf("PARENT: child with PID=%d terminated with exit code %d\n", 
            pid, WEXITSTATUS(status));
        
        pid = waitpid(-1, &status, WNOHANG);
    }
}

int main() {
    pid_t pid;
    int i, n, status;

    struct sigaction action;
    
    sigemptyset(&action.sa_mask);
    // action.sa_handler = SIG_IGN; // ignore SIGCHLD
    action.sa_handler = handler;
    action.sa_flags = 0;
    
    sigaction(SIGCHLD, &action, NULL);

    for (i = 1; i <= 10; ++i) {
        pid = fork();

        if (pid == 0) {
            printf("CHILD no. %d (PID=%d) working...\n", i, getpid());
            sleep(15);
            printf("CHILD no. %d (PID=%d) exiting...\n", i, getpid());
            exit(0);
        }
    }

    for (i = 1; i <= 4; ++i) {
        printf("PARENT: working hard (task no. %d)...\n", i);
        n = 20; while ((n = sleep(n)) != 0);
        printf("PARENT: end of task no. %d\n", i);
    }

    exit(0);
}