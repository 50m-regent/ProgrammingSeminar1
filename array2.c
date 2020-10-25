#include <stdio.h>
#include <stdlib.h>

int **allocmap(int mx, int my) {
    int **m;
    int y;

    m = malloc(my * sizeof(void*));
    if (m == NULL) return 0;

    for (y = 0; y < my; y++) {
        m[y] = malloc(mx * sizeof(int));
        if (m[y] == NULL) {
            while (--y >= 0) free(m[y]);
            free(m);
            return 0;
        }
    }

    return m;
}

void freemap(int y, int** m) {
    while (--y >= 0) free(m[y]);
    free(m);
}

void setmap(int mx, int my, int **m) {
    int x, y;

    for (y = 0; y < my; ++y) {
        for (x = 0; x < mx; ++x) {
            m[y][x] = (x + 1) * (y + 1);
        }
    }
}

void dispmap(int mx, int my, int **m) {
    int x, y;

    for (y = 0; y < my; ++y) {
        for (x = 0; x < mx; ++x) {
            printf("%3d", m[y][x]);
        }
        printf("\n");
    }
}

int main() {
    int mx = 5, my = 4;
    int **map;

    if ((map = allocmap(mx, my)) == NULL) {
        return EXIT_FAILURE;
    }

    setmap(mx, my, map);
    dispmap(mx, my, map);
    freemap(my, map);

    return EXIT_SUCCESS;
}