#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

#include "p7_shared.h"

int main() {
    int fdReq, fdAns;

    printf("going to open\n");

    if ((fdReq = open("/tmp/fifo_req", O_APPEND)) < 0 || (fdAns = open("/tmp/fifo_ans", O_RDONLY)) < 0) {
        perror("open");
        exit(1);
    }

    printf("going to scanf\n");

    Request request;
    Result results[NUM_OPS];

    scanf("%d%d", &request.a, &request.b);
    write(fdReq, &request, sizeof(Request));

    printf("wrote into buffer\n");

    read(fdAns, &results, sizeof(Result) * NUM_OPS);

    printf("read from buffer\n");

    Result* currentResult;
    for (size_t i = 0; i < NUM_OPS; ++i) {
        currentResult = results + i;

        printf("%d %c %d = ", request.a, operations[i], request.b);

        switch (currentResult->type) {
        case INT:
            printf("%d\n", currentResult->intResult);
            break;
        case FLOAT:
            printf("%f\n", currentResult->floatResult);
            break;
        case INVALID:
            printf("invalid operation\n");
            break;
        default:
            fprintf(stderr, "Error: invalid result type.\n");
            break;
        }
    }

    close(fdReq);
    close(fdAns);

    return 0;
}