#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>

#define READ 0
#define WRITE 1

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s <dir> <arg>\n", argv[0]);
        exit(1);
    }

    int pipeFD1[2];

    if (pipe(pipeFD1) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid1 = fork();

    if (pid1 > 0) { // ls <dir> -laR
        close(pipeFD1[READ]);
        dup2(pipeFD1[WRITE], STDOUT_FILENO);

        execlp("ls", "ls", argv[1], "-laR", NULL);

        perror("execlp");
        exit(1);
    }
    else if (pid1 == 0) {
        int pipeFD2[2];

        if (pipe(pipeFD2) < 0) {
            perror("pipe");
            exit(1);
        }

        pid_t pid2 = fork();

        if (pid2 > 0) { // grep <arg>
            close(pipeFD1[WRITE]);
            close(pipeFD2[READ]);
            dup2(pipeFD2[WRITE], STDOUT_FILENO);
            dup2(pipeFD1[READ], STDIN_FILENO);

            execlp("grep", "grep", argv[2], NULL);

            perror("execlp");
            exit(1);
        }
        else if (pid2 == 0) { // sort
            close(pipeFD2[WRITE]);
            dup2(pipeFD2[READ], STDIN_FILENO);

            execlp("sort", "sort", NULL);

            perror("execlp");
            exit(1);
        }
        else {
            perror("fork");
            exit(1);
        }
    }
    else {
        perror("fork");
        exit(1);
    }

    return 0;
}