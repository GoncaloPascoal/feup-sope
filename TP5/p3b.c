#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 512

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int pipeFD[2];

    if (pipe(pipeFD) < 0) {
        perror("pipe");
        exit(1);
    }

    int fd;

    if ((fd = open(argv[1], O_RDONLY)) < 0) {
        perror("open");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) { // Parent
        close(pipeFD[READ]);
        dup2(pipeFD[WRITE], STDOUT_FILENO);

        execlp("cat", "cat", argv[1], NULL);
        perror("execlp");
        exit(1);
    }
    else if (pid == 0) { // Child
        close(pipeFD[WRITE]);
        dup2(pipeFD[READ], STDIN_FILENO);

        execlp("sort", "sort", NULL);
        perror("execlp");
        exit(1);
    }
    else {
        perror("fork");
        exit(1);
    }

    exit(0);
}
