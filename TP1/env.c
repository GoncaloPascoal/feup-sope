
#include <stdio.h>
#include <stdlib.h>

int main() {
    char envVar[] = "USER_NAME";
    char* name = getenv(envVar);

    printf("Hello %s.\n", name);

    return 0;
}