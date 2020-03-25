#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 128

typedef struct {
    int a, b;
} OperationValues;

int main() {
    int pipeFD[2];

    if (pipe(pipeFD) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        OperationValues vals;
        
        scanf("%d%d", &vals.a, &vals.b);

        write(pipeFD[WRITE], (char*) &vals, sizeof(OperationValues));

        wait(NULL);
    }
    else if (pid == 0) {
        OperationValues vals;

        read(pipeFD[READ], &vals, sizeof(OperationValues));

        printf("%d + %d = %d\n", vals.a, vals.a, vals.a + vals.b);
        printf("%d - %d = %d\n", vals.a, vals.b, vals.a - vals.b);
        printf("%d * %d = %d\n", vals.a, vals.b, vals.a * vals.b);

        if (vals.b != 0)
            printf("%d / %d = %f\n", vals.a, vals.b, (float)vals.a / vals.b);
        else
            printf("%d / %d = undefined (can't divide by 0)\n", vals.a, vals.b);
    }
    else {
        perror("fork");
        exit(1);
    }

    exit(0);
}