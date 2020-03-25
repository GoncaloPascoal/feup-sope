#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

#define BUF_SIZE 128

enum OperationResult {
    INVALID = -1,
    INT = 0,
    FLOAT = 1
};

int main() {
    int pipeFD1[2];
    int pipeFD2[2];

    if (pipe(pipeFD1) < 0) {
        perror("pipe");
        exit(1);
    }

    if (pipe(pipeFD2) < 0) {
        perror("pipe");
        exit(1);
    }

    pid_t pid = fork();

    if (pid > 0) {
        int a, b;
        
        scanf("%d%d", &a, &b);

        write(pipeFD1[WRITE], &a, sizeof(a));
        write(pipeFD1[WRITE], &b, sizeof(b));

        const size_t NUM_OPS = 4; 
        char operations[] = {'+', '-', '*', '/'};
        enum OperationResult opResult;
        int intResult;
        float floatResult;

        for (size_t i = 0; i < NUM_OPS; ++i) {
            read(pipeFD2[READ], &opResult, sizeof(opResult));

            if (opResult == INVALID) {
                printf("%d %c %d = invalid\n", a, operations[i], b);
            }
            else if (opResult == INT) {
                read(pipeFD2[READ], &intResult, sizeof(intResult));
                printf("%d %c %d = %d\n", a, operations[i], b, intResult);
            }
            else if (opResult == FLOAT) {
                read(pipeFD2[READ], &floatResult, sizeof(floatResult));
                printf("%d %c %d = %f\n", a, operations[i], b, floatResult);
            }
        }

        wait(NULL);
    }
    else if (pid == 0) {
        int a, b;

        read(pipeFD1[READ], &a, sizeof(a));
        read(pipeFD1[READ], &b, sizeof(b));

        enum OperationResult opResult = INT;
        int intResult;
        float floatResult;

        intResult = a + b;

        write(pipeFD2[WRITE], &opResult, sizeof(opResult));
        write(pipeFD2[WRITE], &intResult, sizeof(intResult));

        intResult = a - b;

        write(pipeFD2[WRITE], &opResult, sizeof(opResult));
        write(pipeFD2[WRITE], &intResult, sizeof(intResult));

        intResult = a * b;

        write(pipeFD2[WRITE], &opResult, sizeof(opResult));
        write(pipeFD2[WRITE], &intResult, sizeof(intResult));

        if (b != 0) {
            floatResult = (float)a / b;
            opResult = FLOAT;

            write(pipeFD2[WRITE], &opResult, sizeof(opResult));
            write(pipeFD2[WRITE], &floatResult, sizeof(floatResult));
        }
        else {
            opResult = INVALID;
            write(pipeFD2[WRITE], &opResult, sizeof(opResult));
        }
    }
    else {
        perror("fork");
        exit(1);
    }

    exit(0);
}