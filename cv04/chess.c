#include <stdio.h>
#include <math.h>

int main (void){
	int pole, velikost;
    printf("Zadejte pocet poli:\n");
    if(scanf(" %i ", &pole) != 1 || pole <= 0){
        printf("Nespravny vstup.\n");
        return 1;
    }
    printf("Zadejte velikost pole:\n");
    if(scanf(" %i ", &velikost) != 1 || velikost <= 0){
        printf("Nespravny vstup.\n");
        return 1;
    }

    int charRows = pole*velikost;
    printf("+");
    for(int i = 0; i < charRows; i++){
        printf("-");
    }
    printf("+\n");
    for (int row = 0; row < charRows; row++) {
        printf("|");
        for (int col = 0; col < charRows; col++) {
            if ((row/velikost + col/velikost) % 2 == 0) {
                printf(" ");
            } else {
                printf("X");
            }
        }
        printf("|\n");
    }

    printf("+");
    for(int i = 0; i < charRows; i++){
        printf("-");
    }
    printf("+\n");

    return 0;
}