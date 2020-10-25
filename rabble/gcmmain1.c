#include <stdio.h>
#include <stdlib.h>
#include "gcm.h"

int main(int argc, char **argv) {
    int a, b, g;

    if (argc != 3) {
        printf("Usage: %s a b\n", argv[0]);
        return EXIT_FAILURE;
    }

    a = atoi(argv[1]);
    b = atoi(argv[2]);
    g = gcm(ABS(a), ABS(b));

    printf("gcm(%d, %d) = %d\n", a, b, g);

    return EXIT_SUCCESS;
}