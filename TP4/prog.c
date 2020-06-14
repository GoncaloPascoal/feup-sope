#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s message\n", argv[0]);
        exit(1);
    }

    while (true) {
        printf("%s\n", argv[1]);
        sleep(5);
    }

    return 0;
}