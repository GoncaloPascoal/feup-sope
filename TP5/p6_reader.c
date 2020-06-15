#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>

int readLine(int fd, char* str);

int main() {
    int fd;
    char str[100];

    mkfifo("/tmp/myfifo", 0660);
    fd = open("/tmp/myfifo", O_RDONLY);
    while (readLine(fd, str)) printf("%s", str);
    close(fd);

    return 0;
}

int readLine(int fd, char* str) {
    int n;

    do {
        n = read(fd, str, 1);
    } while (n > 0 && *str++ != '\0');

    return (n > 0);
}
