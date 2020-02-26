// QUESTION 1 - TP2
// By Goncalo Pascoal (up201806332@fe.up.pt)

#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define MAX_PWD_LEN 25

int main() {
    char password[MAX_PWD_LEN + 1];
    char echo = '*';

    char prompt[] = "Password: ";
    write(STDOUT_FILENO, prompt, strlen(prompt));

    struct termios originalTerm, modifiedTerm;
    tcgetattr(STDOUT_FILENO, &originalTerm);

    modifiedTerm = originalTerm;
    modifiedTerm.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL | ICANON);

    tcsetattr(STDOUT_FILENO, TCSAFLUSH, &modifiedTerm);

    char input = 0;
    size_t i = 0;

    while (true) {
        read(STDIN_FILENO, &input, 1);

        if (input == '\n') {
            break;
        }

        if (i < MAX_PWD_LEN) {
            write(STDOUT_FILENO, &echo, 1);
            password[i++] = input;
        }
    }
    
    password[i] = 0;

    tcsetattr(STDOUT_FILENO, TCSANOW, &originalTerm);

    write(STDOUT_FILENO, "\n", 1);
    write(STDOUT_FILENO, prompt, strlen(prompt));
    write(STDOUT_FILENO, password, strlen(password));
    write(STDOUT_FILENO, "\n", 1);

    return 0;
}