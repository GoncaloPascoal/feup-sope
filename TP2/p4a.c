// QUESTION 4a - TP2
// By Goncalo Pascoal (up201806332@fe.up.pt)

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF_SIZE 50

/**
 * @brief Reads characters from stdout and stores them in a buffer, up to a given size.
 * Ends when a newline is read.
 * @param buf       buffer to write to
 * @param bufSize   size of the buffer (including null terminator)
 * @return          length of the string
 */
size_t readToBuf(char* buf, size_t bufSize) {
    char input = 0;
    size_t i = 0;

    while (input != '\n') {
        read(STDIN_FILENO, &input, 1);

        if (i < bufSize - 1 && input != '\n') {
            buf[i++] = input;
        }
    }

    buf[i] = 0;
    return i;
}

bool isNumber(char* str) {
    size_t i = 0;
    char c;

    while ((c = str[i++]) != 0) {
        if (!isdigit(c)) {
            return false;
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    if (argc == 2) {
        int fileDesc = open(argv[1], O_WRONLY | O_CREAT);

        if (fileDesc == -1) {
            perror("Error occurred");
            exit(1);
        }

        char nameBuf[BUF_SIZE];
        char gradeBuf[BUF_SIZE];

        char namePrompt[] = "Name: ";
        char gradePrompt[] = "Grade: ";

        while (true) {
            size_t nameLen = readToBuf(nameBuf, BUF_SIZE);

            if (nameLen == 0) {
                break;
            }

            size_t gradeLen = readToBuf(gradeBuf, BUF_SIZE);

            if (gradeLen == 0) {
                break;
            }

            if (!isNumber(gradeBuf)) {
                printf("Error: grade is not a number.\n");
                exit(2);
            }

            
            write(fileDesc, &namePrompt, nameLen);
            write(fileDesc, "\n", 1);
            write(fileDesc, &gradePrompt, gradeLen);
            write(fileDesc, "\n", 1);
        }

        close(fileDesc);
    }
    else {
        char prompt[] = "Usage: p4a <file>\n";
        write(STDOUT_FILENO, &prompt, strlen(prompt));
    }

    return 0;
}