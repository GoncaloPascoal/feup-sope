// QUESTION 2b - TP2
// By Goncalo Pascoal (up201806332@fe.up.pt)

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SIZE 512

int main(int argc, char* argv[]) {
    if (argc == 2 || argc == 3) {
        int srcDesc = open(argv[1], O_RDONLY), destDesc;
        
        int stdoutDesc = dup(STDOUT_FILENO);

        if (srcDesc == -1) {
            perror("Error occurred");
            exit(1);
        }

        if (argc == 2) {
            // Write contents of source file to stdout
            destDesc = STDOUT_FILENO;
        }
        else {
            // Write contents of source file to destination with dup2() 
            destDesc = open(argv[2], O_WRONLY | O_CREAT);

            if (destDesc == -1) {
                perror("Error occurred");
                exit(1);
            }

            dup2(destDesc, STDOUT_FILENO);
        }

        char buf[BUF_SIZE];

        while (true) {
            int charsRead = read(srcDesc, &buf, BUF_SIZE);

            if (charsRead == -1) {
                perror("Error occurred");
                exit(1);
            }
            else if (charsRead == 0) {
                break;
            }

            write(STDOUT_FILENO, &buf, charsRead);
        }

        if (argc == 3) {
            dup2(stdoutDesc, STDOUT_FILENO);
        }
    }
    else {
        char prompt[] = "Usage: p2b <file> or p2b <file1> <file2>\n";
        write(STDOUT_FILENO, &prompt, strlen(prompt));
    }

    return 0;
}