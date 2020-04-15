#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

#define STDERR      2

size_t n = 50000;

void* thrfunc(void* arg) {
    size_t* charsWritten = malloc(sizeof(size_t));
    *charsWritten = 0;

    fprintf(stderr, "Starting thread %s\n", (char*) arg);
    
    while (n > 0) {
        n--;
        ++(*charsWritten);

        write(STDERR, arg, 1);
    }

    return charsWritten;
}

int main() {
    pthread_t ta, tb;

    pthread_create(&ta, NULL, thrfunc, "1");
    pthread_create(&tb, NULL, thrfunc, "2");

    void* taReturn;
    void* tbReturn;

    pthread_join(ta, &taReturn);
    pthread_join(tb, &tbReturn);

    size_t charsWritten = *((size_t*) taReturn) + *((size_t*) tbReturn);
    free(taReturn);
    free(tbReturn);

    fprintf(stderr, "Total chars written: %lu\n", charsWritten);

    return 0;
}