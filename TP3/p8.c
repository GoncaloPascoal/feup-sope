#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc, char* argv[], char* envp[]) {
    pid_t pid;

    if (argc != 2 && argc != 3) {
        printf("Usage: %s dirname or %s dirname filename\n", argv[0], argv[0]);
        exit(1);
    }

    pid = fork();

    if (pid > 0) {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);

        int stat;

        wait(&stat);

        printf("Exit code: %d\n", WEXITSTATUS(stat));
        if (WIFEXITED(stat)) {
            printf("Child exited normally.\n");
        }
        else {
            printf("Child didn't exit normally.\n");
        }
    }
    else if (pid == 0) {
        char* args[] = {"/bin/ls", "-laR", argv[1], NULL};

        if (argc == 3) {
            // Open destination file
            int fileDes = open(argv[2], O_CREAT | O_WRONLY, 0644);

            if (fileDes < 0) {
                perror(argv[2]);
                exit(2);
            }

            // Redirect standard output
            dup2(fileDes, STDOUT_FILENO);
        }

        execve("/bin/ls", args, envp);
        printf("Command not executed!\n");
        exit(1);
    }

    exit(0);
}