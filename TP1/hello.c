
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 2) {
        printf("Hello %s.\n", argv[1]);
    }
    else if (argc == 3) {
        size_t numTimes = atoi(argv[2]);
        for (size_t i = 0; i < numTimes; ++i) {
            printf("Hello %s.\n", argv[1]);
        }
    }
    else {
        printf("Hello world.\n");
    }
    
    return 0;
}