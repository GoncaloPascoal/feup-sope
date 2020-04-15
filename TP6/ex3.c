#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 10

void* printHello(void* threadNum) {
    printf("Hello from the thread no. %d!\n", *((int*) threadNum));
    free(threadNum);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];

    for (int t = 0; t < NUM_THREADS; ++t) {
        printf("Creating thread %d\n", t);

        int* arg = malloc(sizeof(int));
        *arg = t;

        pthread_create(&threads[t], NULL, printHello, arg);
    }

    pthread_exit(0);
}