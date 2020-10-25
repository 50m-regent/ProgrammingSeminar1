#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define BOARDW 10
#define BOARDH 10

int main () {
    srand((unsigned)time(NULL));

    int predx, predy, targx, targy, cont;

    do {
        puts("---------------");
        puts("Hiding target...\n");
        sleep(1);

        targx = rand() % BOARDW + 1;
        targy = rand() % BOARDH + 1;

        do {
            do {
                printf("Predict X<< ");
                scanf("%d", &predx);
            } while (predx < 1 || predx > BOARDW);

            do {
                printf("Predict Y<< ");
                scanf("%d", &predy);
            } while (predy < 1 || predy > BOARDH);

            printf(
                "Hint: %d\n\n",
                abs(targx - predx) + abs(targy - predy)
            );
        } while (predx != targx || predy != targy);

        puts("Correct!");
        puts("---------------");

        printf("Finish: 0, Continue: Else<< ");
        scanf("%d", &cont);
    } while (cont);
    
    puts("\nBye!");
    return EXIT_SUCCESS;
}