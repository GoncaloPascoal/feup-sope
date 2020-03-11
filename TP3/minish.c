#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>

#define BUF_SIZE    256
#define MAX_TOKENS  16

int main() {
    char prompt[] = "minish > ";
    char quit[] = "quit";
    char buf[BUF_SIZE];

    char* tokens[MAX_TOKENS];

    while (true) {
        write(STDOUT_FILENO, prompt, strlen(prompt));

        int charsRead;

        if ((charsRead = read(STDIN_FILENO, buf, BUF_SIZE)) == -1) {
            perror("read");
            exit(1);
        }

        // Remove newline from end of buffer
        buf[charsRead - 1] = 0;

        if (strcmp(buf, quit) == 0)
            break;

        int numTokens = 0;
        char* token = strtok(buf, " ");

        while (token != NULL && numTokens < MAX_TOKENS - 1) {
            tokens[numTokens] = (char*) malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(tokens[numTokens], token);

            ++numTokens;
            token = strtok(NULL, " ");
        }

        tokens[numTokens] = NULL;
        
        pid_t pid = fork();

        if (pid > 0) { // Parent
            int stat;
            wait(&stat);
        }
        else if (pid == 0) { // Child
            execvp(tokens[0], tokens);
            printf("Fatal error: command not executed.\n");
            exit(1);
        }
        else {
            perror("fork");
            exit(1);
        }

        for (int i = 0; i < numTokens; ++i) {
            free(tokens[i]);
        }
    }

    exit(0);
}