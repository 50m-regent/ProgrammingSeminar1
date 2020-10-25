#include <stdio.h>
#include <stdlib.h>

#define MSIZE 9

void setmap(int m[MSIZE][MSIZE]) {
    int x, y;

    for (y = 0; y < MSIZE; y++) {
        for (x = 0; x < MSIZE; x++) {
            m[y][x] = (x + 1) * (y + 1);
        }
    }
}

void dispmap(int m[MSIZE][MSIZE]) {
    int x, y;

    for (y = 0; y < MSIZE; y++) {
        for (x = 0; x < MSIZE; x++) {
            printf("%3d", m[y][x]);
        }
        printf("\n");
    }
}

int main() {
    int map[MSIZE][MSIZE];

    setmap(map);
    dispmap(map);

    return EXIT_SUCCESS;
}