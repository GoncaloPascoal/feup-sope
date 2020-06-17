#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct {
    const char* filePath;
    const char* pattern;
} GrepInfo;

// TODO: Fill an array with line numbers instead of printing
int grepFile(const char* filePath, const char* pattern) {
    FILE* filePtr = fopen(filePath, "r");

    if (filePtr == NULL) {
        perror("fopen");
        return 1;
    }

    char* line = NULL;
    ssize_t numBytes = 0;
    unsigned int lineNum = 1;

    while(getline(&line, &numBytes, filePtr) > 0) {
        if (strstr(line, pattern) != NULL) {
            printf("Line %d in file %s\n", lineNum, filePath);
        }
        
        numBytes = 0;
        ++lineNum;

        free(line);
        line = NULL;
    }

    free(line);
    return 0;
}

void* threadFunc(void* arg) {
    GrepInfo* info = (GrepInfo*) arg;

    if (grepFile(info->filePath, info->pattern) != 0) {
        fprintf(stderr, "Error when calling grepFile\n");
    }

    free(arg);
    return NULL;
}


int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: %s pattern file1 [file2 file3...]\n", argv[0]);
        exit(1);
    }

    pthread_t tid;

    for (int i = 2; i < argc; ++i) {
        GrepInfo* arg = malloc(sizeof(GrepInfo));
        arg->filePath = argv[i];
        arg->pattern = argv[1];

        if (pthread_create(&tid, NULL, threadFunc, arg) != 0) {
            perror("pthread_create");
            free(arg);
        }
        else if (pthread_detach(tid) != 0) {
            perror("pthread_deatch");
            free(arg);
        }
    }

    pthread_exit(NULL);
}