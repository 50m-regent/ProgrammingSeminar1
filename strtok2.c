#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFSIZE 10

int main () {
    int x, y, z;
    char buf[BUFSIZE];

    while (gets(buf) != NULL) {
        if (buf[0] == '#') continue;

        x = atoi(strtok(buf,  ","));
        y = atoi(strtok(NULL, ","));
        z = atoi(strtok(NULL, "\0"));

        printf("%3d,%3d,%3d\n", x, y, z);
    }
    return EXIT_SUCCESS;
}