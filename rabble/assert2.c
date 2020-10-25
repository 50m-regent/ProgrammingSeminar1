#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    char buf[81];
    double a, b;

    fgets(buf, sizeof(buf), stdin);
    a = atof(buf);
    fgets(buf, sizeof(buf), stdin);
    b = atof(buf);

    assert(b != 0);

    printf("%lf\n", a / b);

    return EXIT_SUCCESS;
}