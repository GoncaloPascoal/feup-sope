#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS 10

void* threadFunc(void* arg) {
    sleep(1);
    printf("%lu\n", (unsigned long) pthread_self());

    pthread_exit(arg);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadNums[NUM_THREADS];

    for (size_t i = 0; i < NUM_THREADS; ++i) {
        threadNums[i] = i + 1;
        
        pthread_create(&threads[i], NULL, threadFunc, &threadNums[i]);
    }

    void* returnValue;

    for (size_t i = 0; i < NUM_THREADS; ++i) {
        pthread_join(threads[i], &returnValue);
        printf("Thread %d returned %d.\n", threadNums[i], *(int*) returnValue);
    }

    pthread_exit(0);
}