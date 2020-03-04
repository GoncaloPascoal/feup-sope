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
    case 0: // child #1
        pid = fork();

        switch (pid) {
            case -1:
                perror("fork");
                break;
            case 0: // child #2
                strcpy(str, "Hello ");
                write(STDOUT_FILENO, str, strlen(str));
                break;
            default: // child #1
                wait(NULL);
                strcpy(str, "my ");
                write(STDOUT_FILENO, str, strlen(str));
                break;
        }
        break;
    default: // parent
        wait(NULL);
        strcpy(str, "friends!\n");
        write(STDOUT_FILENO, str, strlen(str));
        break;
    }

    return 0;
}