
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUF_SIZE 512
#define MAX_TOKENS 64

int main() {
    char command[BUF_SIZE];
    char* tokens[MAX_TOKENS];
    
    fgets(command, BUF_SIZE, stdin);

    // Trim newline at the end of the command
    memmove(&command[strlen(command) - 1], &command[strlen(command)], 1);

    // Divides the string into tokens and stores them in a string array
    char* token = strtok(command, " ");
    size_t idx = 0;

    while (token) {
        tokens[idx] = (char*) malloc((strlen(token) + 1) * sizeof(char));
        strcpy(tokens[idx], token);
        ++idx;

        token = strtok(NULL, " ");
    }

    // Prints the tokens and frees dynamically allocated memory
    for (size_t i = 0; i < idx; ++i) {
        puts(tokens[i]);
        free(tokens[i]);
    }

    return 0;
}