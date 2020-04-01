#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

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

    pid_t pid = fork();

    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    }
    else if (pid == 0) {
        close(pipeFD1[READ]);
        dup2(pipeFD1[WRITE], STDOUT_FILENO);

        execlp("ls", "ls", argv[1], "-laR", NULL);

        perror("execlp");
        exit(1);
    }
    else {
        perror("fork");
        exit(1);
    }

    int pipeFD2[2];

    if (pipe(pipeFD2) < 0) {
        perror("pipe");
        exit(1);
    }

    close(pipeFD1[WRITE]);
    pid = fork();

    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    }
    else if (pid == 0) {
        close(pipeFD2[READ]);
        dup2(pipeFD1[READ], STDIN_FILENO);
        dup2(pipeFD2[WRITE], STDOUT_FILENO);

        execlp("grep", "grep", argv[2], NULL);

        perror("execlp");
        exit(1);
    }
    else {
        perror("fork");
        exit(1);
    }

    close(pipeFD2[WRITE]);
    pid = fork();

    if (pid > 0) {
        int status;
        waitpid(pid, &status, 0);
    }
    else if (pid == 0) {
        dup2(pipeFD2[READ], STDIN_FILENO);

        execlp("sort", "sort", NULL);

        perror("execlp");
        exit(1);
    }
    else {
        perror("fork");
        exit(1);
    }

    return 0;
}