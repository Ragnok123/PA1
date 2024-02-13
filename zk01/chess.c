#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void vytiskniPole(int size, int index, int currentColor){
    if(index == size) return;
    printf("|");
    for(int i = 0; i < size; i++){
        if(currentColor){
            printf("x");
        } else {
            printf("o");
        }
        currentColor = !currentColor;
    }
    printf("|\n");
    currentColor = (size % 2 == 0) ? !currentColor : currentColor;
    vytiskniPole(size, index+1, currentColor);
}

int main(){
    int size;
    printf("Zadejte velikost...\n");
    if(scanf("%i",&size) != 1){
        printf("Nespravny vstup.\n");
        return 1;
    }
    int currentColor = 0;
    int currentIndex = 0;
    for(int i = 0; i < size+2; i++){
        printf("-");
    }
    printf("\n");

    vytiskniPole(size, currentIndex, currentColor);

    for(int i = 0; i < size+2; i++){
        printf("-");
    }
    printf("\n");

    return 0;
}