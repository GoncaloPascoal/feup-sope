#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 64

int main() {
    int pipeFD[2];

    if (pipe(pipeFD) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        char buf1[BUF_SIZE], buf2[BUF_SIZE];
        
        scanf("%s%s", buf1, buf2);

        write(pipeFD[WRITE], buf1, BUF_SIZE);
        write(pipeFD[WRITE], buf2, BUF_SIZE);

        wait(NULL);
    }
    else if (pid == 0) {
        char buf1[BUF_SIZE], buf2[BUF_SIZE];

        read(pipeFD[READ], buf1, BUF_SIZE);
        read(pipeFD[READ], buf2, BUF_SIZE);

        int a = atoi(buf1);
        int b = atoi(buf2);

        printf("%d + %d = %d\n", a, b, a + b);
        printf("%d - %d = %d\n", a, b, a - b);
        printf("%d * %d = %d\n", a, b, a * b);

        if (b != 0)
            printf("%d / %d = %f\n", a, b, (float)a / b);
        else
            printf("%d / %d = undefined (can't divide by 0)\n", a, b);
    }
    else {
        perror("fork");
        exit(1);
    }

    exit(0);
}