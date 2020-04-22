#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ELEMS   10000000
#define MAX_THREADS 100
#define min(a, b)   (a) < (b) ? (a) : (b)

int npos;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
int buf[MAX_ELEMS], pos = 0, val = 0;

void* fill(void* nr) {
    while (1) {
        pthread_mutex_lock(&mut);
        if (pos >= npos) {
            pthread_mutex_unlock(&mut);
            return NULL;
        }
        buf[pos] = val;
        ++pos; ++val;
        pthread_mutex_unlock(&mut);
        *(int*)nr += 1;
    }
}

void* verify(void* arg) {
    for (int k = 0; k < npos; ++k) {
        if (buf[k] != k) {
            printf("ERROR: buf[%d] = %d\n", k, buf[k]);
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    int k, nthr, count[MAX_THREADS];
    pthread_t tidf[MAX_THREADS], tidv;
    int total;

    if (argc != 3) {
        printf("Usage: %s <nr_pos> <nr_thrs>\n", argv[0]);
        return 1;
    }

    npos = min(atoi(argv[1]), MAX_ELEMS);
    nthr = min(atoi(argv[2]), MAX_ELEMS);

    total = 0;

    for (k = 0; k < nthr; ++k) {
        count[k] = 0;
        pthread_create(&tidf[k], NULL, fill, &count[k]);
    }

    total = 0;

    for (k = 0; k < nthr; ++k) {
        pthread_join(tidf[k], NULL);
        printf("count[%d] = %d\n", k, count[k]);
        total += count[k];
    }
    printf("total count = %d\n", total);

    pthread_create(&tidv, NULL, verify, NULL);
    pthread_join(tidv, NULL);

    return 0;
}
