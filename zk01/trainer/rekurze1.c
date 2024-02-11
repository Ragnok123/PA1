#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
void prochazet(int pole[], int currentIndex, int mezivypocet){
    int size = sizeof(pole);

    if(currentIndex > size+1){
        printf(" = %i", mezivypocet);
        return;
    }

    int number = pole[currentIndex];
    mezivypocet += number;
    printf("%i", number);
    if(currentIndex != size+1){
        printf(" + ");
    }
    

    prochazet(pole, currentIndex+1, mezivypocet);
}

void prochazetNew(int pole[], int currentIndex){
    prochazet(pole, currentIndex, 0);
}

void kratit(int a, int b){
    if(a % 2 == 0 && b % 2 == 0){
        a = a/2; b = b/2;
    } else if(a % 3 == 0 && b % 3 == 0){
        a = a/3; b = b/3;
    } else if(a % 4 == 0 && b % 4 == 0){
        a = a/4; b = b/4;
    } else if(a % 5 == 0 && b % 5 == 0){
        a = a/5; b = b/5;
    } else {
        printf("Konecny vysledek: %i/%i\n", a, b);
        return;
    }
    kratit(a,b);
}

// **
// ++
// +-
// -+
// --

 void vymena(int pocetPrvku, int currentIndex){ // hledame vsechny moznosti + a -

    if(currentIndex >= pocetPrvku){
        return;
    }
    int num = (int) pow(2,pocetPrvku);
    
    for(int i = 1; i <= num; i++){
        int change = 1;
        int mid = (num/(2*(currentIndex+1)));
        printf("Mid: %i\n", mid);
        if((num % (2*(currentIndex+1))) == 1) change = !change;
        if(change){
            printf("+");
        } else {
            printf("-");
        }
        printf("\n");
    }

    vymena(pocetPrvku, currentIndex+1);
}*/

void iteruj(char *string, int *poleCisel, int pocetPrvku, int number[], int vysledek, int index){
    if(index >= pocetPrvku){
        for(int i = 0; i < pocetPrvku+1; i++){
            char cislo = (char) poleCisel[i] + '0';
            char znamenko;
            if(i < pocetPrvku){
                znamenko = (char) number[i];
            } else { znamenko = '\0';}
            //printf("%c%c", cislo, znamenko);
            string[index] = string[index]+cislo+znamenko;
            //char cislo = sprintf(string[index],sizeof[], "%i", poleCisel[i]);
            //sprintf(string[index]);
            //string[index][i] = cislo  + number[i];
            //printf("%i %c ", poleCisel[i], number[i]);
            //string[i] = poleCisel[i] + '0' + number[i];
        }
        //printf("%i", poleCisel[pocetPrvku]);
        //string[index][pocetPrvku] = poleCisel[pocetPrvku] + '0';
        //string[index][pocetPrvku+1] = '\0';
        printf("\n");

        printf("%c \n", string[index]);

        return;
    }


    char pole[] = {'+', '-'};
    for(int i = 0; i < 2; i++){
        number[index] = pole[i];
        iteruj(string, poleCisel, pocetPrvku, number, vysledek, index+1);
    }
    return;
}

void vymena(int *poleCisel, int pocetPrvku, int index){
    char pole[] = {'+', '-'};
    int *number = (int*)malloc(sizeof(int)*pocetPrvku);
    int num = (int)pow(2,pocetPrvku);
    char *string = (char*) malloc(2000*sizeof(char));
    iteruj(string, poleCisel, pocetPrvku, number, 0, 0);

}

int main(){
    char *rovnice = "2 5 2 5";

    int whiteSpaces = 0;
    int index = 0;

    int capacity = 16;
    int pSize = 0;
    int *pole = (int*) malloc(capacity * sizeof(int));
    while(rovnice[index] != '\0'){
        if(rovnice[index] >= '0' && rovnice[index] <= '9'){
            if(capacity == pSize){
                capacity *= 2;
                pole = (int*) realloc(pole, capacity * sizeof(int));
            }
            pole[pSize++] = (int)rovnice[index] - '0';
        } else {
            whiteSpaces++;
        }
        index++;
    }
    vymena(pole, whiteSpaces, 0);
    free(pole);

    // +++ a 2525 => 
    //      2(0) +(0) 5(1) +(1) 2(2) +(2) 5(3)



    return 0;
}