#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s programs...\n", argv[0]);
        exit(1);
    }

    pid_t* pids = malloc(sizeof(pid_t) * (argc - 1));

    for (size_t i = 1; i < argc; ++i) {
        pids[i - 1] = fork();

        if (pids[i - 1] == 0) {
            execlp(argv[i], argv[i], NULL);
            perror("execlp");
            exit(1);
        }
    }

    int status;
    pid_t pid;

    while ((pid = wait(&status)) != -1) {
        printf("Process with pid = %d exited with status %d\n", pid, WEXITSTATUS(status));

        if (status != 0) {
            // Send SIGKILL to all other processes still in execution
            for (size_t i = 0; i < argc - 1; ++i) {
                if (pids[i] != -1 && pids[i] != pid) {
                    kill(pids[i], SIGKILL);
                }
            }
            exit(1);
        }
        else {
            for (size_t i = 0; i < argc - 1; ++i) {
                if (pids[i] == pid) {
                    pids[i] = -1;
                    break;
                }
            }
        }
    }

    exit(0);
}