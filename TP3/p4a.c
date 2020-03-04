#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>

int main() {
    pid_t pid;
    char str[32];

    pid = fork();

    switch (pid) {
    case -1:
        perror("fork");
        break;
    case 0: // child
        strcpy(str, "Hello ");
        write(STDOUT_FILENO, str, strlen(str));
        break;
    default: // parent
        wait(NULL);
        strcpy(str, "world!\n");
        write(STDOUT_FILENO, str, strlen(str));
        break;
    }

    return 0;
}