#include <pthread.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define BUF_SIZE 512

typedef struct {
    char* fileName;
    const char* srcPath;
    const char* destPath;
} CopyFileInfo;

void* copyFile(void* arg) {
    CopyFileInfo* info = (CopyFileInfo*) arg;

    char* srcFilePath = malloc(strlen(info->srcPath) + strlen(info->fileName) + 2);
    sprintf(srcFilePath, "%s/%s", info->srcPath, info->fileName);

    char* destFilePath = malloc(strlen(info->destPath) + strlen(info->fileName) + 2);
    sprintf(destFilePath, "%s/%s", info->destPath, info->fileName);

    int fdSrc = open(srcFilePath, O_RDONLY);
    int fdDest = open(destFilePath, O_WRONLY | O_CREAT | O_EXCL, 0644);

    free(srcFilePath);
    free(destFilePath);
    free(info->fileName);
    free(info);

    if (fdSrc < 0 || fdDest < 0) {
        perror("open");
        return NULL;
    }

    char buffer[BUF_SIZE];
    ssize_t charsRead;

    while ((charsRead = read(fdSrc, &buffer, BUF_SIZE)) > 0) {
        write(fdDest, &buffer, charsRead);
    }

    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: %s dir_src dir_dest\n", argv[0]);
        exit(1);
    }

    DIR* src = opendir(argv[1]);
    struct dirent* direntPtr;

    if (src == NULL) {
        perror("opendir");
        exit(1);
    }

    pthread_t tid;

    while ((direntPtr = readdir(src)) != NULL) {
        if (direntPtr->d_type == DT_REG) {
            CopyFileInfo* info = malloc(sizeof(CopyFileInfo));

            info->fileName = malloc(strlen(direntPtr->d_name) + 1);
            strcpy(info->fileName, direntPtr->d_name);

            info->srcPath = argv[1];
            info->destPath = argv[2];

            if (pthread_create(&tid, NULL, copyFile, info) != 0) {
                perror("pthread_create");
            }
            else if (pthread_detach(tid) != 0) {
                perror("pthread_detach");
            }
        }
    }

    pthread_exit(NULL);
}
