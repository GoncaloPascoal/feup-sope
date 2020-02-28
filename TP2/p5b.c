#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    char* text1 = "CCCCC";
    char* text2 = "DDDDD";

    fd = open("f1.txt", O_WRONLY | O_SYNC, 0600);
    write(fd, text1, strlen(text1));
    write(fd, text2, strlen(text2));

    close(fd);

    return 0;
}