#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    float a, b;
} Operands;

void* add(void* args) {
    float* result = malloc(sizeof(float));
    *result = (*(Operands*) args).a + (*(Operands*) args).b;
    pthread_exit(result);
}

void* subtract(void* args) {
    float* result = malloc(sizeof(float));
    *result = (*(Operands*) args).a - (*(Operands*) args).b;
    pthread_exit(result);
}

void* multiply(void* args) {
    float* result = malloc(sizeof(float));
    *result = (*(Operands*) args).a * (*(Operands*) args).b;
    pthread_exit(result);
}

void* divide(void* args) {
    float* result = malloc(sizeof(float));
    *result = (*(Operands*) args).a / (*(Operands*) args).b;
    pthread_exit(result);
}

int main() {
    pthread_t threads[4];
    Operands operands;

    scanf("%f%f", &operands.a, &operands.b);

    pthread_create(&threads[0], NULL, add, &operands);
    pthread_create(&threads[1], NULL, subtract, &operands);
    pthread_create(&threads[2], NULL, multiply, &operands);
    pthread_create(&threads[3], NULL, divide, &operands);

    char operations[4] = {'+', '-', '*', '/'};

    for (size_t i = 0; i < 4; ++i) {
        void* retVal;
        pthread_join(threads[i], &retVal);

        printf("%f %c %f = %f\n", operands.a, operations[i], operands.b, *(float*) retVal);

        free(retVal);
    }

    pthread_exit(0);
}