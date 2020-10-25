#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

int main () {
    srand((unsigned)time(NULL));

    int pred, card, cont;

    do {
        puts("---------------");
        puts("Drawing card...\n");
        sleep(1);

        card = rand() % 13 + 1;

        do {
            do {
                printf("Predict(1-13)<< ");
                scanf("%d", &pred);
            } while (pred < 1 || pred > 13);

            if (pred < card) puts("Low");
            if (pred > card) puts("High");
        } while (pred != card);

        puts("\nCorrect!");
        puts("---------------");

        printf("Finish: 0, Continue: Else<< ");
        scanf("%d", &cont);
    } while (cont);
    
    puts("\nBye!");
    return EXIT_SUCCESS;
}