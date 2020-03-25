#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 128

int main() {
    int pipeFD[2];

    if (pipe(pipeFD) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        int a, b;
        
        scanf("%d%d", &a, &b);
        
        char buf[BUF_SIZE];
        sprintf(buf, "%d %d", a, b);

        write(pipeFD[WRITE], buf, BUF_SIZE);

        wait(NULL);
    }
    else if (pid == 0) {
        char buf[BUF_SIZE];
        read(pipeFD[READ], buf, BUF_SIZE);

        int a, b;
        sscanf(buf, "%d%d", &a, &b);

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