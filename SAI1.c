#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define DICE_NUM 2

int main () {
    srand((unsigned)time(NULL));

    int pred, cont, dice[DICE_NUM], sum;

    do {
        do {
            printf("Predict(Even: 0, Odd: 1)<< ");
            scanf("%d", &pred);
        } while (pred < 0 || pred > 1);

        puts("-------------------");
        puts("Rolling the dice...\n");
        
        sleep(1);

        sum = 0;
        for (int i = 0; i < DICE_NUM; i++) {
            dice[i] = rand() % 6 + 1;
            sum += dice[i];

            printf("Die%d: %d, ", i + 1, dice[i]);
        }

        printf(
            "Sum: %d (%s)\n",
            sum,
            sum % 2 ? "Odd" : "Even"
        );

        if ((sum % 2 && pred) || (!(sum % 2) && !pred)) {
            puts("You Win!");
        } else {
            puts("You Lose...");
        }
        puts("-------------------\n");
        sleep(1);

        printf("Finish: 0, Continue: Else<< ");
        scanf("%d", &cont);
    } while (cont);
    
    puts("\nBye!");
    return EXIT_SUCCESS;
}