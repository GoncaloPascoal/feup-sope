
#include <stdio.h>
#include <string.h>

#define BUF_SIZE 512

int main() {
    char command[BUF_SIZE];
    
    fgets(command, BUF_SIZE, stdin);

    char* token = strtok(command, " ");
    while (token) {
        puts(token);
        token = strtok(NULL, " ");
    }

    return 0;
}