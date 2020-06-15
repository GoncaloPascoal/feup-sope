#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>

#include "p7_shared.h"

int main() {
    if (mkfifo("/tmp/fifo_req", 0644) < 0) {
        perror("mkfifo");
        exit(1);
    }

    if (mkfifo("/tmp/fifo_ans", 0644) < 0) {
        perror("mkfifo");
        unlink("/tmp/fifo_req");
        exit(1);
    }

    int fdReq, fdAns;

    if ((fdReq = open("/tmp/fifo_req", O_RDONLY)) < 0 || (fdAns = open("/tmp/fifo_ans", O_WRONLY)) < 0) {
        perror("open");
        unlink("/tmp/fifo_req");
        unlink("/tmp/fifo_ans");
        exit(1);
    }

    Request request;
    Result results[NUM_OPS];

    ssize_t bytesRead;

    while ((bytesRead = read(fdReq, &request, sizeof(Request))) >= 0) {
        if (bytesRead > 0) {
            if (request.a == 0 && request.b == 0) break;

            for (size_t i = 0; i < 3; ++i) {
                results[i].type = INT;
            }

            results[3].type = request.b == 0 ? INVALID : FLOAT;

            results[0].intResult = request.a + request.b;
            results[1].intResult = request.a - request.b;
            results[2].intResult = request.a * request.b;
            
            if (results[3].type != INVALID) {
                results[3].floatResult = request.a / (float) request.b;
            }

            write(fdAns, &results, sizeof(Result) * NUM_OPS);
        }
    }

    close(fdReq);
    close(fdAns);

    unlink("/tmp/fifo_req");
    unlink("/tmp/fifo_ans");

    exit(0);
}