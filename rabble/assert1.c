#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main () {
    double a, b;

    scanf("%lf", &a);
    scanf("%lf", &b);

    assert(b != 0);

    printf("%lf\n", a / b);

    return EXIT_SUCCESS;
}