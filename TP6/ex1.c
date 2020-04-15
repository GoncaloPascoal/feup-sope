#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#define STDERR      2
#define NUM_ITER    10000

void* thrfunc(void* arg) {
    int i;

    fprintf(stderr, "Starting thread %s\n", (char*) arg);
    for (i = 1; i <= NUM_ITER; i++) write(STDERR, arg, 1);
    return NULL;
}

int main() {
    pthread_t ta, tb;
    char arg = '1';

    pthread_create(&ta, NULL, thrfunc, &arg);

    arg = '2';
    pthread_create(&tb, NULL, thrfunc, &arg);

    pthread_join(ta, NULL);
    pthread_join(tb, NULL);

    return 0;
}