
#include <stdio.h>
#include <stdlib.h>

void atexit1() {
    printf("Executing exit handler 1.\n");
}

void atexit2() {
    printf("Executing exit handler 2.\n");
}

int main() {
    atexit(atexit1);
    atexit(atexit2);

    printf("Main done!\n");
    return 0;
}