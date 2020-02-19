
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define BUF_LENGTH 256

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Usage: p6a file1 file2\n");
        exit(3);
    }

    FILE *src, *dst;
    char buf[BUF_LENGTH];
    char* inFile = argv[1];
    char* outFile = argv[2];

    if ((src = fopen(inFile, "r")) == NULL) {
        printf("errno: %d\n", errno);
        exit(1);
    }

    if ((dst = fopen(outFile, "w")) == NULL) {
        printf("errno: %d\n", errno);
        exit(2);
    }

    while ((fgets(buf, BUF_LENGTH, src)) != NULL) {
        fputs(buf, dst);
    }

    fclose(src);
    fclose(dst);

    exit(0);
}
