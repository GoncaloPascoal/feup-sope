#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>


int main(int argc, char* argv[]) {
    DIR* dirp;
    struct dirent* direntp;
    struct stat stat_buf;
    char* str;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s dir_name\n", argv[0]);
        exit(1);
    }

    if ((dirp = opendir(argv[1])) == NULL) {
        perror(argv[1]);
        exit(2);
    }

    char* path;
    
    while ((direntp = readdir(dirp)) != NULL) {
        path = (char*) malloc(sizeof(char) * (strlen(argv[1]) + strlen(direntp->d_name) + 2));
        sprintf(path, "%s%s%s", argv[1], "/", direntp->d_name);

        if (lstat(path, &stat_buf) != 0) {
            perror("lstat failed");
        }

        free(path);

        if (S_ISREG(stat_buf.st_mode)) {
            str = "regular";
        }
        else if (S_ISDIR(stat_buf.st_mode)) {
            str = "directory";
        }
        else {
            str = "other";
        }

        printf("%-25s - %-10s | %lu | %lu\n", direntp->d_name, str, direntp->d_ino, stat_buf.st_size);
    }

    closedir(dirp);
    exit(0);
}